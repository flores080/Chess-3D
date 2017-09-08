#ifndef LOGICA_H
#define LOGICA_H
#include <string.h>
#include <iostream>
#include <MatrizOrtogonal.h>

using namespace std;

struct movimiento{
    char pieza;
    int nivel;
    int movx;
    int movy;
    movimiento(string movimiento);
};

int convLetra(char letra);

int difx(int x, int movx);
int dify(int y, int movy);


bool moverPeonHacia(Matriz * matriz, Nodo * futuro, int posy_fut, int posx_fut,  int nivel, char color, char pieza);
bool moverCaballoHacia(Matriz * matriz, Nodo* futuro, int posy_fut, int posx_fut,  int nivel, char color, char pieza);
bool moverAlfilHacia(Matriz * matriz, Nodo * futuro, int posy_fut, int posx_fut,  int nivel, char color, char pieza);
bool moverTorreHacia(Matriz * matriz, Nodo * futuro, int posy_fut, int posx_fut,  int nivel, char color, char pieza);
bool moverReylHacia(Matriz * matriz, Nodo * futuro, int posy_fut, int posx_fut,  int nivel, char color, char pieza);
bool moverReynalHacia(Matriz * matriz, Nodo * futuro, int posy_fut, int posx_fut,  int nivel, char color, char pieza);

bool mismaPiezaDifNivel(Nodo* nodo, char pieza, char color, int nivel);
int misma_Torre_nivel(Matriz * matriz, Nodo * nodo, char pieza, char color, int nivel);
int mismo_Alfil_nivel(Matriz * matriz, Nodo * nodo, char pieza, char color, int nivel);
int misma_pieza_nivel(Nodo * nodo, char pieza, char color, int nivel);
bool sepuedesubirTorre(Matriz * matriz, int _y, int _x, char pieza, char color, int nivel);
bool sepuedesubirAlfil(Matriz * matriz, int _y, int _x, char pieza, char color, int nivel);
#endif // LOGICA_H
