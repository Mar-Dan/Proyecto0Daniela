#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <string>
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

void Enter(){
    int i =0;
    while(i!=50){
        cout<<endl;
        i++;
    }
}
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
void printListaAreas(){
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
int printListaServicios(){
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
    return 2;
}
void VerEstadoDeColas(){cout<<"Estado colas";}
void SolicitarTiquete(){}
void Atender(){}
int Administracion(){
    int op = 0;
    Enter();
    cout<<"1. Definir áreas"<<endl<<
        "2. Definir servicios disponibles"<<endl<<
        "3. Regresar"<<endl<<
        "¿Que desea realizar? ";
    cin>>op;
    while(op!=3){
        if(op==1){
            printListaAreas();
        }
        if(op==2){
            op = printListaServicios();
        }
        if(op<0 || op>3){
            cout<<"Opción no válida"<<endl;
        }
    }
    cout<<"ADioooo";
    return 0;
}
string Estadisticas(){
    return "helloo mrs. clown";
}
//-----------------------------------------Menú-------------------
int main(){
    int op = 0;
    DefaultAreas();
    DefaultServicios();
    while(op!=6){
        Enter();
        cout<<"Bienvenid@"<<endl;
        cout<<"1. Ver estados de colas"<<endl<<
        "2. Solicitar tiquete"<<endl<<
        "3. Atender"<<endl<<
        "4. Administración"<<endl<<
        "5. Estadísticas"<<endl<<
        "6. Salir"<<endl;

		cout<<"Que desea realizar? "; cin>>op;
		if(op ==1)
			cout<<"VerEstadoDeCola();"<<endl;
		if(op==2)
			cout<<"SolicitarTiquete();"<<endl;
		if(op==3)
			cout<<"Atender"<<endl;
		if(op==4)
			Administracion();
		if(op==5)
			cout<<"Estadisticas"<<endl;
		if(op>6 || op<0)
			cout<<"Opcion no válida"<<endl;

	}
	cout<<"\nGracias por su vista"<<endl;
	return 0;


}
