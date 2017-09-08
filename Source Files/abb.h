#ifndef ABB_H
#define ABB_H
#include <iostream>
#include <cstdlib>
using namespace std;

struct Jugador{
    char* usuario;
    int partidas_ganadas;
    int partidas_perdidas;
};
typedef struct Jugador *JUGADOR;

struct nodo{
     JUGADOR jugador;
     struct nodo *izq, *der;
};

typedef struct nodo *ABB;


ABB abb_crearNodo(char* usuario, int partidas_ganadas, int partidas_perdidas);
void abb_insertar(ABB &arbol, char* usuario, int partidas_ganadas, int partidas_perdidas);
void abb_eliminar(ABB hijo, ABB padre, char* usuario);

void abb_preOrden(ABB arbol);
void abb_enOrden(ABB arbol);
void abb_postOrden(ABB arbol);

void abb_verArbol(ABB arbol,FILE *f);

void abb_generar_imagen(ABB arbol);

ABB abb_nodo_mayor(ABB arbol);

bool abb_esHoja(ABB root);
bool abb_1hijoizq(ABB root);
bool abb_1hijoder(ABB root);
bool abb_2hijos(ABB root);

JUGADOR crearJugador(char* usuario, int partidas_ganadas, int partidas_perdidas);
#endif // ABB_H
