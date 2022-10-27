//string generarNumero2(){
//    int r = rand();
//    while(r<1000 || r>9999)
//        r = rand();
//    string str = to_string(r);
//    return str;
//}

///*LinkedPriorityQueue<string>**/ int mainy(){
//    int clientePrioridad;
//    LinkedPriorityQueue<string> *clientes = new LinkedPriorityQueue<string>(2);
//    Cliente *cliente = new Cliente();
//    for(int i = 0; clientes->getSize()<5; i++){
//        cout<<"Usted es cliente con prioridad? Si(0) No(1) "<<endl;
//        cin>>clientePrioridad;
//        if (clientePrioridad==0){
//            cliente->setPriority(clientePrioridad);
//            cliente->setCodigo();
//            clientes->insert(cliente->getCodigo(), cliente->getPriority());
//
//        }
//        if(clientePrioridad ==1){
//            cliente->setPriority(clientePrioridad);
//            cliente->setCodigo();
//            clientes->insert(cliente->getCodigo(), cliente->getPriority());
//        }
//        clientes->print();
//    }
//    /*cout<<"Modo empleado"<<endl;
//    while(!clientes->isEmpty()){
//        cout<<"Removiendo "<<clientes->removeMin()<<endl;
//        clientes->print();
//    }*/
//    //return clientes;
//    return 0;
//}
//
//void construirArea(){
//
//}
//
//Ventana* CodeVentanillas(Area *area, int i){
//    Ventana *v = new Ventana();
//    v->setCodigo(area, i);
//    return v;
//}
//int main3(){ //En este main se hizo una PriorityQueue<string> para sacar los nombres de una lista de punteros.
//    LinkedPriorityQueue<string> *clientes = new LinkedPriorityQueue<string>(2);
//    Area *area= new Area();
//    Ventana *v = new Ventana();
//    area->setName("Empresas");
//    string a = area->getName();
//    area->setCodigo();
//    area->setCantidadVentanillas(5);
//    List<Ventana*> *L = area->getVentanillas();
//    for(int i = 0; i<area->getCantidadVentanillas(); i++){
//        L->append(CodeVentanillas(area, i));
//    }
//    cout<<"\n";
//    L->print();
//    L->goToStart();
//    cout<<"[ ";
//    for(L->goToStart(); !L->atEnd(); L->next()){
//        Ventana *e = L->getElement();
//        cout<<e->getCodigo();
//    }
//    cout<<"]"<<endl;
//
//    //Atender: No funciona
//    /*int clientePrioridad;
//    Tiquete *cliente = new Tiquete();
//    for(int i = 0; i<5; i++){
//        cout<<"Usted es cliente con prioridad? Si(0) No(1) "<<endl;
//        cin>>clientePrioridad;
//        if (clientePrioridad==0){
//            cliente->setPriority(clientePrioridad);
//            cliente->setCodigo();
//            clientes->insert(cliente->getCodigo(), cliente->getPriority());
//
//        }
//        if(clientePrioridad ==1){
//            cliente->setPriority(clientePrioridad);
//            cliente->setCodigo();
//            clientes->insert(cliente->getCodigo(), cliente->getPriority());
//        }
//        clientes->print();
//    }*/
//    return 0;
//}
//
////--------------------------------Domingo, 22 octubre-----------------------------------------------------------
//
//void generarTiquete(Area* area, Servicio* servicio, int prioridad){
//    int numT;
//    string prefijo;
//    string codigo;
//
//    numT = area->getContadorT();
//    int auxNum=numT+1;
//    prefijo = area->getCodigo();
//
//    if (numT < 10){
//        codigo = prefijo + "0" + to_string(numT);
//    } else {
//        if (numT > 99){
//            throw runtime_error("Max ticket limit exceeded.");
//        } else {
//            codigo = prefijo + to_string(numT);
//        }
//    }
//
//    if (!area->getServicios()->contains(servicio)) {
//        string mensaje;
//        cout << servicio << endl;
//        mensaje = "Area " + area->getCodigo() + "does not attend " + servicio->getNombre();
//        throw runtime_error(mensaje);
//    } else {
//        area->tiquetesAtendidos->append(new Tiquete(prioridad, servicio, codigo));
//    }
//    area->setContadorT();
//}
//
//
//List<Tiquete*>* toArray(List<Area*>* listaAreas){
//    int total = 0;
//    Area* elemento;
//    List<Tiquete*> *L;
//    List<Tiquete*> *arrTiquetes;
//
//    listaAreas->goToStart();
//    while(!listaAreas->atEnd()){
//        elemento = listaAreas->getElement();
//        total += elemento->tiquetesAtendidos->getSize();
//        listaAreas->next();
//    }
//
//    arrTiquetes = new ArrayList<Tiquete*>(total);
//
//    listaAreas->goToStart();
//    while(!listaAreas->atEnd()){
//        elemento = listaAreas->getElement();
//        L = elemento->tiquetesAtendidos;
//        arrTiquetes->extends(L);
//        listaAreas->next();
//    }
//
//
//    return arrTiquetes;
//}
//void printListAreas(List<Area*> *listaAreas){
//    int p = listaAreas->getPos();
//    cout<<"AREAS:"<<endl;
//    for(listaAreas->goToStart(); !listaAreas->atEnd(); listaAreas->next()){
//        Area* a = listaAreas->getElement();
//        cout<<"-";
//        a->toString();
//        cout<<endl;
//    }
//
//    listaAreas->goToPos(p);
//}
//void printListaTiquetes(List<Tiquete*> *arrayTiquete){
//    int p = arrayTiquete->getPos();
//    cout<<"[";
//    for(arrayTiquete->goToStart(); !arrayTiquete->atEnd(); arrayTiquete->next()){
//        Tiquete* t = arrayTiquete->getElement();
//        t->toString();
//    }
//    cout<<"]"<<endl;
//    arrayTiquete->goToPos(p);
//}
//
//void printListaServicios(List<Servicio*> *servicios){
//    int p = servicios->getPos();
//    servicios->goToStart();
//    cout<<"SERVICIOS"<<endl;
//    for(int i = 0; i< servicios->getSize(); i++){
//
//            Servicio *s = servicios->getElement();
//            Area* areaService = s->getArea();
//            cout<<i<<". "<<s->toString()<<" ["<<areaService->getCodigo()<<"]"<<endl;
//            servicios->next();
//
//    }
//    servicios->goToPos(p);
//}
//
//int mainT(){
//    List<Servicio*> *listaServicios = new DLinkedList<Servicio*>();
//    List<Area*> *listaAreas = new DLinkedList<Area*>();
//    List<Tiquete*> *arregloTiquetes;
//
//    Area* areaEmpresas = new Area();
//    areaEmpresas->setName("Empresas");
//    Area* areaServicioAlCliente = new Area();
//    areaServicioAlCliente->setName("Servicio al cliente");
//    Servicio* aeaea = new Servicio("Vean Aggretsuko", areaEmpresas);
//    listaServicios->append(new Servicio("0mg", areaServicioAlCliente));
//    listaServicios->append(aeaea);
//    listaServicios->append(new Servicio("Ayy LMAO", areaEmpresas));
//    listaServicios->append(new Servicio("ROFLMAO", areaServicioAlCliente));
//    listaServicios->print();
//    areaEmpresas->servicios = listaServicios;
//    listaAreas->append(areaEmpresas);
//    areaServicioAlCliente->servicios = listaServicios;
//    listaAreas->append(areaServicioAlCliente);
//
//    printListAreas(listaAreas);
//    printListaServicios(listaServicios);
//
//
//    for(int i = 0; i < 80; i++){
//            generarTiquete(listaAreas->getElement(), aeaea, 1);
//    }
//    for(int i = 0; i < 50; i++){
//            listaAreas->goToStart();
//            listaAreas->next();
//            generarTiquete(listaAreas->getElement(),aeaea, 1);
//    }
//
//    arregloTiquetes = toArray(listaAreas);
//
//    printListaTiquetes(arregloTiquetes);
//
//    cout << listaServicios->contains(aeaea);
//
//    cout<<"\n";
//    cout<<"[ ";
//    for(arregloTiquetes->goToStart(); !arregloTiquetes->atEnd(); arregloTiquetes->next()){
//        Tiquete *e = arregloTiquetes->getElement();
//        cout<<e->getCodigo()+" ";
//    }
//    cout<<"]"<<endl;
//    return 0;
//}
////----------------------------------------------Lunes 24--------------------------------
///*int generarNumero(){
//    int r = rand();
//    return (r % 2);
//}
//
//void generarTiquete(Area* area, Servicio* servicio, int prioridad){
//    int numT;
//    string prefijo;
//    string codigo;
//    Tiquete* tiqueteN;
//
//    numT = area->getContadorT();
//    area->setContadorT();
//    prefijo = area->getCodigo();
//
//    if (numT < 10){
//        codigo = prefijo + "0" + to_string(numT);
//    } else {
//        if (numT > 99){
//            throw runtime_error("Max ticket limit exceeded.");
//        } else {
//            codigo = prefijo + to_string(numT);
//        }
//    }
//    if (!area->servicios->contains(servicio)) {
//        string mensaje;
//        cout << servicio << endl;
//        mensaje = "Area " + area->getCodigo() + "does not attend " + servicio->getNombre();
//        throw runtime_error(mensaje);
//    } else {
//        tiqueteN = new Tiquete(prioridad, servicio, codigo);
//        area->cola->insert(tiqueteN, prioridad);
//    }
//}
//
//Tiquete* atender(Ventana* ventana){
//        Tiquete* tiqueteAtendido;
//        if(ventana->getArea()->cola->isEmpty()){
//                return NULL;
//        } else {
//            tiqueteAtendido = ventana->getArea()->cola->removeMin();
//        }
//        tiqueteAtendido->atenderTiquete(ventana);
//        ventana->getArea()->tiquetesAtendidos->append(tiqueteAtendido);
//
//        return tiqueteAtendido;
//
//        string lastoCliente = t->min();
//        cout<<"Atendiendo a: "<<t->removeMin();
//
//        tiquetesAtendidos++;
//        return lastoCliente;
//
//}
//
//List<Tiquete*>* toArray(List<Area*>* listaAreas){
//    int total = 0;
//    Area* elemento;
//    List<Tiquete*> *L;
//    List<Tiquete*> *arrTiquetes;
//
//    listaAreas->goToStart();
//    while(!listaAreas->atEnd()){
//        elemento = listaAreas->getElement();
//        total += elemento->tiquetesAtendidos->getSize();
//        listaAreas->next();
//    }
//
//    arrTiquetes = new ArrayList<Tiquete*>(total);
//
//    listaAreas->goToStart();
//    while(!listaAreas->atEnd()){
//        elemento = listaAreas->getElement();
//        L = elemento->tiquetesAtendidos;
//        arrTiquetes->extends(L);
//        listaAreas->next();
//    }
//
//
//    return arrTiquetes;
//}
//
//float tiempoPromedio(Area* area){
//    Tiquete* nTiquete;
//    float promedio = 0;
//    List<Tiquete*>* tiquetes;
//    tiquetes = area->tiquetesAtendidos;
//    tiquetes->goToStart();
//    while(!tiquetes->atEnd()){
//        nTiquete = tiquetes->getElement();
//        promedio += nTiquete->espera;
//        tiquetes->next();
//    }
//    return promedio / area->tiquetesAtendidos->getSize();
//}
//
//void agregarVentana(Area* area){
//    area->addVentanilla(new Ventana(area));
//}
//
//void eliminarVentana(Area* area, Ventana* v){
//    Ventana* ventana = area->deleteVentanilla(v);
//    cout << ventana->getCodigo() << " eliminada.";
//}
//
//int main(){
//    List<Servicio*> *listaServicios = new DLinkedList<Servicio*>();
//    List<Area*> *listaAreas = new DLinkedList<Area*>();
//    List<Tiquete*> *arregloTiquetes;
//
//    Area* area = new Area();
//    Area* area2 = new Area();
//    area->addVentanilla(new Ventana(area));
//    area2->addVentanilla(new Ventana(area2));
//    Servicio* aeaea = new Servicio("Vean Aggretsuko");
//    listaServicios->append(new Servicio("0mg"));
//    listaServicios->append(aeaea);
//    listaServicios->append(new Servicio("Ayy LMAO"));
//    listaServicios->append(new Servicio("ROFLMAO"));
//    listaServicios->print();
//    area->servicios = listaServicios;
//    listaAreas->append(area);
//
//    area2->servicios = listaServicios;
//    listaAreas->append(area2);
//
//    for(int i = 0; i < 80; i++){
//            generarTiquete(listaAreas->getElement(), aeaea, generarNumero());
//    }
//    //listaAreas->goToStart();
//    listaAreas->next();
//    for(int i = 0; i < 50; i++){
//            generarTiquete(listaAreas->getElement(),aeaea, generarNumero());
//    }
//
//    area->cola->print();
//    cout << "__________________________" << endl;
//    area2->cola->print();
//    listaAreas->goToStart();
//
//    for(int i = 0; i < 80; i++){
//        Area *nArea;
//        List<Ventana*>* ventana;
//        nArea = listaAreas->getElement();
//        ventana = nArea->getVentanillas();
//        atender(ventana->getElement());
//    }
//    listaAreas->next();
//    for(int i = 0; i < 50; i++){
//        Area *nArea;
//        nArea = listaAreas->getElement();
//        atender(nArea->getVentanillas()->getElement());
//    }
//
//    arregloTiquetes = toArray(listaAreas);
//
//    printListaTiquetes(arregloTiquetes);
//
//    cout << tiempoPromedio(area) << endl;
//
//    cout << listaServicios->contains(aeaea);
//}*/
////--------------------------------Miercoles 26---------------------------
//
//int generarNumero(int tope){
//    int r = rand() % tope;
//    return r;
//}
//
//string generarNombreAleatorio(){
//    List<string>* adjetivo = new ArrayList<string>(12);
//    adjetivo->append("Evil_");
//    adjetivo->append("Simp_");
//    adjetivo->append("Big ass_");
//    adjetivo->append("Lil'");
//    adjetivo->append("Combatiente_");
//    adjetivo->append("Emo_");
//    adjetivo->append("Boomer_");
//    adjetivo->append("E-girl_");
//    adjetivo->append("Libtard_");
//    adjetivo->append("Sussy_");
//    adjetivo->append("Otaku_");
//    adjetivo->append("Incel_");
//
//    List<string>* sustantivo = new ArrayList<string>(12);
//    sustantivo->append("Toruño");
//    sustantivo->append("Crypto-bro");
//    sustantivo->append("Juan_Carlos_Chupapijas");
//    sustantivo->append("Man_pussy_destroyer");
//    sustantivo->append("Furry");
//    sustantivo->append("Conservador_en_lo_social");
//    sustantivo->append("Bingus");
//    sustantivo->append("Figueres");
//    sustantivo->append("Zoodrigo");
//    sustantivo->append("Cabro_Macabro");
//    sustantivo->append("Gacho");
//    sustantivo->append("PACLover");
//
//    string nombre;
//    adjetivo->goToPos(generarNumero(adjetivo->getSize()));
//    sustantivo->goToPos(generarNumero(sustantivo->getSize()));
//    nombre = adjetivo->getElement();
//    nombre += sustantivo->getElement();
//    nombre += "-" + to_string(generarNumero(12));
//    return nombre;
//}
//
////void printListaServicios(List<Servicio*> *servicios){
////    int p;
////    if(servicios->getPos() > 0 && servicios->getPos() < servicios->getSize())
////        p = servicios->getPos();
////    else
////        p = 0;
////    servicios->goToStart();
////    cout<<"SERVICIOS"<<endl;
////    for(int i = 0; i< servicios->getSize(); i++){
////
////            Servicio *s = servicios->getElement();
////            Area* areaService = s->getArea();
////            cout<<i<<". "<<s->toString()<<" ["<<areaService->getCodigo()<<"]"<<endl;
////            servicios->next();
////
////    }
////    servicios->goToPos(p);
////}
//
//void printListaTiquetes(List<Tiquete*> *arrayTiquete){
//    int p = arrayTiquete->getPos();
//    cout<<"[";
//    for(arrayTiquete->goToStart(); !arrayTiquete->atEnd(); arrayTiquete->next()){
//        Tiquete* t = arrayTiquete->getElement();
//        t->toString();
//    }
//    cout<<"]"<<endl;
//    arrayTiquete->goToPos(p);
//}
//
//void generarTiquete(Area* area, Servicio* servicio, int prioridad){
//    int numT;
//    string prefijo;
//    string codigo;
//    Tiquete* tiqueteN;
//
//    servicio->addTiqDados();
//    numT = area->getTiquetesRecibidos();
//    area->setClientes();
//    prefijo = area->getCodigo();
////    cout << prefijo << endl;
//
//    if (numT < 10){
//        codigo = prefijo + "0" + to_string(numT);
//    } else {
//        if (numT > 99){
//            throw runtime_error("Max ticket limit exceeded.");
//        } else {
//            codigo = prefijo + to_string(numT);
//        }
//    }
//    if (!area->servicios->contains(servicio)) {
//        string mensaje;
//        cout << servicio << endl;
//        mensaje = "Area " + area->getCodigo() + "does not attend " + servicio->getNombre();
//        throw runtime_error(mensaje);
//    } else {
//        tiqueteN = new Tiquete(prioridad, servicio, codigo);
//        area->cola->insert(tiqueteN, prioridad);
//    }
//}
//
//int getTiqPref(List<Tiquete*>* arrTiquetes){
//    int preferenciales = 0;
//    arrTiquetes->goToStart();
//    while(!arrTiquetes->atEnd()){
//        Tiquete* tiquete = arrTiquetes->getElement();
//        arrTiquetes->next();
//        if(tiquete->getPrioridad() == 0)
//            preferenciales++;
//    }
//    return preferenciales;
//}
//
//Tiquete* atender(Ventana* ventana){
//        Tiquete* tiqueteAtendido;
//        if(ventana->getArea()->cola->isEmpty()){
//                return NULL;
//        } else {
//            tiqueteAtendido = ventana->getArea()->cola->removeMin();
//        }
//        tiqueteAtendido->atenderTiquete(ventana);
//        ventana->getArea()->tiquetesAtendidos->append(tiqueteAtendido);
//        ventana->getArea()->tiempoT += tiqueteAtendido->getEspera();
//        ventana->getArea()->setContadorT();
//
//        return tiqueteAtendido;
///**
//        string lastoCliente = t->min();
//        cout<<"Atendiendo a: "<<t->removeMin();
//        tiquetesAtendidos++;
//        return lastoCliente;
//*/
//}
//
//List<Tiquete*>* toArray(List<Area*>* listaAreas){
//    int total = 0;
//    Area* elemento;
//    List<Tiquete*> *L;
//    List<Tiquete*> *arrTiquetes;
//
//    listaAreas->goToStart();
//    while(!listaAreas->atEnd()){
//        elemento = listaAreas->getElement();
//        total += elemento->tiquetesAtendidos->getSize();
//        listaAreas->next();
//    }
//
//    arrTiquetes = new ArrayList<Tiquete*>(total);
//
//    listaAreas->goToStart();
//    while(!listaAreas->atEnd()){
//        elemento = listaAreas->getElement();
//        L = elemento->tiquetesAtendidos;
//        arrTiquetes->extends(L);
//        listaAreas->next();
//    }
//
//
//    return arrTiquetes;
//}
//
////float tiempoPromedio(Area* area){
////    Tiquete* nTiquete;
////    float promedio = 0;
////    List<Tiquete*>* tiquetes;
////    tiquetes = area->tiquetesAtendidos;
////    tiquetes->goToStart();
////    while(!tiquetes->atEnd()){
////        nTiquete = tiquetes->getElement();
////        promedio += nTiquete->espera;
////        tiquetes->next();
////    }
////    return promedio / area->tiquetesAtendidos->getSize();
////}
//
//void agregarVentana(Area* area){
//    area->addVentanilla(new Ventana(area));
//}
//
//void eliminarVentana(Area* area, Ventana* v){
//    Ventana* ventana = area->deleteVentanilla(v);
//    cout << ventana->getCodigo() << " eliminada.";
//}
//
//int main4(){
//    srand(time(0));
//
//    List<Servicio*> *listaServicios = new DLinkedList<Servicio*>();
//    List<Area*> *listaAreas = new DLinkedList<Area*>();
//    List<Tiquete*> *arregloTiquetes;
//
//    Area* area = new Area(generarNombreAleatorio());
//    Area* area2 = new Area(generarNombreAleatorio());
//    area->addVentanilla(new Ventana(area));
//    area2->addVentanilla(new Ventana(area2));
//    Servicio* aeaea = new Servicio(generarNombreAleatorio(), area);
//    listaServicios->append(new Servicio(generarNombreAleatorio(), area2));
//    listaServicios->append(aeaea);
//    listaServicios->append(new Servicio(generarNombreAleatorio(), area2));
//    listaServicios->append(new Servicio(generarNombreAleatorio(), area));
//    listaServicios->print();
//    area->servicios = listaServicios;
//    listaAreas->append(area);
//
//    area2->servicios = listaServicios;
//    listaAreas->append(area2);
//
//    printListaServicios(area2->servicios);
//
//    for(int i = 0; i < 100; i++){
//            generarTiquete(listaAreas->getElement(), aeaea, generarNumero(2));
//    }
//    listaAreas->goToStart();
//    listaAreas->next();
//    for(int i = 0; i < 100; i++){
//            generarTiquete(listaAreas->getElement(),aeaea, generarNumero(2));
//    }
//    listaAreas->goToStart();
//
//    for(int i = 0; i < 100; i++){
//        Area *nArea;
//        List<Ventana*>* ventana;
//        nArea = listaAreas->getElement();
//        ventana = nArea->getVentanillas();
//        atender(ventana->getElement());
//    }
//    listaAreas->next();
//    for(int i = 0; i < 100; i++){
//        Area *nArea;
//        nArea = listaAreas->getElement();
//        atender(nArea->getVentanillas()->getElement());
//    }
//
//    arregloTiquetes = toArray(listaAreas);
//    printListaTiquetes(arregloTiquetes);
//
//
//    cout << area->tiempoPromedio() << endl;
//    cout << "Tiquetes emitidos: "<< area->getTiquetesRecibidos() << " Clientes atendidos: " << area->getContadorT() << endl;
//    cout << "Cantidad de tiquetes preferenciales emitidos: " << getTiqPref(arregloTiquetes) << endl;
//}

