#include <iostream>
#include <cassert>

bool lookup(int* cache, int* size_of_cache, int cap_of_cache, int* pages, int calls, int request, int num);

int main()
{

    size_t cap_of_cache = 0;
    int calls = 0;

    std::cin >> cap_of_cache >> calls;
    assert(std::cin.good());


    int* cache = new int[cap_of_cache];
    int* pages = new int[calls];
    int size_of_cache = 0;
    int hits = 0;


    for (int i = 0; i < calls; ++i)
    {
        std::cin >> pages[i];
        assert(std::cin.good());
    }

    for (int num = 0; num < calls; ++num)
    {
        int request = pages[num];

        if (lookup(cache, &size_of_cache, cap_of_cache, pages, calls, request, num))
            ++hits;
    }


    delete[] cache;
    delete[] pages;

    std::cout << "Hits: " << hits;

    return 0;
}   


bool lookup(int* cache, int* size_of_cache, int cap_of_cache, int* pages, int calls, int request, int num)
{
    assert (cache);
    int pages_el = 0;
    int cache_el = 0;
    bool found = false;
    
    for (int i = 0; i < cap_of_cache; ++i) //уже есть
    {
        if (cache[i] == request) 
            return true;
    }

    if (*size_of_cache < cap_of_cache) //
    {
        cache[*size_of_cache] = request;
        ++(*size_of_cache);

        return false;
    }

    for (int i = 0; i < cap_of_cache; ++i)
    {
        for(int j = num; j < calls; ++j)
        {
            if(cache[i] == pages[j])
            {
                found = true;
                if (pages_el < j)
                {
                    pages_el = j;
                    cache_el = i;
                }

                break;
            }
        }

        if(!found)
        {
            cache[i] = request;
            return false;
        }
        else
        {
            found = false;
        }
    }

    cache[cache_el] = request;
    return false;
}
