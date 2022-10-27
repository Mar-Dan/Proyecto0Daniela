#ifndef TIQUETE_H
#define TIQUETE_H

#include <stdexcept>
#include <ctime>
#include <string>

#include "Ventana.h"
#include "Servicio.h"

using namespace std;

class Tiquete
{
    private:
        int prioridad;
        Servicio* servicio;
        string codigo;
        time_t hEntrada;
        time_t hSalida;
        Ventana *ventanilla;



    public:
        double espera;

        Tiquete(int prioridad, Servicio *servicio, string codigo){
            hEntrada = clock();
            this->prioridad = prioridad;
            this->servicio = servicio;
            this->codigo = codigo;

        }
        Tiquete(){};

        void atenderTiquete(Ventana* ventana){
            hSalida = clock();
            espera = ((double)hSalida - (double)hEntrada) / CLOCKS_PER_SEC;
            espera = espera / 60;
            this->ventanilla = ventana;

        }

        int getPrioridad() {return prioridad;}
        Servicio* getServicio() {return servicio;}
        string getCodigo() {return codigo;}
        double getEspera() {return espera;}



    void setCodigo(Area *a, int n){
        codigo = a->getCodigo() + to_string(n);
    }
    void sethEntrada(){

    }
    void gethEntrada(){

    }
    void sethSalida(){

    }
    void gethSalida(){

    }

    void toString(){
        cout<<getCodigo()<<" ";
    }
};

#endif // TIQUETE_H
