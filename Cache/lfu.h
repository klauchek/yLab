#ifndef __LFU__H__
#define __LFU__H__


#include <iostream>
#include <unordered_map>
#include <list>
#include <iterator>
#include <vector>

template <typename T>
struct Item;

template <typename T>
struct FreqNode;



template <typename T>
using FreqIt = typename std::list<FreqNode<T>>::iterator;


template <typename T>
using ItemIt = typename std::list<Item<T>>::iterator;


template <typename T>
struct FreqNode
{
    int hits_;
    std::list<Item<T>> items_;

    //constructor
    FreqNode(int hits = 1) : hits_(hits), items_() {}
};


template <typename T>
struct Item
{
    T data_;
    FreqIt<T> parent_;
    
    //constructor
    Item(T data, FreqIt<T> parent) : data_(data), parent_(parent) {}
};


template <typename T>
class Cache
{
private:

    size_t capacity = 0;
    
    std::list<FreqNode<T>> freqlist_;

    std::unordered_map<T, ItemIt<T>> hash_;
    using HashIt = typename std::unordered_map<T, ItemIt<T>>::iterator;
    

public:

    //constructor
    Cache(size_t cap) : capacity(cap) {}



    bool lookup(const T &elem)
    {
        //find element in the map
        HashIt entry = hash_.find(elem);

        //if there's no such element in the map
        if (entry == hash_.end())
        {
            //element wasn't found, insert new
            insert_item(elem);
            
            return false;
        }

        //element was found
        incr_frequency(entry->second);
        return true;
    }


    int test_processing(std::vector<int> &pages, int calls)
    {
        int hits = 0;

        for (int i = 0; i < calls; ++i)
        {
            if (lookup(pages[i]))
                ++hits;
        }

        return hits;
    }

    

private:

    //delete least frequetly used element
    void delete_lf_used()
    {
        if (freqlist_.size() > 0)
        {
        hash_.erase(freqlist_.front().items_.back().data_);//delete el from hashtable
        freqlist_.front().items_.pop_back();//delete from freqlist

        //if items_ become empty after deletion
        if (freqlist_.front().items_.empty())
            freqlist_.pop_front();//delete freqnode from freqlist
        }
    }



    void insert_item (T elem)
    {
        if (hash_.size() >= capacity)
            delete_lf_used();
        //добавили еще один частотный узел в начало фреклиста, если недостает
        if (freqlist_.empty() || freqlist_.front().hits_ != 1)
            freqlist_.push_front(FreqNode<T>());
        
        freqlist_.front().items_.push_front((Item<T>(elem, freqlist_.begin())));


        hash_.insert({elem, freqlist_.front().items_.begin()});
            return;
        
    }

    void incr_frequency(ItemIt<T> &item_it)
    {
        FreqIt<T> freq_it = item_it->parent_; 

        //проверка на валидность cout + return
        FreqIt<T> next_freq_it = ++freq_it;
        --freq_it;

        //element with freq + 1 already exists
        if ((next_freq_it != freqlist_.end()) && (next_freq_it->hits_ == freq_it->hits_ + 1))
        {
            next_freq_it->items_.push_front(Item<T> (item_it->data_, next_freq_it));
            Change_freq(item_it, freq_it, next_freq_it);
        }

        //element with freq doesnt exist
        FreqIt<T> new_freq_it = freqlist_.insert(next_freq_it, FreqNode<T>(freq_it->hits_ + 1));
        new_freq_it->items_.push_front(Item<T>(item_it->data_, new_freq_it));
        Change_freq(item_it, freq_it, new_freq_it);
    }


    void Change_freq(ItemIt<T> &item_it, FreqIt<T> &cur, FreqIt<T> &fut)
    {
        hash_.erase(item_it->data_);
        hash_.insert({item_it->data_, fut->items_.begin()});
        cur->items_.erase(item_it);
        if(cur->items_.empty())
            freqlist_.erase(cur);
    }
};

#endif 