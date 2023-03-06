#ifndef CONTAINERS__HPP__
#define CONTAINERS__HPP__

#include <algorithm>
#include <utility>
#include <cmath>
#include <stdexcept>
#include <iterator>

namespace containers {

//--------------------- COMMON HELPERS -----------------------------//
template <typename T> void construct(T *p, const T &rhs) {
    new (p) T(rhs);
}
template <typename T> void construct(T *p, T &&rhs) {
    new (p) T(std::move(rhs));
}

template <typename T> void destroy(T *p) {
    p->~T();
}

template <typename FwdIter> void destroy(FwdIter first, FwdIter last) {
    while (first != last)
        destroy(&*first++);
}
//------------------------------------------------------------------//


//----------------------- LINEAR BUFFER ----------------------------//
template <typename T>
struct LinearBuf {
protected:
    T *arr_;
    size_t size_ = 0;

protected:
    LinearBuf(const LinearBuf &) = delete;
    LinearBuf &operator=(const LinearBuf &) = delete;
    LinearBuf(LinearBuf &&rhs) noexcept
        : arr_(rhs.arr_), size_(rhs.size_) {
            std::cout << "LinearBuf move ctor" << std::endl;
        rhs.arr_ = nullptr;
        rhs.size_ = 0;
    }

    LinearBuf &operator=(LinearBuf &&rhs) noexcept {
        std::cout << "LinearBuf move assign" << std::endl;
        std::swap(arr_, rhs.arr_);
        std::swap(size_, rhs.size_);
        return *this;
    }

    LinearBuf(size_t sz = 0)
        : arr_((sz == 0) ? nullptr
        : static_cast<T *>(::operator new(sizeof(T) * sz))), size_(sz) {
            std::cout << "LinearBuf ctor" << std::endl;
        }

    ~LinearBuf() {
        std::cout << "LinearBuf dtor" << std::endl;
        destroy(arr_, arr_ + size_);
        ::operator delete(arr_);
    }
};


//TODO: think about class struct private public
template <typename T>
struct Linear : private LinearBuf<T> {

    using LinearBuf<T>::size_;
    using LinearBuf<T>::arr_;
    //------------------------ big five ----------------------------//
    Linear(size_t size_1 = 0, size_t size_2 = 0) : LinearBuf<T>(size_1 * size_2) {}

    Linear(Linear &&rhs) = default;
    Linear &operator=(Linear &&rhs) = default;

    Linear(const Linear &rhs) : LinearBuf<T>(rhs.size_) {
        std::cout << "Linear copy ctor" << std::endl;
        size_ = 0;
        while (size_ < rhs.size_) {
            construct(arr_ + size_, rhs.arr_[size_]);
            ++size_;
        }
    }

    Linear &operator=(const Linear &rhs) {
        std::cout << "Linear copy assign" << std::endl;
        Linear tmp(rhs);
        std::swap(*this, tmp);
        return *this;
    }

    //--------------------------------------------------------------//

    T& operator[](size_t idx) { return arr_[idx]; }
    const T& operator[](size_t idx) const { return arr_[idx]; }


    T* get_n_row(size_t idx) { return arr_ + idx; }
    T* const get_n_row(size_t idx) const { return arr_ + idx; }

    void fill(T val) {
        std::fill_n(arr_, size_, val);
    }

    template <typename It>
    void fill(It start, It fin) {
        auto dist = std::distance(start, fin);
        if(dist > size_)
            throw std::out_of_range{"sequence is bigger than buffer size"};

        std::copy_n(start, dist, arr_);
        std::fill_n(arr_ + dist, size_ - dist, T{});
    }

    bool equal(const Linear &rhs) const {
        if(size_ != rhs.size_)
            return false;
        return std::equal(arr_, arr_ + size_, rhs.arr_);
    }

    size_t size() const { return size_; }
};
//------------------------------------------------------------------//

//----------------------- JAGGED BUFFER ----------------------------//

template <typename T>
struct JaggedBuf {
protected:
    T **arr_;
    size_t size_1_ = 0;
    size_t size_2_ = 0;

protected:
    JaggedBuf(const JaggedBuf &) = delete;
    JaggedBuf &operator=(const JaggedBuf &) = delete;
    JaggedBuf(JaggedBuf &&rhs) noexcept
        : arr_(rhs.arr_), size_1_(rhs.size_1_), size_2_(rhs.size_2_) {
            std::cout << "JaggedBuf move ctor" << std::endl;
        rhs.arr_ = nullptr;
        rhs.size_1_ = 0;
        rhs.size_2_ = 0;
    }

    JaggedBuf &operator=(JaggedBuf &&rhs) noexcept {
        std::cout << "JaggedBuf move assign" << std::endl;
        std::swap(arr_, rhs.arr_);
        std::swap(size_1_, rhs.size_1_);
        std::swap(size_2_, rhs.size_2_);
        return *this;
    }

    JaggedBuf(size_t size_1 = 0, size_t size_2 = 0)
            : arr_((size_1 == 0 || size_2 == 0) ? nullptr
            : static_cast<T **>(::operator new(sizeof(T*) * size_1))), size_1_(size_1), size_2_(size_2) {
            std::cout << "JaggedBuf ctor" << std::endl;
            for (size_t i = 0; i < size_1_; ++i)
                arr_[i] = static_cast<T *>(::operator new(sizeof(T) * size_2_));
    }

    ~JaggedBuf() {
        std::cout << "JaggedBuf dtor" << std::endl;
        for (size_t i = 0; i < size_1_; ++i) {
            destroy(arr_[i], arr_[i] + size_2_);
            ::operator delete(arr_[i]);
        }
        destroy(arr_, arr_ + size_1_);
        ::operator delete(arr_);
    }
};

template <typename T>
struct Jagged : private JaggedBuf<T> {
    using JaggedBuf<T>::size_1_;
    using JaggedBuf<T>::size_2_;
    using JaggedBuf<T>::arr_;

    //------------------------ big five ----------------------------//
    Jagged(size_t size_1 = 0, size_t size_2 = 0) : JaggedBuf<T>(size_1, size_2) {}

    Jagged(const Jagged &rhs) : JaggedBuf<T>(rhs.size_1_, rhs.size_2_) {
        std::cout << "Jagged copy ctor" << std::endl;
        size_1_ = 0;
        size_2_ = 0;
        while (size_1_ < rhs.size_1_) {
            while(size_2_ < rhs.size_2_) {
                construct(arr_[size_1_] + size_2_, rhs.arr_[size_1_][size_2_]);
                ++size_2_;
            }
            ++size_1_;
        }
    }

    Jagged &operator=(const Jagged &rhs) {
        std::cout << "Jagged copy assign" << std::endl;
        Jagged tmp(rhs);
        std::swap(*this, tmp);
        return *this;
    }
    //--------------------------------------------------------------//

    T& operator[](size_t idx) { return arr_[idx / size_2_][idx % size_2_]; }
    const T& operator[](size_t idx) const { return arr_[idx / size_2_][idx % size_2_]; }

    T* get_n_row(size_t idx) { return arr_[idx / size_2_]; }
    T* const get_n_row(size_t idx) const { return arr_[idx / size_2_]; }

    void fill(T val) {
        for (size_t i = 0; i < size_1_; ++i)
            std::fill_n(arr_[i], size_2_, val);
    }

    template <typename It>
    void fill(It start, It fin) {
        if(std::distance(start, fin) > size_1_ * size_2_)
            throw std::out_of_range{"sequence is bigger than buffer size"};

        size_t i = 0;
        for(auto it = start; it != fin; ++i) {
            size_t j = 0;
            size_t rem = 0;
            auto dist = std::distance(it, fin);
            rem = std::min(size_2_, static_cast<size_t>(dist));
            std::copy_n(it, rem, arr_[i]);
            j = rem - 1;
            std::advance(it, j + 1);

            if(rem == dist)
                std::fill_n(arr_[i] + rem, size_2_ - rem, T{});
        }
        
        for (; i < size_1_; ++i)
            std::fill_n(arr_[i], size_2_, T{});
    }

    bool equal(const Jagged &rhs) const{
        if(size_1_ != rhs.size_1_ || size_2_ != rhs.size_2_)
            return false;
        for (size_t i = 0; i < size_1_; ++i) {
            if(!std::equal(arr_[i], arr_[i] + size_2_, rhs.arr_[i]))
                return false;
        }
        return true;
    }
};
//--------------------------------------------------------------------//

} //namespace containers



#endif //CONTAINERS__HPP__
