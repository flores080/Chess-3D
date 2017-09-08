#include <stdlib.h>
#include <node.h>
node::node(char pieza, char color, int fila, int columna,node* next)
{
    this->pieza = pieza;
    this->color = color;
    this->fila = fila;
    this->columna = columna;
    this->next = next;
}



