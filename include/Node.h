#ifndef NODE_H
#define NODE_H

template <typename E>
/*Hechos en clase nodos de la clase lista enlazada*/
class Node {
public:
    E element;
    Node<E> *next;

    Node(E element, Node<E> *next = nullptr) {
        this->element = element;
        this->next = next;
    }
    Node(Node<E> *next = nullptr) {
        this->next = next;
    }
};

#endif // NODE_H
