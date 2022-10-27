#ifndef TIQUETES_H
#define TIQUETES_H
#include "Tiquete.h"
#include "LinkedPriorityQueue.h"


class Tiquetes
{
    public:
        int i;
    LinkedPriorityQueue<Tiquete> *Tiquetes = new LinkedPriorityQueue<Tiquete>(i);
};

#endif // TIQUETES_H
