#include <queue.h>

void queue::eque(queue* q, char pieza, char color, int fila, int columna)
{
    if(q->head == NULL){
        especial(q,pieza,color,fila,columna);
    }else{
    /* go to the last node */
    node *cursor = q->head;
    while(cursor->next != NULL)
        cursor = cursor->next;

    /* create a new node */
    node* new_node =  create(pieza,color,fila,columna,NULL);
    cursor->next = new_node;
    }
}
void queue::deque(queue* q)
{
    if(q->head == NULL){
        q->head = NULL;
    }else{
        node *cursor = q->head;
        node *back = NULL;
        while(cursor->next != NULL)
        {
            back = cursor;
            cursor = cursor->next;
        }

        if(back != NULL)
            back->next = NULL;

        /* if this is the last node in the list*/
        if(cursor == q->head)
            q->head = NULL;

        free(cursor);
    }
}
node* queue::front(queue* q)
{
    return q->head;
}
void queue::especial(queue* q, char pieza, char color, int fila, int columna)
{
    node* new_node = create(pieza,color,fila,columna,q->head);
    q->head = new_node;
}

