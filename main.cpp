#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "lista.h"

using namespace std;

NodoCola* colaFrente = nullptr;
NodoCola* colaFin = nullptr;
NodoPila* pilaTop = nullptr;

int leerEntero(string mensaje, int minVal, int maxVal) {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail() || valor < minVal || valor > maxVal) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  [!] Entrada invalida. Ingrese un numero entre "
                 << minVal << " y " << maxVal << "." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
    }
}

string leerTexto(string mensaje) {
    string valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail() || valor.empty()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  [!] Entrada invalida. Ingrese un texto sin espacios." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
    }
}

void esperarEnter() {
    cout << "\n  Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

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
    cout << "  [OK] Proceso '" << p->nombre << "' encolado con prioridad " << p->prioridad << "." << endl;
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

void guardarEstado() {
    ofstream archivo("estado.txt");
    archivo << contadorID << endl;
    Proceso* temp = listaHead;
    while (temp != nullptr) {
        archivo << "P " << temp->id << " " << temp->prioridad << " " << temp->memoria << " " << temp->nombre << endl;
        temp = temp->siguiente;
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
        }
    }
    archivo.close();
    cout << "  [OK] Estado cargado correctamente." << endl;
}

void menuCPU() {
    int op;
    do {
        cout << "\n  ╔══════════════════════════════╗" << endl;
        cout << "  ║    PLANIFICADOR DE CPU       ║" << endl;
        cout << "  ║  (Estructura: Cola)          ║" << endl;
        cout << "  ╚══════════════════════════════╝" << endl;
        cout << "  1. Encolar proceso para ejecucion" << endl;
        cout << "  2. Ejecutar siguiente proceso" << endl;
        cout << "  3. Ver cola actual" << endl;
        cout << "  0. Volver al menu principal" << endl;
        op = leerEntero("  Opcion: ", 0, 3);

        if (op == 1) {
            cout << "\n  -- Encolar proceso --" << endl;
            cout << "  (El proceso debe existir en el Gestor de Procesos)" << endl;
            int id = leerEntero("  ID del proceso a encolar: ", 1, 99999);
            encolarProceso(id);
        } else if (op == 2) {
            cout << "\n  -- Ejecutar siguiente proceso --" << endl;
            ejecutarProceso();
        } else if (op == 3) {
            mostrarCola();
            esperarEnter();
        }
    } while (op != 0);
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

int main() {
    cout << "\n  Iniciando Sistema de Gestion de Procesos..." << endl;
    cargarEstado();
    int op;
    do {
        cout << "\n  ╔══════════════════════════════╗" << endl;
        cout << "  ║  SISTEMA DE GESTION DE       ║" << endl;
        cout << "  ║        PROCESOS              ║" << endl;
        cout << "  ╚══════════════════════════════╝" << endl;
        cout << "  1. Gestor de Procesos  (Lista Enlazada)" << endl;
        cout << "  2. Planificador de CPU (Cola)" << endl;
        cout << "  3. Gestor de Memoria   (Pila)" << endl;
        cout << "  4. Guardar estado del sistema" << endl;
        cout << "  0. Salir" << endl;
        op = leerEntero("  Opcion: ", 0, 4);

        if (op == 1) menuGestorProcesos();
        else if (op == 2) menuCPU();
        else if (op == 3) menuMemoria();
        else if (op == 4) guardarEstado();

    } while (op != 0);

    cout << "\n  Cerrando sistema. Hasta luego." << endl;
    return 0;
}