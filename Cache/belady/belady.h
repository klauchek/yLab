#ifndef __BELADY__H__
#define __BELADY__H__


#include <iostream>
#include <unordered_map>
#include <list>
#include <cassert>


template <typename T, typename KeyT = int>
class BeladyCache
{
private:

const int cache_capacity_;
int elems_arr_size_;//is known
T *elems_; //is known 

std::unordered_map<KeyT, T> belady_hash_; //cache itself
using HashIt = typename std::unordered_map<KeyT, T>::iterator;

public:

BeladyCache(int cache_cap, int elems_sz, T *elems) : cache_capacity_(cache_cap),
                                                            elems_arr_size_(elems_sz),
                                                            elems_(elems)
{}

template <typename F>//ok?
bool belady_lookup(const KeyT key, F slow_get_page)
{
    //find element in the map
    HashIt entry = belady_hash_.find(key);

    //if there's no such element in the map
    if (entry == belady_hash_.end())
    {
        //element wasn't found, insert new
        insert_item(key, slow_get_page);
    
        return false;
    }
    //element was found
    return true;
}

template <typename F>
void insert_item (KeyT key, F slow_get_page) //?
{
    if (belady_hash_.size() < cache_capacity_)
    {
        //добавляем в хеш-таблицу - заполняем кэш, еслит место пока есть
        belady_hash_.insert({slow_get_page(key), elems_[key]});//
    }
    
	int lastIn = 0; //in cache
	int found = 0;
	//T last_found  = 0;

	for (auto cache_item : belady_hash_)
	{
		//value to find
		T value = cache_item.second;

		for (int i = 0; i < elems_arr_size_; ++i)//идем по массиву ключей
		{
			if(elems_[i] == value)
			{
				found = 1;
				lastIn = i;//последний
				//last_found = cache_item.second;
				break;
			}
		}
			std:: cout << "At this step(2) found status is: " << found << std::endl;
		
		if (!found)
		{
			std::cout << "Cache item to erase: " << cache_item.second;
		
			belady_hash_.erase(belady_hash_.find(cache_item.second));
			break;
		}
		else
			found = 0;	
	}
	std:: cout << "At this step(1) found status is: " << found << std::endl;
	std:: cout << "Current lastIN: " << lastIn << std::endl;
	//удалем последнюю и вставляем на ее место
	//if(last_found == belady_hash_.size())
	//	belady_hash_.erase(belady_hash_.find(elems_[lastIn]));
	//exit(1);
	belady_hash_.insert({slow_get_page(key), elems_[key]});
}


};

#endif