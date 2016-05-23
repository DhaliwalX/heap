#include <iostream>
#include <string>
#include <cstring>
#include "heap.h"

#define parent(x) (x >> 1)
#define leftchild(x) ((x << 1) + 1);
#define rightchild(x) ((x << 1) + 2)

void max_heapify(long int *arr, int size, int pos)
{
    int right = rightchild(pos);
    int left = leftchild(pos);
    int largest = pos;

    if (right < size && arr[right] > arr[pos])
        largest = right;
    if (left < size && arr[left] > arr[largest])
        largest = left;

    /* here right is used as temporary only */
    if (largest != pos) {
        right = arr[largest];
        arr[largest] = arr[pos];
        arr[pos] = right;
        max_heapify(arr, size, largest);
    }
}

void max_heapify_nr(long int *arr, int size, int pos)
{
    int right;
    int left;
    int largest = pos;
    do {
        pos = largest;
        right = rightchild(pos);
        left = leftchild(pos);

        if (right < size && arr[right] > arr[pos])
            largest = right;
        if (left < size && arr[left] > arr[largest])
            largest = left;

        /* here right is used as temporary only */
        if (largest != pos) {
            right = arr[largest];
            arr[largest] = arr[pos];
            arr[pos] = right;
        }
    } while (largest != pos);
}

void build_heap(long int *arr, int size)
{
    for(int i = size >> 1; i >= 0; i--) {
        max_heapify_nr(arr, size, i);
    }
}

void heap_sort(long int *arr, int size)
{
    long int temp;
    build_heap(arr, size);
    for (int i = size - 1; i > 0; i--) {
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        size = size - 1;
        max_heapify_nr(arr, size, 0);
    }
}

int main(int argc, char *argv[])
{
    long *p = nullptr;
    size_t size, alloc;
    if (argc < 2 || !std::strcmp(argv[1], "-h") || !std::strcmp(argv[1], "--help")) {
        std::cout << "usage: a numbers\n";
        exit(0);
    }
    long *arr = new long[argc - 1];
    long *sarr = new long[argc - 1];

    for (int i = 1; i < argc; i++) {
        try {
            arr[i - 1] = std::stol(argv[i]);
            sarr[i - 1] = std::stol(argv[i]);
        }
        catch (std::exception &e) {
            std::cout << "invalid arguments, taking argv[" << i << "] as '0'\n";
            arr[i - 1] = 0;
            sarr[i - 1] = 0;
        }
    }

    build_heap(arr, argc - 1);
    for (int i = 0; i < argc - 1; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    heap<long> l;
    l.set(heap<long>::heap_type::max);
    for (int i = 0; i < argc - 1; i++) {
        l.add(arr[i]);
    }
    p = l.return_array(&size, &alloc);

    for (int i = 0; i < size; i++) {
        std::cout << p[i] << " ";
    }

    std::cout << std::endl;
    heap_sort(sarr, argc - 1);

    for (int i = 0; i < argc - 1; i++) {
        std::cout << sarr[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}