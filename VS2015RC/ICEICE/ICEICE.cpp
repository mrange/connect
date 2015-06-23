
#include "stdafx.h"

#include <type_traits>
#include <vector>

// Uncomment for a workaround in this specific case
// #define WORKAROUND

namespace
{
  auto collect = [] (auto && collector)
  {
#ifndef WORKAROUND
    using collector_type = decltype (collector);
#endif

    return
      [collector] (auto && source)
      {
        using source_type       = std::remove_reference_t<decltype (source)>    ;
        using value_type        = typename source_type::value_type              ;
#ifdef WORKAROUND
        using collector_type = decltype (collector);
#endif
        using inner_source_type = std::result_of_t<collector_type (value_type)> ;

        return 1;
      };

  };
}

int main ()
{
  std::vector<int> ints;

  auto c = collect ([] (auto && v) {return v;});
  auto r = c (ints);

  return 0;
}
