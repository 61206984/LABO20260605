#ifndef PILA_H
#define PILA_H

#include "proceso.h"
#include "lista.h"

extern NodoPila* pilaTop;
int calcularMemoriaTotal();

void asignarMemoria(int idProceso, int bloque);
void liberarMemoria();
void mostrarMemoria();
void menuMemoria();

#endif