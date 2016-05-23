# Implementation of Heap in C++

This is a simple implementation of heap in C++. This is a simple header only implementation.

## Functions

    heap<int> a;  /* create a heap container */

    // heap type can be heap<DataType>::heap_type::(max | min)
    a.set(heap<int>::heap_type::max);
    a.add(23); // add 23 to the heap
    a.add(34);
    a.add(2);
    a.add(5); // heap will now be 34 23 2 5

