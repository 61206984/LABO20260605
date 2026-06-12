#include <iostream>
#include "lista.h"
using namespace std;

Proceso* listaHead = nullptr;
int contadorID = 1;

void insertarProceso(string nombre, int prioridad, int memoria) {
    Proceso* nuevo = new Proceso();
    nuevo->id = contadorID++;
    nuevo->nombre = nombre;
    nuevo->prioridad = prioridad;
    nuevo->memoria = memoria;
    nuevo->siguiente = nullptr;

    if (listaHead == nullptr) {
        listaHead = nuevo;
    } else {
        Proceso* temp = listaHead;
        while (temp->siguiente != nullptr) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;
    }
    cout << "Proceso registrado con ID: " << nuevo->id << endl;
}

void eliminarProceso(int id) {
    if (listaHead == nullptr) {
        cout << "No hay procesos registrados." << endl;
        return;
    }
    if (listaHead->id == id) {
        Proceso* temp = listaHead;
        listaHead = listaHead->siguiente;
        delete temp;
        cout << "Proceso eliminado." << endl;
        return;
    }
    Proceso* actual = listaHead;
    while (actual->siguiente != nullptr && actual->siguiente->id != id) {
        actual = actual->siguiente;
    }
    if (actual->siguiente == nullptr) {
        cout << "Proceso no encontrado." << endl;
        return;
    }
    Proceso* temp = actual->siguiente;
    actual->siguiente = temp->siguiente;
    delete temp;
    cout << "Proceso eliminado." << endl;
}

Proceso* buscarProcesoPorID(int id) {
    Proceso* temp = listaHead;
    while (temp != nullptr) {
        if (temp->id == id) return temp;
        temp = temp->siguiente;
    }
    return nullptr;
}

Proceso* buscarProcesoPorNombre(string nombre) {
    Proceso* temp = listaHead;
    while (temp != nullptr) {
        if (temp->nombre == nombre) return temp;
        temp = temp->siguiente;
    }
    return nullptr;
}

void modificarPrioridad(int id, int nuevaPrioridad) {
    Proceso* p = buscarProcesoPorID(id);
    if (p == nullptr) {
        cout << "Proceso no encontrado." << endl;
        return;
    }
    p->prioridad = nuevaPrioridad;
    cout << "Prioridad actualizada." << endl;
}

void listarProcesos() {
    if (listaHead == nullptr) {
        cout << "Lista de procesos vacia." << endl;
        return;
    }
    Proceso* temp = listaHead;
    cout << "\n--- Lista de Procesos ---" << endl;
    while (temp != nullptr) {
        cout << "ID: " << temp->id
             << " | Nombre: " << temp->nombre
             << " | Prioridad: " << temp->prioridad
             << " | Memoria: " << temp->memoria << " MB" << endl;
        temp = temp->siguiente;
    }
}

void menuGestorProcesos() {
    int op;
    do {
        cout << "\n  ╔══════════════════════════════╗" << endl;
        cout << "  ║    GESTOR DE PROCESOS        ║" << endl;
        cout << "  ║  (Estructura: Lista Enlazada)║" << endl;
        cout << "  ╚══════════════════════════════╝" << endl;
        cout << "  1. Insertar proceso" << endl;
        cout << "  2. Eliminar proceso por ID" << endl;
        cout << "  3. Buscar proceso por ID" << endl;
        cout << "  4. Buscar proceso por nombre" << endl;
        cout << "  5. Modificar prioridad" << endl;
        cout << "  6. Listar todos los procesos" << endl;
        cout << "  0. Volver al menu principal" << endl;
        op = leerEntero("  Opcion: ", 0, 6);

        if (op == 1) {
            cout << "\n  -- Insertar nuevo proceso --" << endl;
            cout << "  (El nombre no debe contener espacios, ej: chrome, notepad)" << endl;
            string nombre = leerTexto("  Nombre del proceso : ");
            int prioridad = leerEntero("  Prioridad (1=baja, 10=alta): ", 1, 10);
            int memoria = leerEntero("  Memoria requerida en MB (1-4096): ", 1, 4096);
            insertarProceso(nombre, prioridad, memoria);
        } else if (op == 2) {
            cout << "\n  -- Eliminar proceso --" << endl;
            cout << "  (Use la opcion 6 para ver los IDs disponibles)" << endl;
            int id = leerEntero("  ID del proceso a eliminar: ", 1, 99999);
            eliminarProceso(id);
        } else if (op == 3) {
            cout << "\n  -- Buscar proceso por ID --" << endl;
            int id = leerEntero("  ID a buscar: ", 1, 99999);
            Proceso* p = buscarProcesoPorID(id);
            if (p) {
                cout << "  [OK] Proceso encontrado:" << endl;
                cout << "       Nombre   : " << p->nombre << endl;
                cout << "       Prioridad: " << p->prioridad << endl;
                cout << "       Memoria  : " << p->memoria << " MB" << endl;
            } else {
                cout << "  [!] No existe proceso con ese ID." << endl;
            }
            esperarEnter();
        } else if (op == 4) {
            cout << "\n  -- Buscar proceso por nombre --" << endl;
            string nombre = leerTexto("  Nombre a buscar: ");
            Proceso* p = buscarProcesoPorNombre(nombre);
            if (p) {
                cout << "  [OK] Proceso encontrado:" << endl;
                cout << "       ID       : " << p->id << endl;
                cout << "       Prioridad: " << p->prioridad << endl;
                cout << "       Memoria  : " << p->memoria << " MB" << endl;
            } else {
                cout << "  [!] No existe proceso con ese nombre." << endl;
            }
            esperarEnter();
        } else if (op == 5) {
            cout << "\n  -- Modificar prioridad --" << endl;
            cout << "  (Use la opcion 6 para ver los IDs disponibles)" << endl;
            int id = leerEntero("  ID del proceso: ", 1, 99999);
            int nueva = leerEntero("  Nueva prioridad (1=baja, 10=alta): ", 1, 10);
            modificarPrioridad(id, nueva);
        } else if (op == 6) {
            listarProcesos();
            esperarEnter();
        }
    } while (op != 0);
}