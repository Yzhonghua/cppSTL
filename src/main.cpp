#include <iostream>
#include <cstdlib>
#include "queue.hpp"
#include "vector.hpp"
#include "string.hpp"

using std::cout;
using std::endl;

void Usage(char *progname);

void test_queue();

void test_vector();

void test_string();

int main(int argc, char **argv) {
    cout << "Hello World!" << endl;
    if (argc != 2) {
        Usage(argv[0]);
    }

    if (std::string(argv[1]) == "queue") {
        test_queue();
    } else if (std::string(argv[1]) == "vector") {
        test_vector();
    } else if (std::string(argv[1]) == "string") {
        test_string();
    } else {
        cout << "undefined behaviour." << endl;
    }

    return EXIT_SUCCESS;
}

void Usage(char *progname) {
    cout << "Usage: " << progname << " test_part" << endl;
}

void test_queue() {
    myqueue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    myqueue<int> new_q = std::move(q);
    new_q.print();
    // the std::move doesnt destroy the onject
    // It simply casts the object to an rvalue reference to be use for move ctor
    // the moved-from object is still alive
    // and will be destroyed at the same time it normally would have benn
    // like it goes out of scope
    q.print();
}

void test_vector() {
    myvector<char> v;
    v.push_back('a');
    v.push_back('b');
    v.push_back('c');

    myvector<char> new_v = v;
    new_v.print();

    myvector<char> new_new_v(v);
    new_new_v.print();
}

void test_string() {
    mystring a("aaa");
    mystring b("bbb");
    mystring c("ccc");
    mystring test1(a);
    test1.print();
    mystring test2 = a + b;
    test2.print();
    mystring test3 = b;
    test3.print();
    test3 += c;
    test3.print();
}