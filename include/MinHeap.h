#ifndef MINHEAP_H
#define MINHEAP_H
#define DEFAULT_MAX_SIZE 1024

#include <stdexcept>
#include <iostream>

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class MinHeap {
private:
    E *elements;
    int max;
    int size;

    int leftChild(int pos) {
        return 2 * pos + 1;
    }
    int rightChild(int pos) {
        return 2 * pos + 2;
    }
    int parent(int pos) {
        return (pos - 1) / 2;
    }
    bool isLeaf(int pos) {
        return leftChild(pos) >= size;
    }
    void swap(int pos1, int pos2) {
        E temp = elements[pos1];
        elements[pos1] = elements[pos2];
        elements[pos2] = temp;
    }
    void siftUp(int pos) {
        while (pos != 0 && elements[pos] < elements[parent(pos)]) {
            swap(pos, parent(pos));
            pos = parent(pos);
        }
    }
    void siftDown(int pos) {
        while (!isLeaf(pos) &&
               elements[pos] > elements[greaterChild(pos)]) {
            int gChild = greaterChild(pos);
            swap(pos, gChild);
            pos = gChild;
        }
    }
    // retorna el hijo de mayor prioridad (menor)
    int greaterChild(int pos) {
        if (rightChild(pos) >= size ||
            elements[leftChild(pos)] < elements[rightChild(pos)])
            return leftChild(pos);
        return rightChild(pos);
    }


public:
    MinHeap(int max = DEFAULT_MAX_SIZE) {
        if (max < 1)
            throw runtime_error("Invalid max size.");
        elements = new E[max];
        this->max = max;
        size = 0;
    }
    ~MinHeap() {
        delete [] elements;
    }
    void insert(E element) {
        if (size == max)
            throw runtime_error("Heap is full.");
        elements[size] = element;
        siftUp(size);
        size++;
    }
    E first() {
        if (size == 0)
            throw runtime_error("Heap is empty.");
        return elements[0];
    }
    E removeFirst() {
        return remove(0);
    }
    E remove(int pos) {
        if (size == 0)
            throw runtime_error("Heap is empty.");
        swap(pos, size - 1);
        size--;
        siftDown(pos);
        return elements[size];
    }
    int getSize() {
        return size;
    }
    bool isEmpty() {
        return size == 0;
    }
    void print() {
        cout << "( ";
        for (int i = 0; i < size; i++)
            cout << elements[i] << " ";
        cout << ")" << endl;
    }
};

#endif // MINHEAP_H
