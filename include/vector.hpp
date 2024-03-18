#ifndef HL_VECTOR
#define HL_VECTOR

#include <algorithm>
#include <iostream>

template<typename T>
class myvector {
  public:
    myvector() = default;

    ~myvector() { delete[] __data; };

    myvector(const myvector &v) {
        __capacity = v.__capacity;
        __size = v.__size;
        if (__size != 0) {
            __data = new T[__capacity];
            for (size_t i = 0; i < __size; ++i) { __data[i] = v[i]; }
        }
    }

    myvector &operator=(const myvector &v) {
        if (this != &v) {
            delete[] __data;
            // set __data = nullptr immediately
            __data = nullptr;

            __capacity = v.__capacity;
            __size = v.__size;
            if (__size != 0) {
                __data = new T[__capacity];
                for (size_t i = 0; i < __size; ++i) { __data[i] = v[i]; }
            }
        }
        return *this;
    }

    myvector(myvector &&v) {
        __data = v.__data;
        __size = v.__size;
        __capacity = v.__capacity;
        v.__data = nullptr;
        v.__size = 0;
        v.__capacity = 0;
    }

    myvector &operator=(myvector &&v) {
        if (this != &v) {
            delete[] __data;
            // __data = nullptr; // dont need cause we will overwrite
            __capacity = v.__capacity;
            __size = v.__size;

            // we dont need to check if __size == 0
            __data = v.__data;
            v.__data = nullptr;
            v.__size = 0;
            v.__capacity = 0;      
        }
        return *this;
    }


    [[nodiscard]] size_t size() const noexcept { return __size; };

    [[nodiscard]] size_t capacity() const noexcept { return __capacity; };

    [[nodiscard]] bool empty() const noexcept { return __size == 0; };

    const T &operator[](size_t i) const { return __data[i]; };

    T &operator[](size_t i) { return __data[i]; };

    void push_back(const T &value);

    void push_back(T &&value);

    void pop_back() { __size--; };

    // for test
    void print() const noexcept {
        std::cout << "Here goes vecotr:" << std::endl;
        for (size_t i = 0; i < __size; ++i) {
            std::cout << __data[i] << " " << std::endl;
        }
    }


  private:
    T *__data{nullptr};
    size_t __size{0};
    size_t __capacity{0};

    static constexpr size_t MINIMUM_CAPACITY = 8;
};

template<typename T>
void myvector<T>::push_back(const T &value) {
    if (__size == __capacity) {
        auto __old_data = __data;
        __capacity = std::max(MINIMUM_CAPACITY, 2 * __size);
        __data = new T[__capacity];
        for (size_t i = 0; i < __size; ++i) {
            __data[i] = __old_data[i];
        }
        delete[] __old_data;
    }
    __data[__size++] = value;
}

template<typename T>
void myvector<T>::push_back(T &&value) {
    if (__size == __capacity) {
        __capacity = std::max(MINIMUM_CAPACITY, 2 * __size);
        auto __new_data = new T[__capacity];
        for (size_t i = 0; i < __size; ++i) {
            __new_data[i] = __data[i];
        }
        delete[] __data;
        __data = __new_data;
    }
    __data[__size++] = std::move(value);
}

#endif