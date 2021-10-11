#ifndef __LFU__H__
#define __LFU__H__


#include <iostream>
#include <unordered_map>
#include <list>
#include <iterator>
#include <vector>
#include <cassert>


//! Declaration of Item structure
template <typename T>
struct Item;

//! Declaration of FreqNode structure
template <typename T>
struct FreqNode;


//! typedef for iterator of std::list<FreqNode>
template <typename T>
using FreqIt = typename std::list<FreqNode<T>>::iterator;

//! typedef for iterator of std::list<Item>
template <typename T>
using ItemIt = typename std::list<Item<T>>::iterator;


//! Definition of FreqNode structure
template <typename T>
struct FreqNode
{
    int hits_;
    std::list<Item<T>> items_;

    //!Ctor
    FreqNode(int hits = 1) : hits_(hits), items_() {}
};


//! Definition of Item structure
template <typename T>
struct Item
{
    T data_;
    FreqIt<T> parent_;
    
    //!Ctor
    Item(T data, FreqIt<T> parent) : data_(data), parent_(parent) {}
};



//! Class for LFU algorithm
template <typename T, typename KeyT = int>
class Cache
{
private:

    size_t capacity = 0;
    
    //! List of FreqNodes
    std::list<FreqNode<T>> freqlist_;

    //! typedef for iterator of std::unordered_map<KeyT, ItemIt<T>>
    std::unordered_map<KeyT, ItemIt<T>> hash_;
    using HashIt = typename std::unordered_map<KeyT, ItemIt<T>>::iterator;
    

public:

    //!Ctor
    Cache(size_t cap) : capacity(cap) {}

    //--------------------------------------------------------
    //! Function for checking if there is an item in the cache
    //! @param[in] elem   requested element
    //!
    //! @return true if cache hit happened
    //!         false if element doesn't exist in the cache
    //--------------------------------------------------------

    template <typename F> 
    bool lookup(const KeyT elem, F slow_get_page)
    {
        //find element in the map
        HashIt entry = hash_.find(elem);

        //if there's no such element in the map
        if (entry == hash_.end())
        {

            //element wasn't found, insert new
            insert_item(elem, slow_get_page);
            
            return false;
        }

        //element was found
        incr_frequency(entry->second);
        return true;
    }
    

private:


    //! Function for deleting least frequently used element from the cache

    void delete_lf_used()
    {
        if (freqlist_.size() > 0)
        {
            //delete element from hashtable and from freqlist
            hash_.erase(freqlist_.front().items_.back().data_);
            freqlist_.front().items_.pop_back();

            //if items_ become empty after deletion -> delete freqnode from freqlist
            if (freqlist_.front().items_.empty())
                freqlist_.pop_front();
        }
    }

    //--------------------------------------------------------
    //! Function for inserting an element into the cache
    //! @param[in] elem   element to insert
    //--------------------------------------------------------
    template <typename F>
    void insert_item (KeyT elem, F slow_get_page) //&
    {
        if (hash_.size() >= capacity)
            delete_lf_used();

        //adding ine more freqnode if necessary
        if (freqlist_.empty() || freqlist_.front().hits_ != 1)
            freqlist_.push_front(FreqNode<T>());
        
        //adding the element to the freqlist and to the hashtable
        freqlist_.front().items_.push_front((Item<T>(slow_get_page(elem), freqlist_.begin())));
        hash_.insert({elem, freqlist_.front().items_.begin()});

    }

    //--------------------------------------------------------
    //! Function for incrementing usage frequency of the element
    //! @param[in] item_it   iterator to the element that was inserted
    //--------------------------------------------------------

    void incr_frequency(ItemIt<T> item_it)
    {
        //if there was only one freqnode in the freqlist before inserting new element
        if (next(item_it->parent_) == freqlist_.end())
        {
            freqlist_.emplace_back(item_it->parent_->hits_ + 1);
        }

        FreqIt<T> freq_it = item_it->parent_; 
        FreqIt<T> next_freq_it = ++freq_it;
        --freq_it;

        //if at least one element with incremented frequency already exists
        if (next_freq_it->hits_ == (freq_it->hits_ + 1))
        {
            next_freq_it->items_.push_front(Item<T> (item_it->data_, next_freq_it));
            Change_freq(item_it, freq_it, next_freq_it);
        }
        else
        {
            //if element with incremented frequency doesn't exist
            FreqIt<T> new_freq_it = freqlist_.insert(next_freq_it, FreqNode<T>(freq_it->hits_ + 1));
            new_freq_it->items_.push_front(Item<T>(item_it->data_, new_freq_it));
            Change_freq(item_it, freq_it, new_freq_it);
        }
    }


    //--------------------------------------------------------
    //! Function for retying the element to the new freqnode
    //! @param[in] item_it   iterator to the element that will be retied
    //! @param[in] cur       iterator to the current freqnode
    //! @param[in] fut       iterator to the next freqnode (with incremented frequency)
    //--------------------------------------------------------
    void Change_freq(ItemIt<T> item_it, FreqIt<T> cur, FreqIt<T> fut)
    {
        hash_.erase(item_it->data_);
        hash_.insert({item_it->data_, fut->items_.begin()});
        cur->items_.erase(item_it);
        if(cur->items_.empty())
            freqlist_.erase(cur);
    }
};


#endif 