#ifndef HEAP_H_
#define HEAP_H_

#include <cctype>
#include <algorithm>
/**
 * a generic heap implementation in C++
 */
template <typename DataType>
class heap {
public:
    enum class heap_type {
        min,
        max
    };
    using index_offset_t = DataType*;
    class iterator {
    public:
        iterator() :
            index(nullptr) { }

        iterator(const DataType *dp) :
            index(dp) { }

        iterator(const iterator &it) :
            index(it.iterator) { }

        iterator &operator=(const iterator &it)
        {
            index = it.index;
            return *this;
        }

        DataType &operator*()
        {
            return *index;
        }

        const DataType &operator*() const
        {
            return *index;
        }

        DataType *operator->()
        {
            return index;
        }

        iterator& operator++()
        {
            this->index++;
            return *this;
        }

        iterator operator--()
        {
            this->index--;
            return *this;
        }

        iterator operator++(int)
        {
            return iterator(this->index++);
        }

        iterator operator--(int)
        {
            return iterator(this->index--);
        }


    private:
        /* I am storing the index only */
         index_offset_t index;
    };

    heap() :
        store(nullptr), size(0), alloc(0), type(heap_type::min)
        { }

    heap(const heap<DataType> &other)
    {
        store = new DataType[other.size];
        copy_array_elements(store, other.store, other.size);
        size = other.size;
        alloc = size;
    }

    heap &operator=(const heap<DataType> &other)
    {
        DataType *temp;

        if (size >= other.size) {
            copy_array_elements(store, other.store, other.size);
            size = other.size;
            return *this;
        } else {
            temp = store;
            store = new DataType[other.size];
            copy_array_elements(store, other.store, other.size);
            size = other.size;
            alloc = other.size;
            delete []temp;
            return *this;
        }
    }

    heap(DataType *arr, int size)
    {
        store = new DataType[size];
        for (int i = 0; i < size; i++) {
            store[i] = arr[i];
        }
        this->size = size;
        this->alloc = size;
    }

    heap(DataType *start, DataType *end)
    {
        DataType *it;

        store = new DataType[end - start];
        it = store;
        for (DataType *i = start; i != end; i++) {
            *it = *i;
            it++;
        }
        this->size = end - start;
        this->alloc = this->size;
    }

    ~heap()
    {
        delete []store;
    }

    void set(enum heap_type type)
    {
        this->type = type;
    }

    void build_heap()
    {
        if (type == heap_type::max) {
            build_max_heap();
        } else if (type == heap_type::min) {
            build_min_heap();
        }
    }

    void add(const DataType &element)
    {
        DataType *temp;
        ptrdiff_t i, p;

        if (size == alloc) {
            temp = store;
            store = new DataType[alloc << 1];
            copy_array_elements(store, temp, size);
            delete []temp;
            alloc <<= 1;
        }
        store[size++] = element;
        correct_heap();
    }

    DataType extract()
    {
        DataType ret;

        ret = store[0];
        store[0] = store[--size];
        correct_heap();
    }

    DataType *return_array(size_t *size, size_t *alloc)
    {
        *size = this->size;
        *alloc = this->alloc;
        return store;
    }
private:
    void correct_heap()
    {
        ptrdiff_t i, p;

        i = size - 1;
        p = parent(i);
        if (type == heap_type::max) {
            while (p > 0 && store[p] < store[i]) {
                std::swap(store[p], store[i]);
                i = p;
                p = parent(i);
            }
            _max_heapify(0);
        } else {

            while (p > 0 && store[p] > store[i]) {
                std::swap(store[p], store[i]);
                i = p;
                p = parent(i);
            }
            _min_heapify(0);
        }
    }

    void _max_heapify(int index)
    {
        ptrdiff_t left, right, largest = index;
        DataType element; // this requires the datatype to have default constructor

        do {
            left = left_child(index);
            right = right_child(index);
            index = largest;
            if (left < size && store[left] > store[index]) {
                largest = left;
            }

            if (right < size && store[right] > store[largest]) {
                largest = right;
            }

            if (largest != index) {
                element = store[largest];
                store[largest] = store[index];
                store[index] = element;
            }
        } while (largest != index);
    }

    void _min_heapify(int index)
    {
        ptrdiff_t left, right, largest = index;
        DataType element; // this requires the datatype to have default constructor

        do {
            left = left_child(index);
            right = right_child(index);
            index = largest;
            if (left < size && store[left] < store[index]) {
                largest = left;
            }

            if (right < size && store[right] < store[largest]) {
                largest = right;
            }

            if (largest != index) {
                element = store[largest];
                store[largest] = store[index];
                store[index] = element;
            }
        } while (largest != index);
    }

    void build_max_heap()
    {
        for (ptrdiff_t i = (size >> 1); i >= 0; i--) {
            _max_heapify(i);
        }
    }

    void build_min_heap()
    {
        for (ptrdiff_t i = (size >> 1); i >= 0; i--) {
            _min_heapify(i);
        }
    }

    void copy_array_elements(DataType *first, const DataType *second, int size)
    {
        for (ptrdiff_t i = 0; i < size; i++) {
            first[i] = second[i];
        }
    }

    inline ptrdiff_t parent(const ptrdiff_t element)
    {
        return element >> 1;
    }

    inline ptrdiff_t left_child(const ptrdiff_t parent)
    {
        return (parent << 1) + 1;
    }


    inline ptrdiff_t right_child(const ptrdiff_t parent)
    {
        return (parent << 1) + 2;
    }

    DataType *store;
    size_t size;
    size_t alloc;
    heap_type type;
};

#endif
