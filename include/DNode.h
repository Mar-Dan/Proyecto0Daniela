#ifndef DNODE_H
#define DNODE_H
/*Hecha en clase: Nodo de listas doblemente enlazadas*/
template <typename E>
class DNode {
public:
    E element;
    DNode<E> *next;
    DNode<E> *previous;

    DNode(E element, DNode<E> *next, DNode<E> *previous) {
        this->element = element;
        this->next = next;
        this->previous = previous;
    }
    DNode(DNode<E> *next, DNode<E> *previous) {
        this->next = next;
        this->previous = previous;
    }
};

#endif // DNODE_H
