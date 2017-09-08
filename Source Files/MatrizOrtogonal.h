#ifndef MatrizOrtogonal
#define MatrizOrtogonal
#include <queue.h>

typedef struct Nodo Nodo;
typedef struct Encabezado Encabezado;
typedef struct ListaEncabezados ListaEncabezados;
typedef struct Matriz Matriz;

struct Nodo
{
    int fila;
    int columna;
    char pieza;
    char color;
    Nodo * derecha;
    Nodo * izquierda;
    Nodo * arriba;
    Nodo * abajo;

    Nodo * Nivel0;
    Nodo * Nivel2;
    Nodo * Nivel1;
    Nodo(int fila, int columna, char pieza, char color);
};

struct Encabezado
{
    int id;
    Encabezado * siguiente;
    Encabezado * anterior;
    Nodo * acceso;
    Encabezado(int id);
};

struct ListaEncabezados
{
    Encabezado * primero;
    void insertar(Encabezado * nuevo);
    Encabezado * getEncabezado(int id);
};

struct Matriz
{
    ListaEncabezados * eFilas;
    ListaEncabezados * eColumnas;
    ListaEncabezados * eNivel;
    Matriz();
    queue* linealidad;

    void _insertar(int fila, int columna, int nivel, char pieza, char color);
    void insertar(int fila, int columna, int nivel, char pieza, char color);

    void recorrerFilas(int nivel);
    void recorrerColumnas(int nivel);

    void eliminar(int fila, int columna, int nivel);
    void actualizar_columna(Nodo* eliminar, Encabezado* columna);
    void actualizar_fila(Nodo* eliminar, Encabezado* fila);


    void imagenLinealizacion();
    Nodo* getValueAt(int fila, int columna, int nivel);
    Nodo* buscarEnColumna(int columna, int nivel, char pieza, char color);
    Nodo* buscarEnFila(int fila, int nivel, char pieza, char color);
};

#endif // MATRIZORTOGONAL
