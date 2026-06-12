#include <iostream>
#include <fstream>
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

Proceso* listaHead = nullptr;
NodoCola* colaFrente = nullptr;
NodoCola* colaFin = nullptr;
NodoPila* pilaTop = nullptr;
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

void encolarProceso(int id) {
    Proceso* p = buscarProcesoPorID(id);
    if (p == nullptr) {
        cout << "Proceso no encontrado en la lista." << endl;
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
    cout << "Proceso encolado segun prioridad." << endl;
}

void ejecutarProceso() {
    if (colaFrente == nullptr) {
        cout << "Cola de CPU vacia." << endl;
        return;
    }
    NodoCola* temp = colaFrente;
    cout << "Ejecutando proceso: " << temp->datos.nombre
         << " (ID: " << temp->datos.id
         << ", Prioridad: " << temp->datos.prioridad << ")" << endl;
    colaFrente = colaFrente->siguiente;
    if (colaFrente == nullptr) colaFin = nullptr;
    delete temp;
}

void mostrarCola() {
    if (colaFrente == nullptr) {
        cout << "Cola de CPU vacia." << endl;
        return;
    }
    NodoCola* temp = colaFrente;
    cout << "\n--- Cola de CPU (mayor prioridad primero) ---" << endl;
    while (temp != nullptr) {
        cout << "ID: " << temp->datos.id
             << " | Nombre: " << temp->datos.nombre
             << " | Prioridad: " << temp->datos.prioridad << endl;
        temp = temp->siguiente;
    }
}

void asignarMemoria(int idProceso, int bloque) {
    NodoPila* nuevo = new NodoPila();
    nuevo->idProceso = idProceso;
    nuevo->bloqueMemoria = bloque;
    nuevo->siguiente = pilaTop;
    pilaTop = nuevo;
    cout << "Memoria asignada: " << bloque << " MB al proceso ID " << idProceso << endl;
}

void liberarMemoria() {
    if (pilaTop == nullptr) {
        cout << "No hay memoria asignada." << endl;
        return;
    }
    cout << "Liberando memoria del proceso ID: " << pilaTop->idProceso
         << " (" << pilaTop->bloqueMemoria << " MB)" << endl;
    NodoPila* temp = pilaTop;
    pilaTop = pilaTop->siguiente;
    delete temp;
}

void mostrarMemoria() {
    if (pilaTop == nullptr) {
        cout << "Pila de memoria vacia." << endl;
        return;
    }
    NodoPila* temp = pilaTop;
    cout << "\n--- Estado de Memoria (LIFO) ---" << endl;
    while (temp != nullptr) {
        cout << "Proceso ID: " << temp->idProceso
             << " | Bloque: " << temp->bloqueMemoria << " MB" << endl;
        temp = temp->siguiente;
    }
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
    cout << "Estado guardado en estado.txt" << endl;
}

void cargarEstado() {
    ifstream archivo("estado.txt");
    if (!archivo.is_open()) {
        cout << "No se encontro archivo de estado." << endl;
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
    cout << "Estado cargado correctamente." << endl;
}

void menuGestorProcesos() {
    int op;
    do {
        cout << "\n=== Gestor de Procesos ===" << endl;
        cout << "1. Insertar proceso" << endl;
        cout << "2. Eliminar proceso" << endl;
        cout << "3. Buscar por ID" << endl;
        cout << "4. Buscar por nombre" << endl;
        cout << "5. Modificar prioridad" << endl;
        cout << "6. Listar procesos" << endl;
        cout << "0. Volver" << endl;
        cout << "Opcion: ";
        cin >> op;

        if (op == 1) {
            string nombre;
            int prioridad, memoria;
            cout << "Nombre: "; cin >> nombre;
            cout << "Prioridad (1-10): "; cin >> prioridad;
            cout << "Memoria requerida (MB): "; cin >> memoria;
            insertarProceso(nombre, prioridad, memoria);
        } else if (op == 2) {
            int id;
            cout << "ID a eliminar: "; cin >> id;
            eliminarProceso(id);
        } else if (op == 3) {
            int id;
            cout << "ID a buscar: "; cin >> id;
            Proceso* p = buscarProcesoPorID(id);
            if (p) cout << "Encontrado: " << p->nombre << " | Prioridad: " << p->prioridad << endl;
            else cout << "No encontrado." << endl;
        } else if (op == 4) {
            string nombre;
            cout << "Nombre a buscar: "; cin >> nombre;
            Proceso* p = buscarProcesoPorNombre(nombre);
            if (p) cout << "Encontrado ID: " << p->id << " | Prioridad: " << p->prioridad << endl;
            else cout << "No encontrado." << endl;
        } else if (op == 5) {
            int id, nueva;
            cout << "ID del proceso: "; cin >> id;
            cout << "Nueva prioridad: "; cin >> nueva;
            modificarPrioridad(id, nueva);
        } else if (op == 6) {
            listarProcesos();
        }
    } while (op != 0);
}

void menuCPU() {
    int op;
    do {
        cout << "\n=== Planificador de CPU ===" << endl;
        cout << "1. Encolar proceso" << endl;
        cout << "2. Ejecutar siguiente proceso" << endl;
        cout << "3. Ver cola actual" << endl;
        cout << "0. Volver" << endl;
        cout << "Opcion: ";
        cin >> op;

        if (op == 1) {
            int id;
            cout << "ID del proceso a encolar: "; cin >> id;
            encolarProceso(id);
        } else if (op == 2) {
            ejecutarProceso();
        } else if (op == 3) {
            mostrarCola();
        }
    } while (op != 0);
}

void menuMemoria() {
    int op;
    do {
        cout << "\n=== Gestor de Memoria ===" << endl;
        cout << "1. Asignar memoria a proceso" << endl;
        cout << "2. Liberar ultimo bloque" << endl;
        cout << "3. Ver estado de memoria" << endl;
        cout << "0. Volver" << endl;
        cout << "Opcion: ";
        cin >> op;

        if (op == 1) {
            int id, bloque;
            cout << "ID del proceso: "; cin >> id;
            cout << "Bloque de memoria (MB): "; cin >> bloque;
            asignarMemoria(id, bloque);
        } else if (op == 2) {
            liberarMemoria();
        } else if (op == 3) {
            mostrarMemoria();
        }
    } while (op != 0);
}

int main() {
    cargarEstado();
    int op;
    do {
        cout << "\n========================================" << endl;
        cout << "   SISTEMA DE GESTION DE PROCESOS" << endl;
        cout << "========================================" << endl;
        cout << "1. Gestor de Procesos (Lista Enlazada)" << endl;
        cout << "2. Planificador de CPU (Cola)" << endl;
        cout << "3. Gestor de Memoria (Pila)" << endl;
        cout << "4. Guardar estado" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> op;

        if (op == 1) menuGestorProcesos();
        else if (op == 2) menuCPU();
        else if (op == 3) menuMemoria();
        else if (op == 4) guardarEstado();

    } while (op != 0);

    cout << "Saliendo del sistema..." << endl;
    return 0;
}