#ifndef AREA_H
#define AREA_H
#include "Node.h"
#include "LinkedPriorityQueue.h"
#include "HeapPriorityQueue.h"
#include "LinkedList.h"
#include "Tiquete.h"
#include "ArrayList.h"
//#include "ListaVentanillas.h"
#include <conio.h>
#include <string>
#include <iostream>

using namespace std;

class Ventana;
class Tiquete;

class Servicio;
#include "Servicio.h"


class Area{
protected:
    List<Ventana*> *ventanillas = new LinkedList<Ventana*>();
    int cantVentanillas;
    string nombre;
    string codigo;
    int clientes;
    int contadorT=0;
public:
    List<Servicio*> *servicios = new LinkedList<Servicio*>();
    PriorityQueue<Tiquete*>* cola = new HeapPriorityQueue<Tiquete*>(100);
    List<Tiquete*> *tiquetesAtendidos = new ArrayList<Tiquete*>(100);
    double tiempoT = 0;
    Area(){
        this->ventanillas = ventanillas;
        this->nombre=nombre;
        this->codigo = codigo;
        this->contadorT = contadorT;
        this->tiempoT = tiempoT;
//        List<Servicio*> *servicios = new LinkedList<Servicio*>();
        //this->clientes = clientes;
    }
    Area(int cantVentanillas){
        this->cantVentanillas = cantVentanillas;

    }
    Area(string nombre){
        this->nombre = nombre;
        this->clientes = clientes;
    }
    void setName(string n){
        nombre = n;
        setCodigo();
    }
    string getName(){
        return nombre;
    }
    void setCodigo(){
        codigo = nombre.at(0);
    }
    string getCodigo(){
        return codigo;
    }
    void setVentanillas(List<Ventana*> *v){
        ventanillas = v;
    }
    List<Ventana*>* getVentanillas(){
        return ventanillas;
    }
   /*void setClientes(LinkedPriorityQueue<string> *lista){
        clientes = lista;
    }
    LinkedPriorityQueue<string>* getClientes(){
        return clientes;
    }*/
    void setCantidadVentanillas(int c){
        cantVentanillas = c;
    }
    int getCantidadVentanillas(){
        return cantVentanillas;
    }
    void addVentanilla(Ventana* v){ /*Usar una lista Ventana* para evitar */
        int p = ventanillas->getPos();
        ventanillas->goToEnd();
        ventanillas->insert(v);
        ventanillas->goToPos(p);
    }
    void deleteVentanilla(){
        int p = ventanillas->getPos();
        ventanillas->goToEnd();
        ventanillas->remove();
        ventanillas->goToPos(p);

    }
    void atender(){

    }
    void setContadorT(){
        this->contadorT = contadorT + 1;
    }
    int getContadorT(){
        return contadorT;
    }
    void setTiempoT(double t){
        tiempoT = t;
    }
    double getTiempoT(){
        return tiempoT;
    }
    List<Servicio*>* getServicios(){
        return servicios;
    }
    int getTiquetesAtendidos(){
        return clientes;
    }
    Ventana* deleteVentanilla(Ventana* v){
            if(ventanillas->contains(v))
                return ventanillas->remove();
                else
                    return nullptr;
    }
    void toString(){
        cout<<getName();
        cout<<" ("<<getCodigo()<<")";

        //cout<<"Clientes: "<<endl;
        //clientes->print();

    }



};

#endif // AREA_H
