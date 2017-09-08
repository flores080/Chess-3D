#ifndef NODE_H
#define NODE_H
typedef struct node
{
    char pieza;
    char color;
    int fila;
    int columna;
    struct node* next;
    node(char pieza, char color, int fila, int columna, node* next);
} node;


#endif // NODE_H
