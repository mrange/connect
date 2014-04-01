#include "stdafx.h"

#include <set>
#include <map>

int main()
{
    std::map<int, std::set<int>> works
    {
        { 0 , {1 , 2}},
    };


    std::map<int, std::map<int, int>> works2
    {
        { 0 , {{1, 2} , {2, 3}}},
    };

    std::map<int, std::set<int>> crashes
    {
        { 0 , {1 , 2}},
        { 3 , {4 , 5}},
    };

    std::map<int, std::map<int, int>> crashes2
    {
        { 0 , {{1, 2} , {2, 3}}},
        { 3 , {{4, 2} , {5, 3}}},
    };

    return 0;
}
