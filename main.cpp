//pruebaaaa
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
void printListAreas(List<Area*> *listaAreas){
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

void DefaultListaServicios(){
    //listaServicios = new DLinkedList<Servicio*>();
    listaServicios->append(new Servicio("Retiro", 'C');
    listaServicios->append(aeaea);
    listaServicios->append(new Servicio(generarNombreAleatorio(), area2));
    listaServicios->append(new Servicio(generarNombreAleatorio(), area));
}
void printListaServicios(List<Servicio*> *servicios){
    int p;
    if(servicios->getPos() > 0 && servicios->getPos() < servicios->getSize())
        p = servicios->getPos();
    else
        p = 0;
    servicios->goToStart();
    cout<<"SERVICIOS"<<endl;
    for(int i = 0; i< servicios->getSize(); i++){

            Servicio *s = servicios->getElement();
            Area* areaService = s->getArea();
            cout<<i<<". "<<s->toString()<<" ["<<areaService->getCodigo()<<"]"<<endl;
            servicios->next();

    }
    servicios->goToPos(p);
}
List<Area*> *listaAreas = DefaultAreas();
//-----------------------------------------Menú-------------------
int main(){
    DefaultAreasYServicios(List<Area*> *listaAreas, List<Servicio*> *listServicios);

}
