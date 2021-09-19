#include <iostream>
#include "lfu.h"

int main()
{
 size_t cap_of_cache;
 int num_of_calls;
std::vector<int> pages;

std::cout << "Enter the size:\n";
std::cin >> cap_of_cache;

std::cout << "Enter num of calls:\n";
std::cin >> num_of_calls;

std::cout << "Enter the pages:\n";

int page;

for (int i = 0; i < num_of_calls; ++i)
{
    std::cin >> page;
    pages.push_back(page);

}


Cache<int> cache(cap_of_cache);

int hits;
hits = cache.test_processing(pages, num_of_calls);

std::cout << "Cache hits = " << hits << "\n";  



    return 0;
}