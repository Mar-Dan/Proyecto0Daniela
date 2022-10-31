#ifndef VENTANA_H
#define VENTANA_H

#include <string>
#include <iostream>
#include <stdlib.h>

#include "Tiquete.h"
#include "LinkedPriorityQueue.h"

using namespace std;

class Area;
class Tiquete;

class Ventana{
protected:
    Area *area;
    int n;
    string codigo;
    string lastCliente;
    int tiquetesAtendidos=0;

private:
    string generarCodigo(Area* area){
        string prefijo;
        int nVentana;
        prefijo = area->getCodigo();
        nVentana = area->getCantidadVentanillas();
        area->setCantidadVentanillas(nVentana++);
        if(nVentana < 10)
            return prefijo = prefijo + "0" + to_string(nVentana);
        else
            return prefijo = prefijo + to_string(nVentana);
    }

public:
//    Ventana(){
//        this->area = area;
//        this->n = n;
//        this->codigo = codigo;
//        this->lastCliente = lastCliente;
//        this->tiquetesAtendidos = tiquetesAtendidos;
//    }
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

    Tiquete* atender(){
        Tiquete* tiqueteAtendido;

        if(area->cola->isEmpty()){
                return NULL;
        }

        tiqueteAtendido = area->cola->removeMin();
        lastCliente = tiqueteAtendido->getCodigo();

        return tiqueteAtendido;
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
