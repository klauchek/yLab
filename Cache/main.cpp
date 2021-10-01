#include <iostream>
#include "lfu.h"

int main()
{

size_t cap_of_cache = 0;
int calls = 0;

std::cin >> cap_of_cache >> calls;
    assert(std::cin.good());

Cache<int> cache(cap_of_cache);

int hits;
hits = cache.test_processing(calls);

std::cout << "Cache hits = " << hits << "\n";  

    return 0;
}