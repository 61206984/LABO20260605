#ifndef PROCESO_H
#define PROCESO_H

#include <string>
using namespace std;

struct Proceso {
    int id;
    string nombre;
    int prioridad;
    int memoria;
    Proceso* siguiente;
};

struct NodoCola {
    Proceso datos;
    NodoCola* siguiente;
};

struct NodoPila {
    int idProceso;
    int bloqueMemoria;
    NodoPila* siguiente;
};

#endif