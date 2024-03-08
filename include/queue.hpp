#ifndef HL_QUEUE
#define HL_QUEUE

#include <algorithm>
#include <iostream>

template<typename T>
class myqueue {
  public:
    myqueue() = default;

    ~myqueue() { delete[] __data; };

    // feature: oject from same class can access each other
    myqueue(const myqueue &q) {
        __front = 0;
        __capacity = __back = q.__back - q.__front;
        if (__capacity != 0) {
            __data = new T[__capacity];
            for (size_t i = 0; i < __back; ++i) {
                __data[i] = q[i + q.__front];
            }
        }
    }

    myqueue &operator=(const myqueue &q) {
        if (this != &q) {
            delete[] __data;
            __data = nullptr;
        }

        __front = 0;
        __capacity = __back = q.__back - q.__front;
        if (__capacity != 0) {
            __data = new T[__capacity];
            for (size_t i = 0; i < __back; ++i) {
                __data[i] = q[i + q.__front];
            }
        }
        return *this;
    }

    myqueue(myqueue &&q) {
        // transfer ownership
        __data = q.__data;
        __front = q.__front;
        __back = q.__back;
        __capacity = q.__capacity;
        // prevent double-delete
        // since q will be auto destroyed
        q.__data = nullptr;
        // make q represent an empty queue.
        // ensures that the use of 'q' after moving does not lead to undefined behavior.
        q.__front = 0;
        q.__back = 0;
        q.__capacity = 0;
    }

    myqueue &operator=(myqueue &&q) {
        if (this != &q) {
            delete[] __data;

            __data = q.__data;
            __front = q.__front;
            __back = q.__back;
            __capacity = q.__capacity;
            q.__data = nullptr;
            q.__front = 0;
            q.__back = 0;
            q.__capacity = 0;
        }
        return *this;
    }

    [[nodiscard]] size_t size() const noexcept { return __back - __front; };

    [[nodiscard]] size_t capacity() const noexcept { return __capacity; };

    [[nodiscard]] bool empty() const noexcept { return __front == __back; };

    // for assignment and copy ctor
    const T &operator[](size_t i) const noexcept { return __data[i]; };

    // for assignment and copy ctor
    T &operator[](size_t i) noexcept { return __data[i]; };
    
    T &front() noexcept { return __data[__front]; };

    const T &front() const noexcept { return __data[__front]; };

    T back() const noexcept { return __data[__back - 1]; };

    T &back() noexcept { return __data[__back - 1]; };

    void push(const T &value);

    void push(T &&value);

    void pop() { __front++; };

    // for test usage
    void print() {
        std::cout << "Here goes queue:" << std::endl;
        for (size_t i = __front; i < __back; ++i) {
            std::cout << __data[i] << " " << std::endl;
        }
    }

  private:
    T *__data{nullptr};
    size_t __front{0};
    size_t __back{0};
    size_t __capacity{0};

    static constexpr size_t MINIMUM_CAPACITY = 8;
};

template<typename T>
void myqueue<T>::push(const T &value) {
    if (__back == __capacity) {
        // resize
        __capacity = std::max(MINIMUM_CAPACITY, 2 * (__back - __front));
        auto __old_data = __data;
        __data = new T[__capacity];
        for (size_t i = __front; i < __back; ++i) {
            __data[i - __front] = __old_data[i];
        }
        delete[] __old_data;
        __back -= __front;
        __front = 0;
    }
    // resize
    __data[__back++] = value;
}

template<typename T>
void myqueue<T>::push(T &&value) {
    if (__back == __capacity) {
        // resize
        __capacity = std::max(MINIMUM_CAPACITY, 2 * (__back - __front));
        auto __old_data = __data;
        __data = new T[__capacity];
        for (size_t i = __front; i < __back; ++i) {
            __data[i - __front] = __old_data[i];
        }
        delete[] __old_data;
        __back -= __front;
        __front = 0;
    }
    // resize
    __data[__back++] = std::move(value);
}

#endif