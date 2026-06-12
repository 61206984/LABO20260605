#include <iostream>
#include "cola.h"
using namespace std;


NodoCola* colaFrente = nullptr;
NodoCola* colaFin = nullptr;
int totalEjecutados = 0;

void encolarProceso(int id) {
    Proceso* p = buscarProcesoPorID(id);
    if (p == nullptr) {
        cout << "  [!] No existe ningun proceso con ID " << id << "." << endl;
        return;
    }
    NodoCola* nuevo = new NodoCola();
    nuevo->datos = *p;
    nuevo->siguiente = nullptr;

    if (colaFrente == nullptr) {
        colaFrente = nuevo;
        colaFin = nuevo;
    } else {
        NodoCola* actual = colaFrente;
        NodoCola* anterior = nullptr;
        while (actual != nullptr && actual->datos.prioridad >= nuevo->datos.prioridad) {
            anterior = actual;
            actual = actual->siguiente;
        }
        if (anterior == nullptr) {
            nuevo->siguiente = colaFrente;
            colaFrente = nuevo;
        } else {
            nuevo->siguiente = actual;
            anterior->siguiente = nuevo;
            if (actual == nullptr) colaFin = nuevo;
        }
    }
    NodoCola* verificar = colaFrente;
    while (verificar != nullptr) {
        if (verificar->datos.id == id) {
            cout << "  [!] El proceso '" << p->nombre << "' ya esta en la cola." << endl;
            return;
        }
        verificar = verificar->siguiente;
    }
}

void ejecutarProceso() {
    if (colaFrente == nullptr) {
        cout << "  [!] La cola de CPU esta vacia. No hay procesos para ejecutar." << endl;
        return;
    }
    NodoCola* temp = colaFrente;
    cout << "  [>>] Ejecutando: '" << temp->datos.nombre
         << "' | ID: " << temp->datos.id
         << " | Prioridad: " << temp->datos.prioridad << endl;
    colaFrente = colaFrente->siguiente;
    if (colaFrente == nullptr) colaFin = nullptr;
    delete temp;
    totalEjecutados++;
    cout << "  [OK] Proceso finalizado y retirado de la cola." << endl;
}

void mostrarCola() {
    if (colaFrente == nullptr) {
        cout << "  [!] La cola de CPU esta vacia." << endl;
        return;
    }
    cout << "\n  +----+------------------+------------+" << endl;
    cout << "  | ID | Nombre           | Prioridad  |" << endl;
    cout << "  +----+------------------+------------+" << endl;
    NodoCola* temp = colaFrente;
    while (temp != nullptr) {
        cout << "  | " << temp->datos.id
             << "  | " << temp->datos.nombre;
        int espacios = 17 - temp->datos.nombre.length();
        for (int i = 0; i < espacios; i++) cout << " ";
        cout << "| " << temp->datos.prioridad << endl;
        temp = temp->siguiente;
    }
    cout << "  +----+------------------+------------+" << endl;
}

void menuCPU() {
    int op;
    do {
        cout << "\n  ╔══════════════════════════════╗" << endl;
        cout << "  ║    PLANIFICADOR DE CPU       ║" << endl;
        cout << "  ║  (Estructura: Cola)          ║" << endl;
        cout << "  ╚══════════════════════════════╝" << endl;
        cout << "  Procesos ejecutados en esta sesion: " << totalEjecutados << endl;
        cout << "  1. Encolar proceso para ejecucion" << endl;
        cout << "  2. Ejecutar siguiente proceso" << endl;
        cout << "  3. Ver cola actual" << endl;
        cout << "  0. Volver al menu principal" << endl;
        op = leerEntero("  Opcion: ", 0, 3);

        if (op == 1) {
            cout << "\n  -- Encolar proceso --" << endl;
            cout << "  (El proceso debe existir en el Gestor de Procesos)" << endl;
            cout << "  (Ingrese 0 para cancelar)" << endl;
            int id = leerEntero("  ID del proceso a encolar: ", 0, 99999);
            if (id != 0) {
                encolarProceso(id);
                esperarEnter();
    }
        } else if (op == 2) {
            cout << "\n  -- Ejecutar siguiente proceso --" << endl;
            ejecutarProceso();
            esperarEnter();
        } else if (op == 3) {
            mostrarCola();
            esperarEnter();
        }
    } while (op != 0);
}