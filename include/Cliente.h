#ifndef CLIENTE_H
#define CLIENTE_H
#include <cstdlib>
#include <iostream>
using std :: string;
using std :: to_string;
using namespace std;

class Cliente{
private:
    Area *area;
    string codigo;
    int priority;
    int i = 0;

public:
    Cliente(){
        this->codigo = codigo;
        this->priority = priority;
    }

    void setCodigo(){
        codigo = area->getCodigo() + to_string(i);
        i++;
    }

    string getCodigo(){
        return codigo;
    }

    void setPriority(int p){
        priority = p;
    }
    int getPriority(){
        return priority;
    }




};

#endif // CLIENTE_H
