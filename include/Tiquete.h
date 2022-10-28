#ifndef TIQUETE_H
#define TIQUETE_H

#include <stdexcept>
#include <ctime>


#include "Servicio.h"

using namespace std;

class Ventana;
class Servicio;

class Tiquete
{
    private:
        int prioridad;
        Servicio* servicio;
        string codigo;
        time_t hEntrada;
        time_t hSalida;
        Ventana* ventanilla;



    public:

        double espera;
        Tiquete(int prioridad, Servicio *servicio, string codigo){
            hEntrada = clock();
            this->prioridad = prioridad;
            this->servicio = servicio;
            this->codigo = codigo;

        }

        void atenderTiquete(Ventana* ventana){
            hSalida = clock();
            espera = ((double)hSalida - (double)hEntrada);
            this->servicio->addContadorT();
            this->espera = espera / CLOCKS_PER_SEC;
            this->ventanilla = ventana;

        }

        void toString(){
            cout<<getCodigo()<<" ";
        }

        int getPrioridad() {return prioridad;}
        Servicio* getServicio() {return servicio;}
        string getCodigo() {return codigo;}
        double getEspera() {return espera;}
};
#include "Ventana.h"

#endif // TIQUETE_H
