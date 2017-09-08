#include <stdio.h>
#include <stdlib.h>
#include <node.h>
#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue
{
    node* head;
public:
    void eque(queue* q, char pieza, char color, int fila, int columna);
    void deque(queue* q);
    node* front(queue* q);
    void especial(queue* q, char pieza, char color, int fila, int columna);
    void dispose(queue* q);
    queue();
} queue;



#endif // QUEUE_H
