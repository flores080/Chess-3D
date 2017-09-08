#ifndef Q_P_H
#define Q_P_H
#include <n_p.h>

typedef struct queue_prioridad
{
    nodo_q_p* head;
public:
    void eque(queue_prioridad* q,  char* usuario, int partidas_ganadas, int partidas_perdidas);
    void clear(queue_prioridad* q);
    nodo_q_p* front(queue_prioridad* q);
    void dispose(queue_prioridad* q);
    queue_prioridad();
} queue_prioridad;


#endif // Q_P_H
