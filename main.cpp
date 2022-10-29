#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include "LinkedPriorityQueue.h"
#include "DLinkedList.h"
#include "PriorityQueue.h"
#include "Tiquete.h"
#include "Ventana.h"
//#include "Cliente.h"
#include "Servicio.h"
#include "Area.h"
#include "Dictionary.h"

using namespace std;
List<Area*> *listaAreas;
List<Servicio*> *listaServicios;

void Enter(){
    system("CLS");

}
void VerEstadoDeColas(){cout<<"Estado colas";}
void SolicitarTiquete(Area* area, Servicio* servicio, int prioridad){
    int numT;
    string prefijo;
    string codigo;

    numT = area->getContadorT();
    prefijo = area->getCodigo();

    if (numT < 10){
        codigo = prefijo + "0" + to_string(numT);
    } else {
        if (numT > 99){
            throw runtime_error("Max ticket limit exceeded.");
        } else {
            codigo = prefijo + to_string(numT);
        }
    }
    if (!area->servicios->contains(servicio)) {
        string mensaje;
        cout << servicio << endl;
        mensaje = "Area " + area->getCodigo() + "does not attend " + servicio->getNombre();
        throw runtime_error(mensaje);
    } else {
        area->getCodigo();
    }
}

List<Tiquete*>* toArray(List<Area*>* listaAreas){
    int total = 0;
    Area* elemento;
    List<Tiquete*> *L;
    List<Tiquete*> *arrTiquetes;

    listaAreas->goToStart();
    while(!listaAreas->atEnd()){
        elemento = listaAreas->getElement();
        total += elemento->tiquetesAtendidos->getSize();
        listaAreas->next();
    }

    arrTiquetes = new ArrayList<Tiquete*>(total);

    listaAreas->goToStart();
    while(!listaAreas->atEnd()){
        elemento = listaAreas->getElement();
        L = elemento->tiquetesAtendidos;
        arrTiquetes->extends(L);
        listaAreas->next();
    }


    return arrTiquetes;
}

int getTiqPref(List<Tiquete*>* arrTiquetes){
    int preferenciales = 0;
    arrTiquetes->goToStart();
    while(!arrTiquetes->atEnd()){
        Tiquete* tiquete = arrTiquetes->getElement();
        arrTiquetes->next();
        if(tiquete->getPrioridad() == 0)
            preferenciales++;
    }
    return preferenciales;
}

Tiquete* atender(Ventana* ventana){
        Tiquete* tiqueteAtendido;
        if(ventana->getArea()->cola->isEmpty()){
                return NULL;
        } else {
            tiqueteAtendido = ventana->atender();
        }
        tiqueteAtendido->atenderTiquete(ventana);
        ventana->getArea()->tiquetesAtendidos->append(tiqueteAtendido);
        ventana->getArea()->tiempoT += tiqueteAtendido->getEspera();
        ventana->getArea()->setContadorT();

        return tiqueteAtendido;
}

//***********************************ADMINISTRACION******************************************

void DefaultAreas(){
    listaAreas = new DLinkedList<Area*>();
    Area* cajas = new Area();
    cajas->setName("Cajas");
    cajas->setCantidadVentanillas(5);
    Area* servicioAlCLiente = new Area();
    servicioAlCLiente->setName("Servicio al cliente");
    cajas->setCantidadVentanillas(3);
    Area* empresarial = new Area();
    empresarial->setName("Empresarial");
    empresarial->setCantidadVentanillas(2);
    Area* informacion = new Area();
    informacion->setName("Información");
    informacion->setCantidadVentanillas(1);
    listaAreas->append(cajas);
    listaAreas->append(servicioAlCLiente);
    listaAreas->append(empresarial);
    listaAreas->append(informacion);

}
void printListaAreas(){
    Enter();
    int i=0;
    int p = listaAreas->getPos();
    cout<<"AREAS:"<<endl;
    for(listaAreas->goToStart(); !listaAreas->atEnd(); listaAreas->next()){
        Area* a = listaAreas->getElement();
        cout<<i<<".";
        a->toString();
        cout<<endl;
        i++;
    }
    cout<<"\n";

    listaAreas->goToPos(p);
}

Area* getArea(string nombreArea){
    for(listaAreas->goToStart(); !listaAreas->atEnd(); listaAreas->next()){
        Area *a = listaAreas->getElement();
        if(a->getName()==nombreArea)
            return a;
    }
    cout<<("No existe un area con ese nombre")<<endl<<
    "Asegurese que las mayúsculas y minúsculas coincidan";
    return nullptr;

}
Area* crearArea(string nombre, int cantVentanillas){
    for(listaAreas->goToStart(); !listaAreas->atEnd();listaAreas->next()){
        Area *a = listaAreas->getElement();
        if(a->getName()==nombre){
            cout<<"Ya existe esta área"<<endl;
            return nullptr;
        }
    }
    Area* nArea = new Area(nombre, cantVentanillas);
    nArea->setCodigo();
    List<Ventana*>* listaVentanillas = new LinkedList<Ventana*>();
    for(int i = 0; i<cantVentanillas;i++)
        listaVentanillas->append(new Ventana(nArea));
    nArea->setVentanillas(listaVentanillas);
    nArea->setCantidadVentanillas(cantVentanillas);
    cout<<"Area creada exitosamente"<<endl;
    return nArea;
}
void DefaultServicios(){
    listaServicios = new DLinkedList<Servicio*>();
    listaServicios->append(new Servicio("Retiro", getArea("Cajas")));
    listaServicios->append(new Servicio("Depósito", getArea("Cajas")));
    listaServicios->append(new Servicio("Pagar recibo", getArea("Cajas")));
    listaServicios->append(new Servicio("Pagar marchamo", getArea("Cajas")));
    listaServicios->append(new Servicio("Cambiar cheque", getArea("Cajas")));
    listaServicios->append(new Servicio("Retirar tarjeta", getArea("Información")));
    listaServicios->append(new Servicio("Consulta", getArea("Información")));
    listaServicios->append(new Servicio("Inversiones", getArea("Empresarial")));
    listaServicios->append(new Servicio("Abrir cuenta", getArea("Servicio al cliente")));

}
bool checkServicio(string nameService){
    int p = listaServicios->getPos();
    for(listaServicios->goToStart();!listaServicios->atEnd();listaServicios->next()){
        Servicio *s = listaServicios->getElement();
        string nombreS = s->getNombre();
        if(nombreS == nameService)
            return true;
    }
    return false;
}
void deleteServicio(int i){
    cout<<"¿Cual servicio desea borrar? "; cin>>i;
    int origin = listaServicios->getPos();
    listaServicios->goToPos(i);
    listaServicios->remove();
    listaServicios->goToPos(origin);
    return;
}
void printListaServicios(){
    Enter();
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
    cout<<"\n";
    listaServicios->goToPos(p);
}

int Administracion(){
    Enter();
    int op = 0;
    int opS=0;
    int opA=0;
    int poseOg;
    int p;
    int pNew;
    Servicio *s;
    Area *a;
    while(op!=3){
        Enter();
        opS=0;
        opA=0;
        cout<<"1. Definir áreas"<<endl<<
        "2. Definir servicios disponibles"<<endl<<
        "3. Regresar"<<endl;
        cout<<"¿Que desea realizar, administardor? ";cin>>op;
        if(op==1){
            Enter();
            while(opA!=4){
                cout<<"1. Agregar area"<<endl<<
                    "2. Borrar"<<endl<<
                    "3. Ver lista"<<endl<<
                    "4. Regresar"<<endl<<
                    "¿Que desea hacer con la lista de áreas? "; cin>>opA;

                if(opA==1){
                    string nombreArea;
                    int cantVentanillas;
                    cout<<"Escriba el nombre del área: ";cin>>nombreArea;
                    cout<<"¿Cuantas ventanillas puede tener el área?"; cin>>cantVentanillas;
                    listaAreas->append(crearArea(nombreArea, cantVentanillas));

                }
                if(opA==2){
                    poseOg = listaAreas->getPos();
                    cout<<"Escriba la posición en la lista del servicio a borrar: "; cin>>p;
                    listaAreas->goToPos(p);
                    a = listaAreas->getElement();
                    string name = a->getName();
                    listaAreas->remove();
                    cout<<"Se removió el servicio '"<<name<<"'"<<endl;
                    listaAreas->goToPos(poseOg);
                }
                if(opA==3){
                    printListaAreas();
                }
                if(opA<=0 || opA>4){
                    Enter();
                    cout<<"Opcion no válida"<<endl;
                }
            }
        }
        if(op==2){
            Enter();
            while(opS!=5){
                    cout<<"1. Agregar servicio"<<endl<<
                    "2. Borrar servicio"<<endl<<
                    "3. Reordenar lista"<<endl<<
                    "4. Ver lista"<<endl<<
                    "5. Regresar"<<endl;

                    cout<<"¿Que desea hacer con la lista de servicios? "; cin>>opS;
                    //Agregar
                    if(opS==1){
                        string nombre;
                        string nombreArea;
                        cout<<"Escriba el nombre del servicio: "; cin>>nombre;
                        if(checkServicio(nombre)){
                            Enter();
                            cout<<"Ya existe un servicio del mismo nombre"<<endl;
                        }
                        else{
                            cout<<"Escribe el nombre del area del servicio: "; cin>>nombreArea;
                            listaServicios->append(new Servicio(nombre, getArea(nombreArea)));
                        }
                    }
                    //Borrar
                    if(opS==2){
                        poseOg = listaServicios->getPos();
                        cout<<"Escriba la posición en la lista del servicio a borrar: "; cin>>p;
                        listaServicios->goToPos(p);
                        s = listaServicios->getElement();
                        string name = s->getNombre();
                        listaServicios->remove();
                        Enter();
                        cout<<"Se removió el servicio '"<<name<<"'"<<endl;
                        listaServicios->goToPos(poseOg);
                    }
                    //Reaordenar elementos
                    if(opS==3){
                       poseOg = listaServicios->getPos();
                       cout<<"Escriba la posición en la lista del servicio a ordenar: "; cin>>p;
                       listaServicios->goToPos(p);
                       s = listaServicios->getElement();
                       listaServicios->remove();
                       cout<<"Escriba la posición en la lista que lo desea insertar: "; cin>>pNew;
                       listaServicios->goToPos(pNew);
                       listaServicios->insert(s);
                       Enter();
                       cout<<"El servicio '"<<s->getNombre()<<"' se editó con éxito"<<endl;
                       listaServicios->goToPos(poseOg);
                    }
                    //Mostrar Lista
                    if(opS==4){
                        Enter();
                        printListaServicios();

                    }
                    if(opS<=0 || opS>5){
                        cout<<"Opción no válida"<<endl;
                        cin.get();
                    }
            }

        }
        if(op<=0 || op>3){
            cout<<"Opción no válida"<<endl;
        }

    }
    return 0;
}
string Estadisticas(){
    return "helloo mrs. clown";
}
//-----------------------------------------Menú-------------------
int main(){
    int op = 0;
    DefaultAreas();
    listaAreas->goToStart();
    Area *a= listaAreas->getElement();
    a->toString();
    cout<<a->getCantidadVentanillas();
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
		if(op>6 || op<=0)
			cout<<"Opcion no válida"<<endl;

	}
	cout<<"\nGracias por su vista"<<endl;
	return 0;


}
