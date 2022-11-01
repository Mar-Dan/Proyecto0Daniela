#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <ios>
#include <limits>
#include <stdio.h>
#include <locale.h>
#include <windows.h>

#include "LinkedPriorityQueue.h"
#include "PriorityQueue.h"
#include "DLinkedList.h"
#include "Tiquete.h"
#include "Ventana.h"
#include "Servicio.h"
#include "Area.h"

/*Anthony Camacho y Maria Daniela Chaves
Main del Proyecto 0:
Incluye métodos para:
1. Ver los tiquetes esperando en cada cola por area.
2. Solicitar un tiquete como cliente, al que
se le asigna un area, un servicio y una prioridad.
3. Atender los tiquetes en espera y verificar si las
colas están vacías.
4. Como administrador configurar los servicios (agregar,
eliminar y reacomodar) y areas (agregar y eliminar)
5. Ver estadisticas de tiempo de espera, tiquetes
dispensados por area y servicio, tiquetes atendidos por
ventana, total de tiquetes preferenciales*/

using namespace std;
List<Area*> *listaAreas;
List<Servicio*> *listaServicios;

int readNumber(string error_message) {

    int result;

    while (!(cin >> result)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << error_message << std::endl;
    }

    return result;
}

int generarNumero(int tope){
    int r = rand() % tope;
    return r;
}

int readNumber(string error_message) {
    //Método de Saurabh Dhage, obtenido de su respuesta en StackOverflow
//https://stackoverflow.com/questions/69735621/the-best-way-to-capture-user-input-int-with-error-handling-loop#:~:text=0-,Reading,-from%20a%20stream

    int result;

    while (!(cin >> result)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << error_message << std::endl;
    }

    return result;
}

void Enter(){
    system("CLS");
}

Tiquete* SolicitarTiquete(Area* area, Servicio* servicio, int prioridad){
    /**
    Función para crear un tiquete nuevo, asociarlo a la cola de su respectiva
    área y agregar el tiquete a los parámetros de cada objeto que precisa saber
    cuántos tiquetes relacionados a sí mismo se han emitido.
    **/
    int numT;
    string prefijo;
    string codigo;
    Tiquete* tiqueteN;

    servicio->addTiqDados();
    numT = area->getContadorT();
    area->setContadorT();
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
        for(area->servicios->goToStart(); !area->servicios->atEnd(); area->servicios->next()){
            cout << area->servicios->getElement()->getNombre() << ", ";
        }
        cout << endl << servicio->getNombre() << endl;
        string mensaje = "Area " + area->getName() + " does not attend " + servicio->getNombre();
        throw runtime_error(mensaje);
    } else {
        tiqueteN = new Tiquete(prioridad, servicio, codigo);
        area->cola->insert(tiqueteN, prioridad);
    }
    return tiqueteN;
}

List<Tiquete*>* toArray(List<Area*>* listaAreas){
    /**
    Función para crear una ArrayList con los tiquetes atendidos de todas las
    áreas.
    **/
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
        throw runtime_error("No elements to make an ArrayList.");
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
    /**
    Función para obtener la cantidad de tiquetes con prioridad 0 en un ArrayList
    de punteros a tiquetes. Devuelve el resultado del conteo.
    **/
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
    /**
    Función para manipular un tiquete y sus objetos asociados, de tal manera que
    se almacene como un tiquete que ya no puede se atendido.
    **/
    Tiquete* tiqueteAtendido;
    if(ventana->getArea()->cola->isEmpty()){
            return nullptr;
    } else {
        tiqueteAtendido = ventana->atender();
    }
    tiqueteAtendido->atenderTiquete(ventana);
    ventana->getArea()->tiquetesAtendidos->append(tiqueteAtendido);
    ventana->getArea()->tiempoT += tiqueteAtendido->getEspera();
    ventana->getArea()->addClientes();

    return tiqueteAtendido;
}

//******************************ADMINISTRACIÓN**********************************

Area* getArea(string codeArea){
    for(listaAreas->goToStart(); !listaAreas->atEnd(); listaAreas->next()){
        Area *a = listaAreas->getElement();
        if(a->getName()==codeArea)
            return a;
    }
    cout<<("No existe un área con ese nombre")<<endl<<
    "Asegúrese que las mayúsculas y minúsculas coincidan"<<endl;
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
    Enter();
    cout<<"Área creada exitosamente"<<endl;
    return nArea;
}
void DefaultAreas(){
    listaAreas = new DLinkedList<Area*>();

    Area* cajas = crearArea("Cajas", 5);

    Area* servicioAlCLiente = crearArea("Servicio al cliente", 3);

    Area* empresarial = crearArea("Empresarial", 2);

    Area* informacion = crearArea("Información", 1);

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
    for(listaServicios->goToStart();!listaServicios->atEnd();listaServicios->next()){
        Servicio *s = listaServicios->getElement();
        string nombreS = s->getNombre();
        if(nombreS == nameService)
            return true;
    }
    return false;
}
void deleteServicio(int i){
    cout<<"¿Cuál servicio desea borrar? "; cin>>i;
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

void printCola(PriorityQueue<Tiquete*>* C){
    /**
    Método para mostrar en pantalla las colas de la lista C.
    Debido a que C es un puntero a una lista de punteros, se saca cada objeto de
    la cola para mostrar su nombre y se inserta en otra lista, para repetir el
    proceso al revés, de tal manera que la cola a la que apunta C no quede vacía
    **/
    PriorityQueue<Tiquete*>* cola = new LinkedPriorityQueue<Tiquete*>(2);

    bool enPrioridad = true;
    Tiquete* tiqLocal;
    cout << "Cola de prioridad: [ ";
    while(!C->isEmpty()){
        tiqLocal = C->removeMin();
        if(enPrioridad){
            if(tiqLocal->getPrioridad() != 0){
                enPrioridad = false;
                cout << " ]\nCola ordinaria: [ ";
            }
        }
        cout << tiqLocal->getCodigo() << ", ";
        cola->insert(tiqLocal, tiqLocal->getPrioridad());
    }
    cout << " ]" << endl;
    while(!cola->isEmpty()){
        tiqLocal = cola->removeMin();
        C->insert(tiqLocal, tiqLocal->getPrioridad());
    }
}

void VerEstadoDeColas(){
    /**
    Método para mostrar en pantalla el estado de las colas de todas las áreas.
    **/
    string foo;
    cout << "Estado de colas:" << endl;
    for(listaAreas->goToStart(); !listaAreas->atEnd(); listaAreas->next()){
        cout << "Área:\t" << listaAreas->getElement()->getName() << "\t\tCantidad de ventanillas: " << listaAreas->getElement()->getCantidadVentanillas() << endl;
        printCola(listaAreas->getElement()->cola);
        cout << endl << endl;
    }
    cout << "Ingrese cualquier número para continuar"; cin >> foo;
}
void menuPrintVentanas(){
    /**
    Método para mostrar en pantalla el menú para consultar los tiquetes atendidos
    por ventana a través de su respectiva área.
    **/
    Enter();
    listaAreas->goToStart();
    Area* local;
    int i = 0;
    cout << "Indique el número del Área que desea consultar" << endl;
    while(!listaAreas->atEnd()){
        cout << i << ". " << listaAreas->getElement()->getCodigo() << endl;
        i++;
        listaAreas->next();
    }
    bool selec = false;
    while(!selec){
        try {
            cout << "Área a consultar: "; cin >> i;
            listaAreas->goToPos(i);
            local = listaAreas->getElement();
            selec = true;
        } catch(runtime_error &) {
            cout << "Selección inválida >:(" << endl << endl;
        }
    }
    Enter();
    local->getVentanillas()->goToStart();
    while(!local->getVentanillas()->atEnd()){
        cout << "Ventanilla: " << local->getVentanillas()->getElement()->getCodigo() << "\tTiquetes atendidos: " << local->getVentanillas()->getElement()->getTiquetesAtendidos() << endl;
        local->getVentanillas()->next();
    }
//    string d;
//    cout << "Ingrese cualquier número para regresar al menú."; cin >> d;
    return;
}
void menuAtender(){
    /**
    Método para mostrar en pantalla el menú para atender un tiquete en la
    ventanilla que le corresponde a quien opere el programa
    **/
    Area* local;
    int i = 0;
    cout << "Indique el número del Área a la que pertenece" << endl;
    listaAreas->goToStart();
    while(!listaAreas->atEnd()){
        cout << i << ". " << listaAreas->getElement()->getName() << endl;
        i++;
        listaAreas->next();
    }
    bool selec = false;
    while(!selec){
        try {
            cout << "Su área: "; cin >> i;
            listaAreas->goToPos(i);
            local = listaAreas->getElement();
            selec = true;
            i = 0;
        } catch(runtime_error &) {
            cout << "Selección inválida >:(" << endl << endl;
        }
    }
    Enter();
    local->ventanillas->goToStart();
    cout << "Indique el número de la ventanilla en la que atiende" << endl;
    local->ventanillas->goToStart();
    while(!local->ventanillas->atEnd()){
        cout << i << ". " << local->ventanillas->getElement()->getCodigo() << endl;
        i++;
        local->ventanillas->next();
    }
    Ventana* ventanaLocal;
    selec = false;
    while(!selec){
        try {
            cout << "Su ventanilla: "; cin >> i;
            local->ventanillas->goToPos(i);
            ventanaLocal= local->ventanillas->getElement();
            selec = true;
        } catch(runtime_error &) {
            cout << "Selección inválida >:(" << endl << endl;
        }
    }
    i = 1;
    while (i == 1){
        if (ventanaLocal->getArea()->cola->isEmpty()){
            cout << "La cola de tiquetes está vacía. Presione cualquier número para salir al menú principal "; cin >> i;
            i = 0;
        } else {
            Tiquete* tiqueteAtendido = atender(ventanaLocal);
            cout << "Tiquete [" << tiqueteAtendido->getCodigo() << "] ha sido atendido."
            << endl << "Presione 1 para seguir atendiendo o cualquier otro número para salir al menú principal "; cin >> i;
        }
    }
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
        cout<<"1. Definir Áreas"<<endl<<
        "2. Definir servicios disponibles"<<endl<<
        "3. Regresar"<<endl;
        cout<<"¿Qué desea realizar, administardor? ";cin>>op;
        if(op==1){
            Enter();
            while(opA!=4){
                cout<<"1. Agregar area"<<endl<<
                    "2. Borrar"<<endl<<
                    "3. Ver lista"<<endl<<
                    "4. Regresar"<<endl<<
                    "¿Qué desea hacer con la lista de áreas? "; cin>>opA;

                if(opA==1){
                    string nombreArea;
                    int cantVentanillas;
                    cout<<"Escriba el nombre del área: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, nombreArea);
                    cout<<"¿Cuántas ventanillas puede tener el área? "; cin>>cantVentanillas;
                    listaAreas->append(crearArea(nombreArea, cantVentanillas));

                }
                if(opA==2){
                    poseOg = listaAreas->getPos();
                    cout<<"Escriba la posición en la lista del area a borrar: "; cin>>p;
                    if(p<0||p>listaAreas->getSize()){
                        Enter();
                        cout<<"Opción no válida"<<endl;
                    }else{
                        listaAreas->goToPos(p);
                        a = listaAreas->getElement();
                        string name = a->getName();
                        listaAreas->remove();
                        Enter();
                        cout<<"Se removió el servicio '"<<name<<"'"<<endl;
                        listaAreas->goToPos(poseOg);
                    }
                }
                if(opA==3){
                    printListaAreas();
                }
                if(opA<=0 || opA>4){
                    Enter();
                    cout<<"Opción no válida"<<endl;
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

                    cout<<"¿Qué desea hacer con la lista de servicios? ";
                    opS = readNumber("Opción no válida");
                    //Agregar
                    if(opS==1){
                        string nombre;
                        string nombreArea;
                        cout<<"Escriba el nombre del servicio: ";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        getline(cin, nombre);
                        if(checkServicio(nombre)){
                            Enter();
                            cout<<"Ya existe un servicio del mismo nombre"<<endl;
                        }
                        else{
                            cout<<"Escribe el nombre del área del servicio: ";
                            //cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            getline(cin, nombreArea);
                            listaServicios->append(new Servicio(nombre, getArea(nombreArea)));
                        }
                    }
                    //Borrar
                    if(opS==2){
                        poseOg = listaServicios->getPos();
                        cout<<"Escriba la posición en la lista del servicio a borrar: "; cin>>p;
                        if(p<0||p>listaServicios->getSize()){
                            Enter();
                            cout<<"Opción no válida"<<endl;
                        } else{
                            listaServicios->goToPos(p);
                            s = listaServicios->getElement();
                            string name = s->getNombre();
                            listaServicios->remove();
                            Enter();
                            cout<<"Se removió el servicio '"<<name<<"'"<<endl;
                            listaServicios->goToPos(poseOg);
                            }
                    }
                    //Reaordenar elementos
                    if(opS==3){
                       poseOg = listaServicios->getPos();
                       cout<<"Escriba la posición en la lista del servicio a ordenar: "; cin>>p;
                       if(p<0||p>listaServicios->getSize()){
                        Enter();
                        cout<<"Opción no válida"<<endl;
                       }
                       else{
                           listaServicios->goToPos(p);
                           s = listaServicios->getElement();
                           listaServicios->remove();
                           cout<<"Escriba la posición en la lista que lo desea insertar: "; cin>>pNew;
                           if(pNew<0 ||pNew>listaServicios->getSize()){
                            Enter();
                            cout<<"Opción no válida"<<endl;
                           }
                           else{
                               listaServicios->goToPos(pNew);
                               listaServicios->insert(s);
                               Enter();
                               cout<<"El servicio '"<<s->getNombre()<<"' se editó con éxito"<<endl;
                               listaServicios->goToPos(poseOg);
                           }
                       }
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
//******************************************ESTADISTICAS********************************************
void Estadisticas(){
    /**
    Método para mostrar en pantalla el menú de estadísticas
    **/
    int op = 0;
    string foo;
    while(op!=6){
        Enter();
        cout<<"Menú de estadísticas"<<endl;
        cout<<"1. Tiempo de espera promedio por áreas"<<endl<<
        "2. Total de tiquetes dispensados por área"<<endl<<
        "3. Total de tiquetes atendidos por ventanilla"<<endl<<
        "4. Total de tiquetes dispensados por servicio"<<endl<<
        "5. Total de tiquetes preferenciales dispensados en todo el sistema"<<endl<<
        "6. Salir"<<endl;

        cout<<"¿Qué desea realizar? ";
        op = readNumber("Opción no válida");
        if(op ==1){
            listaAreas->goToStart();
            Area* local;
            while(!listaAreas->atEnd()){
                local = listaAreas->getElement();
                cout << "Área: " << local->getCodigo() << "\t Tiempo de espera promedio: " << local->getTiempoPromedio() << endl;
                listaAreas->next();
            }
            cout << "Ingrese cualquier número para continuar "; cin >> foo;
        }
        else if(op==2){
            listaAreas->goToStart();
            Area* local;
            while(!listaAreas->atEnd()){
                local = listaAreas->getElement();
                cout << "Área: " << local->getCodigo() << "\t Tiquetes dispensados: " << local->getContadorT() << endl;
                listaAreas->next();
            }
            cout << "Ingrese cualquier número para continuar "; cin >> foo;
        }
        else if(op==3){
            menuPrintVentanas();
            cout << "Ingrese cualquier número para continuar "; cin >> foo;
        }
        else if(op==4){
            listaServicios->goToStart();
            while(!listaServicios->atEnd()){
                cout << "Servicio: " << listaServicios->getElement()->getNombre() << "\t Tiquetes dispensados: "
                        << listaServicios->getElement()->getTiqDados() << endl;
                listaServicios->next();
            }
            cout << "Ingrese cualquier número para continuar "; cin >> foo;
        }
        else if(op==5){
            List<Tiquete*>* tList = toArray(listaAreas);
            cout<<"Estadísticas"<<endl;
            cout << "Total de tiquetes preferenciales dispensados: " << getTiqPref(tList) << endl;
            cout << "Ingrese cualquier número para continuar "; cin >> foo;
        }
        else if(op>6 || op<=0)
            cout<<"Opcion no válida"<<endl;

    }
}
void menuSolicitarTiquete(){
    /**
    Método para mostrar en pantalla el menú para solicitar un tiquete de manera
    cómoda y separada del menú principal.
    **/
    int e = listaServicios->getSize();
    int op = 0;
    Tiquete* nTiquete;
    printListaServicios();
    cout << "Seleccione en cuál servicio desea que le atiendan: ";
    op = readNumber("Opción no válida");
    if(op >= 0 && op < e){
        listaServicios->goToPos(op);
        cout << "¿Desea que le atiendan en " << listaServicios->getElement()->getNombre()
        << " ?" << endl << "(1/0): "; cin >> op;
        if(op == 1){
            cout << "¿Usted es cliente preferencial?" << endl << "(1/0): "; cin >> op;
            if (op != 0 && op != 1){
                cout << "Valor ingresado inválido. Realice el proceso nuevamente."
                << endl << endl << "Ingrese 0 para continuar ";
                op = readNumber("Opción no válida");
                menuSolicitarTiquete();
            } else if(op == 1){
                Area* areaT = listaServicios->getElement()->getArea();
                Servicio* servicioT = listaServicios->getElement();
                nTiquete = SolicitarTiquete(areaT, servicioT, 0);
            } else {
            Area* areaT = listaServicios->getElement()->getArea();
            Servicio* servicioT = listaServicios->getElement();
            nTiquete = SolicitarTiquete(areaT, servicioT, 1);
            }
        } else {
            if (op == 0){
                cout << "Ingrese 0 para continuar";
            } else {
                cout << "Valor ingresado inválido. Realice el proceso nuevamente."
                << endl << endl << "Ingrese 0 para continuar ";
            }
            op = readNumber("Opción no válida");
            Enter();
            menuSolicitarTiquete();
        }
        cout << "Tiquete solicitado exitosamente. El código de su tiquete es: " << nTiquete->getCodigo()
                << ", y se le atenderá en el área " << nTiquete->getServicio()->getArea()->getName() << endl
                    << "Ingrese cualquier número para continuar: "; cin >> op;
        op = 0;
    } else {
        cout << "Valor ingresado inválido. Realice el proceso nuevamente."
        << endl << endl << "Ingrese 0 para continuar ";
        op = readNumber("Opción no válida");
        Enter();
        menuSolicitarTiquete();
    }
}
//----------------------------Funciones de testeo-------------------------------

void runTestEmitirTiquetes(int nTiquetes){
    /**
    Función para simular la emisión de tiquetes de manera aleatoria.
    El parámetro nTiquetes indica cuántos tiquetes se emitirán
    **/
    int areas = listaAreas->getSize();
    Area* area;
    for(int i = 0; i < nTiquetes; i++){
            listaAreas->goToPos(generarNumero(areas));
            area = listaAreas->getElement();
            area->servicios->goToPos(generarNumero(area->servicios->getSize()));
            SolicitarTiquete(area, area->servicios->getElement(), generarNumero(2));
    }

}

void runTestAtenderTiquetes(int nTiquetes){
    /**
    Función para simular atender tiquetes de manera aleatoria.
    El parámetro nTiquetes recibe la cantidad de tiquetes que se atenderán
    **/
    int areas = listaAreas->getSize();
    Area* area;
    for(int i = 0; i < nTiquetes; i++){
            listaAreas->goToPos(generarNumero(areas));
            area = listaAreas->getElement();
            area->ventanillas->goToPos(generarNumero(area->ventanillas->getSize()));
            if(atender(area->ventanillas->getElement()) == nullptr)
                i--;
    }
}
//____________________________________Menú______________________________________


int main(){
    SetConsoleOutputCP( 65001 );
    int op = -1;
    DefaultAreas();
    listaAreas->goToStart();
    Area *a= listaAreas->getElement();
    a->toString();
    cout<<a->getCantidadVentanillas();
    DefaultServicios();

    while(op < 0 || op > 1){
        Enter();
        cout << "Iniciar el programa con tiquetes de prueba?" << endl << "(1/0): ";
        op = readNumber("Opción no válida");
        if(op == 1){
            op = -1;
            while(op < 1 || op > 100){
                cout << "Ingrese la cantidad de tiquetes que desea crear: ";
                op = readNumber("Opción no válida");
                if(op > 1 && op <= 100)
                    runTestEmitirTiquetes(op);
            }
            int tope = op;
            op = -1;
            while(op < 1 || op > tope){
                cout << "Ingrese la cantidad de tiquetes que desea atender: ";
                op = readNumber("Opción no válida");
                if(op > 1 && op <= tope)
                    runTestAtenderTiquetes(op);
            }
            op = 1;
        }
    }
    op = -1;
    Enter();
//    cout << toArray(listaAreas)->getSize() << endl;

    while(op!=6){
        cout<<"Bienvenid@"<<endl;
        cout<<"1. Ver estados de colas"<<endl<<
        "2. Solicitar tiquete"<<endl<<
        "3. Atender"<<endl<<
        "4. Administración"<<endl<<
        "5. Estadísticas"<<endl<<
        "6. Salir"<<endl;

		cout<<"Qué desea realizar? ";
        op = readNumber("Opción no válida");


		if(op ==1)
			VerEstadoDeColas();
		if(op==2){
            Enter();
			menuSolicitarTiquete();
        }
		if(op==3){
            Enter();
            menuAtender();
		}
		if(op==4)
			Administracion();
		if(op==5)
			Estadisticas();
		if(op>6 || op<=0)
			cout<<"Opción no válida"<<endl;
        Enter();
	}
	cout<<"\nGracias por su visita"<<endl;
	return 0;

}
