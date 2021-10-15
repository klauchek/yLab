#include <iostream>
#include "belady.h"

//! Slow get page callback func imitation

int slow_get_page_int(int key){
        return key;}


int main()
{
    int cap_of_cache = 0;
    int calls = 0;

    std::cin >> cap_of_cache >> calls;
        assert(std::cin.good());

    int* pages = new int[calls];
    assert(pages);

    BeladyCache<int> Cache(cap_of_cache, calls, pages);

    int hits = 0;

    for (int i = 0; i < calls; ++i)
    {
        std::cin >> pages[i];
        assert(std::cin.good());
    }
    for (int i = 0; i < calls; ++i)
    {
        if (Cache.belady_lookup(pages[i], slow_get_page_int))
            ++hits;
    }

    std::cout << "Cache hits = " << hits << "\n";  

    delete[] pages;

    return 0;
}