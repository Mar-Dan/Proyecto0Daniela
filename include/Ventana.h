#ifndef VENTANA_H
#define VENTANA_H
#include "Area.h"
#include "LinkedPriorityQueue.h"
#include "ListaTiquetes.h"
#include <conio.h>
#include <string>
#include <iostream>
#include <stdlib.h>


using std::to_string;
using namespace std;

class Area;
class Ventana{
protected:
    Area *area;
    int n;
    string codigo;
    string lastCliente;
    int tiquetesAtendidos=0;


public:
    Ventana(){
        this->area = area;
        this->n = n;
        this->codigo = codigo;
        this->lastCliente = lastCliente;
        this->tiquetesAtendidos = tiquetesAtendidos;
    }
    Ventana(Area* area){
        this->area = area;
        this->codigo = area->getCodigo();
    }
    void setArea(Area *a){
        area = a;
    }
    Area* getArea(){
        return area;
    }

    void setCodigo(Area *a, int n){
        codigo =  a->getCodigo()+ to_string(n)+ " ";

    }

    string getCodigo(){
        return codigo;
    }
    string Atender(PriorityQueue<string> *t){
        string lastoCliente = t->min();
        cout<<"Atendiendo a: "<<t->removeMin();

        tiquetesAtendidos++;
        return lastoCliente;
    }

    /*void setlastCliente(){
        lastCliente = Atender(ListaTiquetes<string> *s);
    }*/

    /*void getLastCliente(){

    }*/
    void print(){
        cout<<getCodigo()<<":"<<lastCliente;

    }
    friend ostream& operator << (ostream& os, const Ventana& m){
            os << m.codigo;
            return os ;
    }


};






#endif // VENTANA_H
