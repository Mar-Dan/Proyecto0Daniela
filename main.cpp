#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "LinkedPriorityQueue.h"
#include "DLinkedList.h"
#include "PriorityQueue.h"
#include "Servicio.h"
#include "Area.h"
#include "Ventana.h"
#include "Cliente.h"
#include "Tiquete.h"
#include "ListaVentanillas.h"
#include "Dictionary.h"

using namespace std;
List<Area*> *listaAreas;
List<Servicio*> *listaServicios;


void DefaultAreas(){
    listaAreas = new DLinkedList<Area*>();
    Area* cajas = new Area();
    cajas->setName("Cajas");
    Area* servicioAlCLiente = new Area();
    servicioAlCLiente->setName("Servicio al Cliente");
    Area* empresarial = new Area();
    empresarial->setName("Empresarial");
    Area* informacion = new Area();
    informacion->setName("Información");
    listaAreas->append(cajas);
    listaAreas->append(servicioAlCLiente);
    listaAreas->append(empresarial);
    listaAreas->append(informacion);

}
void printListAreas(){
    int p = listaAreas->getPos();
    cout<<"AREAS:"<<endl;
    for(listaAreas->goToStart(); !listaAreas->atEnd(); listaAreas->next()){
        Area* a = listaAreas->getElement();
        cout<<"-";
        a->toString();
        cout<<endl;
    }

    listaAreas->goToPos(p);
}

Area* getArea(string nombreArea){
    for(listaAreas->goToStart(); !listaAreas->atEnd(); listaAreas->next()){
        Area *a = listaAreas->getElement();
        if(a->getName()==nombreArea)
            return a;
    }
    throw runtime_error("Area no encontrada");

}

void DefaultServicios(){
    listaServicios = new DLinkedList<Servicio*>();
    listaServicios->append(new Servicio("Retiro", getArea("Cajas")));
    listaServicios->append(new Servicio("Déposito", getArea("Cajas")));
    listaServicios->append(new Servicio("Pagar recibo", getArea("Cajas")));
    listaServicios->append(new Servicio("Pagar marchamo", getArea("Cajas")));
    listaServicios->append(new Servicio("Cambiar cheque", getArea("Cajas")));
    listaServicios->append(new Servicio("Retirar tarjeta", getArea("Información")));
    listaServicios->append(new Servicio("Consulta", getArea("Información")));
    listaServicios->append(new Servicio("Inversiones", getArea("Empresarial")));
    listaServicios->append(new Servicio("Abrir cuenta", getArea("Servicio al Cliente")));

}
void printListaServicios(){
    int p;
    if(listaServicios->getPos() > 0 && listaServicios->getPos() < listaServicios->getSize())
        p = listaServicios->getPos();
    else
        p = 0;
    listaServicios->goToStart();
    cout<<"SERVICIOS"<<endl;
    for(int i = 0; i< listaServicios->getSize(); i++){

            Servicio *s = listaServicios->getElement();
            Area* areaService = s->getArea();
            cout<<i<<". "<<s->toString()<<" ["<<areaService->getCodigo()<<"]"<<endl;
            listaServicios->next();

    }
    listaServicios->goToPos(p);
}
//-----------------------------------------Menú-------------------
int main(){
    DefaultAreas();
    DefaultServicios();
    printListaServicios();
    listaServicios()->getElement();
    listaServicios->remove();

