#include <iostream>
#include <fstream>
#include <string>
#include "persistencia.h"
#include "lista.h"
#include "pila.h"
using namespace std;

void guardarEstado() {
    ofstream archivo("estado.txt");
    archivo << contadorID << endl;
    Proceso* temp = listaHead;
    while (temp != nullptr) {
        archivo << "P " << temp->id << " " << temp->prioridad << " " << temp->memoria << " " << temp->nombre << endl;
        temp = temp->siguiente;
    }
    NodoPila* tempPila = pilaTop;
    while (tempPila != nullptr) {
        archivo << "M " << tempPila->idProceso << " " << tempPila->bloqueMemoria << endl;
        tempPila = tempPila->siguiente;
    }
    archivo.close();
    cout << "  [OK] Estado guardado en estado.txt" << endl;
}

void cargarEstado() {
    ifstream archivo("estado.txt");
    if (!archivo.is_open()) {
        cout << "  [i] No se encontro estado previo. Iniciando sistema nuevo." << endl;
        return;
    }
    archivo >> contadorID;
    string tipo;
    while (archivo >> tipo) {
        if (tipo == "P") {
            int id, prioridad, memoria;
            string nombre;
            archivo >> id >> prioridad >> memoria >> nombre;
            Proceso* nuevo = new Proceso();
            nuevo->id = id;
            nuevo->nombre = nombre;
            nuevo->prioridad = prioridad;
            nuevo->memoria = memoria;
            nuevo->siguiente = nullptr;
            if (listaHead == nullptr) {
                listaHead = nuevo;
            } else {
                Proceso* t = listaHead;
                while (t->siguiente != nullptr) t = t->siguiente;
                t->siguiente = nuevo;
            }
        } else if (tipo == "M") {
            int idProceso, bloque;
            archivo >> idProceso >> bloque;
            NodoPila* nuevo = new NodoPila();
            nuevo->idProceso = idProceso;
            nuevo->bloqueMemoria = bloque;
            nuevo->siguiente = nullptr;
            if (pilaTop == nullptr) {
                pilaTop = nuevo;
            } else {
                NodoPila* t = pilaTop;
                while (t->siguiente != nullptr) t = t->siguiente;
                t->siguiente = nuevo;
            }
        }
    }
    archivo.close();
    cout << "  [OK] Estado cargado correctamente." << endl;
}