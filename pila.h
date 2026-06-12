#ifndef PILA_H
#define PILA_H

#include "proceso.h"
#include "lista.h"

extern NodoPila* pilaTop;

void asignarMemoria(int idProceso, int bloque);
void liberarMemoria();
void mostrarMemoria();
void menuMemoria();

#endif