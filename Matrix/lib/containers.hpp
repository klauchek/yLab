#ifndef CONTAINERS__HPP__
#define CONTAINERS__HPP__

#include <algorithm>
#include <utility>
// ProxyRow here

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
        : static_cast<T *>(::operator new(sizeof(T) * (sz * sz)))), size_(sz * sz) {
            std::cout << "LinearBuf ctor" << std::endl;
        }

    ~LinearBuf() {
        std::cout << "LinearBuf dtor" << std::endl;
        std::cout << size_ << std::endl;
        destroy(arr_, arr_ + size_);
        ::operator delete(arr_);
    }
};

template <typename T>
struct Linear : private LinearBuf<T> { 
    using LinearBuf<T>::size_;
    using LinearBuf<T>::arr_;

    explicit Linear(size_t sz = 0) : LinearBuf<T>(sz * sz) {}

    Linear(Linear &&rhs) = default;
    Linear &operator=(Linear &&rhs) = default;

    Linear(const Linear &rhs) : LinearBuf<T>(rhs.size_) {
        std::cout << "Linear copy ctor" << std::endl;
        std::cout << size_ << std::endl;
        std::cout << rhs.size_ << std::endl;
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

    T &operator[](size_t idx) {
        return arr_[idx];
    }
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

//поймать исключение или сделать nothrow и обработать
    JaggedBuf(size_t sz = 0)
            : arr_((sz == 0) ? nullptr
            : static_cast<T **>(::operator new(sizeof(T*) * sz))), size_1_(sz), size_2_(sz) {
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

    explicit Jagged(size_t sz = 0) : JaggedBuf<T>(sz) {}

    Jagged(const Jagged &rhs) : JaggedBuf<T>(rhs.size_) {
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
};
//--------------------------------------------------------------------//

} //namespace containers

#endif //CONTAINERS__HPP__
