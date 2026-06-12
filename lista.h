#ifndef LISTA_H
#define LISTA_H

#include "proceso.h"

extern Proceso* listaHead;
extern int contadorID;

void insertarProceso(string nombre, int prioridad, int memoria);
void eliminarProceso(int id);
Proceso* buscarProcesoPorID(int id);
Proceso* buscarProcesoPorNombre(string nombre);
void modificarPrioridad(int id, int nuevaPrioridad);
void listarProcesos();
void menuGestorProcesos();
int leerEntero(string mensaje, int minVal, int maxVal);
string leerTexto(string mensaje);

#endif