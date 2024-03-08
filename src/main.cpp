#include <iostream>
#include <cstdlib>
#include "queue.hpp"

using std::cout;
using std::endl;

void Usage(char *progname);

void test_queue();

int main(int argc, char **argv) {
    cout << "Hello World!" << endl;
    if (argc != 2) {
        Usage(argv[0]);
    }

    if (std::string(argv[1]) == "queue") {
        test_queue();
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