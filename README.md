#### Mar 18 Updata:

* add dctor
* notice when assign we're checking address rather than value

```
// we do this
if (this != &rhs) {}

// rather than
if (*this != rhs) {}
```

* when string assign ctor, we need to check if __size == 0 since we will call strcpy() which will want two non-null pointers. But for vector we don't need.
* for string, replace all manual operations with strcpy(), and make sure to set __data[0] = '\0' if __size == 0.
* for move assign ctor, we don't need to check if __size == 0 like normal assign ctor. We are simply take the ownership and clear the old ones.
* set __data = nullptr immediately to prevent potential issues rather than doing later inside the else-statement.

```
    // do this:
    mystring &operator=(const mystring &s) {
        if (this != &s) {
            delete[] __data;
	    __data = nullptr;

            __size = s.__size;
            __capacity = s.__capacity;
            if (__size != 0) {
                __data = new char[__capacity];
                strcpy(__data, s.__data);
            }
        }
        return *this;
    };

    // rather than:  
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
```
