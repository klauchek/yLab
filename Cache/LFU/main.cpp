#include <iostream>
#include "lfu.h"

//! Slow get page callback func imitation

int slow_get_page_int(int key){
        return key;}


//--------------------------------------------------------
//! Function for testing LFU algorithm
//! @param[in] calls   number of requests
//!
//! @return number of cache hits
//--------------------------------------------------------

int test_processing(int calls, size_t size)
{
    Cache<int> cache(size);
    int page;
    int hits = 0;

    for (int i = 0; i < calls; ++i)
    {
        std::cin >> page;
        assert(std::cin.good());
        
        if (cache.lookup(page, slow_get_page_int))
            ++hits;
    }

    return hits;
}

int main()
{
    size_t cap_of_cache = 0;
    int calls = 0;

    std::cin >> cap_of_cache >> calls;
        assert(std::cin.good());

    int hits;
    hits = test_processing(calls, cap_of_cache);

    std::cout << "Cache hits = " << hits << "\n";  

        return 0;
}