#ifndef HL_STRING
#define HL_STRING

#include <iostream>

class mystring {
  public:
    mystring() = default;

    ~mystring() { delete[] __data; };

    mystring(const mystring &s) {
        __size = s.__size;
        __capacity = s.__capacity;
        if (__size != 0) {
            __data = new char[__capacity];
            for (size_t i = 0; i < __size; ++i) { __data[i] = s.__data[i]; }
            // manually set the null-terminator
            __data[__size] = '\0';
            // if you comment this line, you may find the programm goes fine.
            // but that is because many implementations initialize the memory to zero for security reasons
            // i.e. '\0'
            // but that's not guaranteed in C++ standard.
            // Therefore you cannot and should not rely on this behavior.

            // optimize:
            // if (s.__size != 0) {
            //     strcpy(__data, s.__data);
            // } else {
            //     __data[0] = '\0';
            // }
        }
    };

    mystring(mystring &&s) {
        __data = s.__data;
        __size = s.__size;
        __capacity = s.__capacity;
        s.__data = nullptr;
        s.__size = 0;
        s.__capacity = 0;
    };

    mystring(const char *s) {
        if (s != nullptr) { // notice: strcpy wants two non-null pointers
            __size = strlen(s);
            __capacity = std::max(__size + 1, MINIMUM_CAPACITY);
            __data = new char[__capacity];
            strcpy(__data, s);  // add '\0' at __data[__size] for us
                                // that's why we need __size + 1 at least
        }
    };

    mystring &operator=(const mystring &s) {
        if (this != &s) {
            delete[] __data;

            __size = s.__size;
            __capacity = s.__capacity;
            if (__size != 0) {
                __data = new char[__capacity];
                strcpy(__data, s.__data);
            } else {
                __data = nullptr;
            }
        }
        return *this;
    };

    // mystring &operator=(const mystring &s) {
    //     if (this != &s) {
    //         delete[] __data;
    //         __data = nullptr;

    //         __size = s.__size;
    //         __capacity = s.__capacity;
    //         if (__size != 0) {
    //             __data = new char[__capacity];
    //             for (size_t i = 0; i < __size; ++i) { __data[i] = s.__data[i]; };
    //             // manually set the null-terminator
    //             __data[__size] = '\0';
    //         }
    //     }
    //     return *this;
    // };

    mystring &operator=(mystring &&s) {
        if (this != &s) {
            delete[] __data;
            __size = s.__size;
            __capacity = s.__capacity;

            // we dont need to check if __size == 0
            __data = s.__data; // simply get the ownership
            s.__data = nullptr; // any clear the old ones
            s.__size = 0;
            s.__capacity = 0;
        }
        return *this;
    };

    mystring &operator=(const char *s) {
        delete[] __data;
        if (s != nullptr) {
            __size = strlen(s);
            __capacity = std::max(__size + 1, MINIMUM_CAPACITY);
            __data = new char[__capacity];
            strcpy(__data, s);  // auto set the null-terminator
        } else {
            __data = nullptr;
            __size = 0;
            __capacity = 0;
        }
        return *this;
    };

    mystring operator+(const mystring &rhs) {
        if (__data == nullptr) return rhs;
        if (rhs.__data == nullptr) return *this;

        size_t __new_size = __size + rhs.__size;
        mystring result;
        result.__size = __new_size;
        result.__capacity = __new_size + 1;
        result.__data = new char[result.__capacity];

        strcpy(result.__data, __data);
        strcat(result.__data, rhs.__data);
        return result;
    };

    mystring &operator+=(const mystring &rhs) {
        if (__size == 0) {
            *this = rhs;
        } else if (rhs.__size != 0) {
            __size += rhs.__size;
            // we compare size + 1 to capacity, not size!!!
            // since we need a space for the null-terminator.
            if (__size + 1 <= __capacity) {
                strcat(__data, rhs.__data);
            } else {
                // resize
                char *__old_data = __data;
                __capacity = std::max(MINIMUM_CAPACITY, (__size + 1) * 2);
                __data = new char[__capacity];
                strcpy(__data, __old_data);
                delete[] __old_data;
                strcat(__data, rhs.__data);
            }
        }
        return *this;
    };

    bool operator==(const mystring &rhs) {
        if (__size != rhs.__size) return false;
        for (size_t i = 0; i < __size; ++i) {
            if (__data[i] != rhs.__data[i]) { return false; }
        }
        return true;
    };


    [[nodiscard]] size_t size() const noexcept { return __size; };

    [[nodiscard]] size_t length() const noexcept { return __size; };

    [[nodiscard]] size_t capacity() const noexcept { return __capacity; };

    [[nodiscard]] bool empty() const noexcept { return __size == 0; };

    const char &operator[](size_t i) const noexcept { return __data[i]; };

    char &operator[](size_t i) noexcept { return __data[i]; };

    // for test
    void print() const {
        std::cout << "Here goed string:" << std::endl;
        if (__size != 0) { std::cout << __data << std::endl; }
    }

  private:
    char *__data{nullptr};
    size_t __size{0};
    size_t __capacity{0};

    static constexpr size_t MINIMUM_CAPACITY = 8;
};

#endif