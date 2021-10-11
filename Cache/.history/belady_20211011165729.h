#ifndef __BELADY__H__
#define __BELADY__H__


#include <iostream>
#include <unordered_map>
#include <list>


template <typename T, typename KeyT = int>
class BeladyCache
{
private:

const size_t cache_capacity_;
size_t keys_arr_size_;//is known
KeyT *keys_; //is known 

std::unordered_map<KeyT, T> belady_hash_;
using HashIt = typename std::unordered_map<KeyT, T>::iterator;

public:

BeladyCache(size_t cache_cap, size_t keys_sz, KeyT *keys) : cache_capacity_(cache_cap),
                                                            keys_arr_size_(keys_sz),
                                                            keys_(keys)
{}

template <typename F>//ok?
bool beladi_lookup(const KeyT elem, F slow_get_page)
{
    //find element in the map
    HashIt entry = belady_hash_.find(elem);

    //if there's no such element in the map
    if (entry == hash_.end())
    {
        //element wasn't found, insert new
        insert_item(elem, slow_get_page);
        
        return false;
    }
    //element was found
    return true;
}

template <typename F>
void insert_item (KeyT elem, F slow_get_page) //&
{
    if (belady_hash_.size() < cache_capacity_)
    {
        //добавляем
        
    }
    
    //adding ine more freqnode if necessary
    if (freqlist_.empty() || freqlist_.front().hits_ != 1)
        freqlist_.push_front(FreqNode<T>());
    
    //adding the element to the freqlist and to the hashtable
    freqlist_.front().items_.push_front((Item<T>(slow_get_page(elem), freqlist_.begin())));
    hash_.insert({elem, freqlist_.front().items_.begin()});

}

};

#endif