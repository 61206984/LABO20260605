#ifndef COLA_H
#define COLA_H

#include "proceso.h"
#include "lista.h"

extern NodoCola* colaFrente;
extern NodoCola* colaFin;
extern int totalEjecutados;

void encolarProceso(int id);
void ejecutarProceso();
void mostrarCola();
void menuCPU();

#endif