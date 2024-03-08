#ifndef HL_STRING
#define HL_STRING

#include <iostream>

class mystring {
  public:
    mystring() = default;

    ~mystring() { };

    mystring(const mystring &s) { };

    mystring(mystring &&s) { };

    mystring(const char *s) { };

    mystring &operator=(const mystring &s) { };

    mystring &operator=(mystring &&s) { };

    mystring &operator=(const char *s) { };

    mystring &operator+(const mystring &rhs) { };

    mystring &operator+=(const mystring &rhs) { };

    bool operator==(const mystring &rhs) { };


    [[nodiscard]] size_t size() const noexcept { return __size; };

    [[nodiscard]] size_t length() const noexcept { return __size; };

    [[nodiscard]] size_t capacity() const noexcept { return __capacity; };

    [[nodiscard]] bool empty() const noexcept { return __size == 0; };

    const char &operator[](size_t i) const noexcept { return __data[i]; };

    char &operator[](size_t i) noexcept { return __data[i]; };

    // for test
    void print() const {
        if (__size != 0) { std::cout << __data << std::endl; }
    }

  private:
    char *__data{nullptr};
    size_t __size{0};
    size_t __capacity{0};

    static constexpr size_t MINIMUM_CAPACITY = 8;
};

#endif