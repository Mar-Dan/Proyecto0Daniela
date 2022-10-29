#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include "DLinkedList.h"
#include "Tiquete.h"
#include "Ventana.h"
//#include "Cliente.h"
#include "Servicio.h"
#include "Area.h"
//#include "ListaVentanillas.h"
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
    Tiquete* tiqueteN;

    servicio->addContadorT();
    numT = area->getContadorT();
    area->setContadorT();
    prefijo = area->getCodigo();
//    cout << prefijo << endl;

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
        tiqueteN = new Tiquete(prioridad, servicio, codigo);
        area->cola->insert(tiqueteN, prioridad);
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
    if (total < 1){
        thro
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
        ventana->getArea()->addClientes();

        return tiqueteAtendido;
}

//***********************************ADMINISTRACION******************************************

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
    Enter();
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
    cout<<("No existe un area con ese nombre")<<endl<<
    "Asegurese que las mayúsculas y minúsculas coincidan";
    return NULL;

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
    listaServicios->append(new Servicio("Abrir cuenta", getArea("Servicio al Cliente")));

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

void menuPrintVentanas(){
    Enter();
    listaAreas->goToStart();
    Area* local;
    int i = 0;
    cout << "Indique el número del área que desea consultar" << endl;
    while(!listaAreas->atEnd()){
        cout << i << ". " << listaAreas->getElement()->getCodigo() << endl;
        i++;
        listaAreas->next();
    }
    bool selec = false;
    while(!selec){
        try{
            cout << "Área a consultar: "; cin >> i;
            listaAreas->goToPos(i);
            local = listaAreas->getElement();
            selec = true;
        } catch(runtime_error e) {
            cout << "Selección inválida >:(" << endl << endl;
        }
    }
    Enter();
    local->getVentanillas()->goToStart();
    while(!local->getVentanillas()->atEnd()){
        cout << "Ventanilla: " << local->getVentanillas()->getElement()->getCodigo() << "\t Tiquetes dispensados: " << local->getContadorT() << endl;
        local->getVentanillas()->next();
    }
    string d;
    cout << "Presione enter para regresar al menú."; cin >> d;
    return;
}

int Administracion(){
    Enter();
    int op = 0;
    int opS=0;
    int poseOg;
    int p;
    int pNew;
    Servicio *s;
    while(op!=3){

        cout<<"1. Definir áreas"<<endl<<
        "2. Definir servicios disponibles"<<endl<<
        "3. Regresar"<<endl;
        cout<<"¿Que desea realizar, administardor? ";cin>>op;
        if(op==1){
            printListaAreas();
        }
        if(op==2){
            //Enter();
            while(opS!=5){
                    cout<<"1. Agregar servicio"<<endl<<
                    "2. Borrar servicio"<<endl<<
                    "3. Reordenar lista"<<endl<<
                    "4. Ver lista"<<endl<<
                    "5. Regresar"<<endl;

                    cout<<"¿Que desea hacer con la lista de servicios?"<<endl; cin>>opS;
                    //Agregar
                    if(opS==1){
                        string nombre;
                        string nombreArea;
                        cout<<"Escriba el nombre del servicio: "; cin>>nombre;
                        cout<<"Escribe el nombre del area del servicio: "; cin>>nombreArea;
                        listaServicios->append(new Servicio(nombre, getArea(nombreArea)));
                    }
                    //Borrar
                    if(opS==2){
                        poseOg = listaServicios->getPos();
                        cout<<"Escriba la posición en la lista del servicio a borrar: "; cin>>p;
                        listaServicios->goToPos(p);
                        s = listaServicios->getElement();
                        string name = s->getNombre();
                        listaServicios->remove();
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
                       cout<<"El servicio '"<<s->getNombre()<<"' se editó con éxito"<<endl;
                       listaServicios->goToPos(poseOg);
                    }
                    //Mostrar Lista
                    if(opS==4){
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
void Estadisticas(){
    int op = 0;
    while(op!=6){
        List<Tiquete*>* tiquetesTotal = toArray(listaAreas);
        Enter();
        cout<<"Menú de estadísticas"<<endl;
        cout<<"1. Tiempo de espera promedio por áreas"<<endl<<
        "2. Total de tiquetes dispensados por área"<<endl<<
        "3. Total de tiquetes atendidos por ventanilla"<<endl<<
        "4. Total de tiquetes dispensados por servicio"<<endl<<
        "5. Total de tiquetes preferenciales dispensados en todo el sistema"<<endl<<
        "6. Salir"<<endl;

        cout<<"Que desea realizar? "; cin>>op;
        if(op ==1){
            listaAreas->goToStart();
            Area* local;
            while(!listaAreas->atEnd()){
                local = listaAreas->getElement();
                cout << "Área: " << local->getCodigo() << "\t Tiempo de espera promedio: " << local->getTiempoPromedio() << endl;
                listaAreas->next();
            }
        }
        else if(op==2){
            listaAreas->goToStart();
            Area* local;
            while(!listaAreas->atEnd()){
                local = listaAreas->getElement();
                cout << "Área: " << local->getCodigo() << "\t Tiquetes dispensados: " << local->getContadorT() << endl;
                listaAreas->next();
            }
        }
        else if(op==3){
            menuPrintVentanas();
        }
        else if(op==4){
            listaServicios->goToStart();
            while(!listaServicios->atEnd()){
                cout << "Servicio: " << listaServicios->getElement()->getNombre() << "\t Tiquetes dispensados: " << listaServicios->getElement()->getTiqDados() << endl;
                listaServicios->next();
            }
        }
        else if(op==5)
            cout<<"Estadisticas"<<endl;
        else if(op>6 || op<=0)
            cout<<"Opcion no válida"<<endl;

    }
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
			Estadisticas();
		if(op>6 || op<=0)
			cout<<"Opcion no válida"<<endl;

	}
	cout<<"\nGracias por su vista"<<endl;
	return 0;


}
