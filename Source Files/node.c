#include <stdlib.h>
#include <node.h>
node* create(char pieza, char color, int fila, int columna,node* next)
{
    node* new_node = (node*)malloc(sizeof(node));
    if(new_node == NULL)
    {
        printf("Error creating a new node.\n");
        exit(0);
    }
    new_node->pieza = pieza;
    new_node->color = color;
    new_node->fila = fila;
    new_node->columna = columna;
    new_node->next = next;

    return new_node;
}



