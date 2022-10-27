#ifndef HEAPPRIORITYQUEUE_H
#define HEAPPRIORITYQUEUE_H

#include <stdexcept>
#include "PriorityQueue.h"
#include "KVPair.h"
#include "MinHeap.h"

template <typename E>
class HeapPriorityQueue : public PriorityQueue<E> {
private:
    MinHeap<KVPair<int, E>> *elements;
    int priorities;

public:
    HeapPriorityQueue(int priorities, int max = DEFAULT_MAX_SIZE) {
        if (priorities < 1)
            throw runtime_error("Invalid number of priorities.");
        elements = new MinHeap<KVPair<int, E>>(max);
        this->priorities = priorities;
    }
    ~HeapPriorityQueue() {
        delete elements;
    }
    void insert(E element, int priority) {
        if (priority < 0 || priority >= priorities)
            throw runtime_error("Invalid priority.");
        KVPair<int, E> p(priority, element);
        elements->insert(p);
    }
    E min() {
        KVPair<int, E> p = elements->first();
        return p.value;
    }
    E removeMin() {
        KVPair<int, E> p = elements->removeFirst();
        return p.value;
    }
    int getSize() {
        return elements->getSize();
    }
    bool isEmpty() {
        return elements->isEmpty();
    }
    void print() {
        elements->print();
    }
};

#endif // HEAPPRIORITYQUEUE_H
