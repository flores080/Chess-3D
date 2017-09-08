#ifndef N_P_H
#define N_P_H
typedef struct nodo_q_p
{

    char* usuario;
    int partidas_ganadas;
    int partidas_perdidas;
    struct nodo_q_p* next;
    nodo_q_p(char* usuario, int partidas_ganadas, int partidas_perdidas, nodo_q_p* next);
} nodo_q_p;

#endif // N_P_H
