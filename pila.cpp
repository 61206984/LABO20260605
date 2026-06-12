#include <iostream>
#include "pila.h"
using namespace std;

NodoPila* pilaTop = nullptr;

void asignarMemoria(int idProceso, int bloque) {
    if (buscarProcesoPorID(idProceso) == nullptr) {
        cout << "  [!] No existe ningun proceso con ID " << idProceso << "." << endl;
        return;
    }
    NodoPila* nuevo = new NodoPila();
    nuevo->idProceso = idProceso;
    nuevo->bloqueMemoria = bloque;
    nuevo->siguiente = pilaTop;
    pilaTop = nuevo;
    cout << "  [OK] Se asignaron " << bloque << " MB al proceso ID " << idProceso << "." << endl;
}

void liberarMemoria() {
    if (pilaTop == nullptr) {
        cout << "  [!] La pila de memoria esta vacia. No hay bloques para liberar." << endl;
        return;
    }
    cout << "  [OK] Liberando " << pilaTop->bloqueMemoria
         << " MB del proceso ID " << pilaTop->idProceso << "." << endl;
    NodoPila* temp = pilaTop;
    pilaTop = pilaTop->siguiente;
    delete temp;
}

void mostrarMemoria() {
    if (pilaTop == nullptr) {
        cout << "  [!] La pila de memoria esta vacia." << endl;
        return;
    }
    cout << "\n  +------------+------------+" << endl;
    cout << "  | Proceso ID | Bloque(MB) |" << endl;
    cout << "  +------------+------------+" << endl;
    NodoPila* temp = pilaTop;
    while (temp != nullptr) {
        cout << "  | " << temp->idProceso
             << "          | " << temp->bloqueMemoria << endl;
        temp = temp->siguiente;
    }
    cout << "  +------------+------------+" << endl;
    cout << "  (tope de pila arriba)" << endl;
}

void menuMemoria() {
    int op;
    do {
        cout << "\n  ╔══════════════════════════════╗" << endl;
        cout << "  ║    GESTOR DE MEMORIA         ║" << endl;
        cout << "  ║  (Estructura: Pila)          ║" << endl;
        cout << "  ╚══════════════════════════════╝" << endl;
        cout << "  1. Asignar memoria a proceso" << endl;
        cout << "  2. Liberar ultimo bloque (LIFO)" << endl;
        cout << "  3. Ver estado actual de memoria" << endl;
        cout << "  0. Volver al menu principal" << endl;
        op = leerEntero("  Opcion: ", 0, 3);

        if (op == 1) {
            cout << "\n  -- Asignar memoria --" << endl;
            cout << "  (El proceso debe existir en el Gestor de Procesos)" << endl;
            int id = leerEntero("  ID del proceso: ", 1, 99999);
            int bloque = leerEntero("  Tamano del bloque en MB (1-4096): ", 1, 4096);
            asignarMemoria(id, bloque);
        } else if (op == 2) {
            cout << "\n  -- Liberar ultimo bloque --" << endl;
            liberarMemoria();
        } else if (op == 3) {
            mostrarMemoria();
            esperarEnter();
        }
    } while (op != 0);
}