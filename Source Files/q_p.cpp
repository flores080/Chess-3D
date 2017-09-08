#include <q_p.h>
#include <iostream>

using namespace std;

queue_prioridad::queue_prioridad(){
    this->head = NULL;
}
void queue_prioridad::eque(queue_prioridad* q, char *usuario, int partidas_ganadas, int partidas_perdidas)
{
    if(q->head == NULL){
        nodo_q_p* new_node = new nodo_q_p(usuario,partidas_ganadas,partidas_perdidas,NULL);
        q->head = new_node;
    }else{
    /* go to the last node */
        nodo_q_p *cursor = q->head;
        if(partidas_ganadas>q->head->partidas_ganadas){
            nodo_q_p* new_node = new nodo_q_p(usuario, partidas_ganadas, partidas_perdidas,q->head);
            q->head = new_node;
        }else{
        nodo_q_p * back = NULL;
            while(cursor!= NULL){
                if(partidas_ganadas>cursor->partidas_ganadas){
                    break;
                }
                back = cursor;
                cursor = cursor->next;

            }

            back->next = new nodo_q_p(usuario, partidas_ganadas, partidas_perdidas,cursor);
        }
    }
}
void queue_prioridad::clear(queue_prioridad* q)
{

    if(q->head == NULL){
        q->head = NULL;
    }else{
        nodo_q_p *cursor = q->head;
        nodo_q_p *back = NULL;
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
nodo_q_p* queue_prioridad::front(queue_prioridad* q)
{
    return q->head;
}

