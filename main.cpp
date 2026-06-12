#include <iostream>
#include <limits>
#include "lista.h"
#include "cola.h"
#include "pila.h"
#include "persistencia.h"

using namespace std;

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

    cout << "\n  Guardando estado antes de salir..." << endl;
    guardarEstado();
    cout << "\n  Cerrando sistema. Hasta luego." << endl;
    return 0;
}