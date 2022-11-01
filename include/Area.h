#ifndef AREA_H
#define AREA_H
#include <locale.h>
#include <windows.h>
#include <string>
#include <iostream>

#include "LinkedPriorityQueue.h"
#include "LinkedList.h"
#include "Tiquete.h"
#include "ArrayList.h"

using namespace std;

class Ventana;
class Tiquete;

class Servicio;
#include "Servicio.h" // El include aquí para forzar el orden en que se importa


class Area{
protected:
    int cantVentanillas=0;
    string nombre;
    char codigo;
    int clientes=0;
    int contadorT=0;
public:
    List<Ventana*> *ventanillas = new LinkedList<Ventana*>();
    List<Servicio*> *servicios = new LinkedList<Servicio*>();
    PriorityQueue<Tiquete*>* cola = new LinkedPriorityQueue<Tiquete*>(2);
    List<Tiquete*> *tiquetesAtendidos = new ArrayList<Tiquete*>(100);
    double tiempoT = 0;
    Area(){
        this->ventanillas = ventanillas;
        this->nombre=nombre;
        this->codigo = codigo;
        this->contadorT = contadorT;
        this->tiempoT = tiempoT;

    }
    Area(int cantVentanillas){
        this->cantVentanillas = cantVentanillas;

    }
    Area(string nombre){
        this->nombre = nombre;
        this->clientes = clientes;
    }
    Area(string name, int cVentanillas){
        this->ventanillas = ventanillas;
        this->nombre = name;
        this->codigo = codigo;
        this->contadorT = contadorT;
        this->tiempoT = tiempoT;
        this->cantVentanillas = cVentanillas;
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
    char getCodigo(){
        return codigo;
    }
    string toStringCodigo(){
        string codeString = to_string(codigo);
        return codeString;
    }
    void setVentanillas(List<Ventana*> *v){
        ventanillas = v;
    }
    List<Ventana*>* getVentanillas(){
        return ventanillas;
    }

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
    int getClientes(){
        return clientes;
    }
    void addClientes(){
        clientes++;
    }
    void setContadorT(){
        contadorT++;
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
    double getTiempoPromedio(){
        return tiempoT / tiquetesAtendidos->getSize();
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
        SetConsoleOutputCP( 65001 );
        cout<<getName();
        cout<<" ("<<getCodigo()<<")";
    }



};

#endif // AREA_H
