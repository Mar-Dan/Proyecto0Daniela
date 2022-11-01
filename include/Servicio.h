#ifndef SERVICIO_H
#define SERVICIO_H

#include <iostream>
#include <string>
#include "Area.h"
using namespace std;
class Area;

#include "Tiquete.h" // El include aquí para forzar el orden en que se importa
class Servicio
{
   private:
        string nombre;
        Area* area;
        int tiqDados;
        int contadorT;

    public:

        Servicio(string nombre, Area* area){
            this->nombre = nombre;
            this->area = area;
            area->servicios->append(this);
            tiqDados = 0;
            contadorT = 0;
        }

        Servicio(string nombre) {
            this->nombre = nombre;
            tiqDados = 0;
            contadorT = 0;
        }

        string getNombre() {return nombre;}
        int getTiqDados() {return tiqDados;}
        int getContadorT() {return contadorT;}
        Area* getArea(){return area;}

        void addContadorT(){
            contadorT++;
        }

        friend ostream& operator << (ostream& os, const Servicio& m)
        {
            os << m.nombre;
            return os ;
        }
        friend bool operator == (const Servicio &p1, const Servicio &p2)
        {
            if(p1.nombre == p2.nombre)
                return true;
            else
                return false;
        }

        string toString(){
            //string aCode = area->getCodigo();
            return getNombre();
        }
};
#endif // SERVICIO_H



