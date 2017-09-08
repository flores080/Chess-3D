#include <stdlib.h>
#include <n_p.h>

nodo_q_p::nodo_q_p(char* usuario, int partidas_ganadas, int partidas_perdidas, nodo_q_p* next)
{
    this->usuario = usuario;
    this->partidas_ganadas = partidas_ganadas;
    this->partidas_perdidas = partidas_perdidas;
    this->next = next;
}
