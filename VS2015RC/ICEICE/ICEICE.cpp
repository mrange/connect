
#include "stdafx.h"

#include <iostream>
#include <type_traits>
#include <vector>

// Set WORKAROUND to 1 or 2 for different workarounds
#define WORKAROUND 0

namespace
{
  struct user
  {
    std::uint64_t id;
  };

  template<typename TValueType>
  struct strip_type
  {
    using type = std::remove_cv_t<std::remove_reference_t<TValueType>>  ;
  };

  template<class TValueType>
  using strip_type_t = typename strip_type<TValueType>::type;

  auto do_it =
    [] (auto && source)
    {
      using source_type           = decltype (source)         ;
      using stripped_source_type  = strip_type_t<source_type> ;

#if WORKAROUND == 1
      return [source = std::forward<source_type> (source)] (int sink)
#else
      return [source = std::forward<source_type> (source)] (auto && sink)
#endif
        {
#if WORKAROUND == 2
          using source_type           = decltype (source)         ;
          using stripped_source_type  = strip_type_t<source_type> ;
#endif
          auto result = stripped_source_type ();
  
          return result;
        };
    };
}

int main ()
{
  std::vector<user> users;
  auto p = do_it (users);
  std::vector<user> r = p (1);

  std::cout << r.size () << std::endl;

  return 0;
}
