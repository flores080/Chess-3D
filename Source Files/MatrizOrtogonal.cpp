#include <MatrizOrtogonal.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
using namespace std;

Nodo::Nodo(int fila, int columna, char pieza, char color)
{
    this->fila = fila;
    this->columna = columna;
    this->pieza = pieza;
    this->color = color;
    this->abajo = NULL;
    this->arriba = NULL;
    this->derecha = NULL;
    this->izquierda = NULL;
    this->Nivel0 = NULL;
    this->Nivel2 = NULL;
    this->Nivel1 = NULL;
}

Encabezado::Encabezado(int id)
{
    this->id = id;
    this->siguiente = NULL;
    this->anterior = NULL;
    this->acceso = NULL;
}

void ListaEncabezados::insertar(Encabezado * nuevo)
{
    if(primero == NULL)
    {
       primero = nuevo;
    }
    else
    {
        if(nuevo->id < primero->id) //Inserción al inicio
        {
            nuevo->siguiente = primero;
            primero->anterior = nuevo;
            primero = nuevo;
        }
        else
        {
            Encabezado * actual = primero;
            while(actual->siguiente != NULL)
            {
                if(nuevo->id < actual->siguiente->id) //Inserción en el medio
                {
                    nuevo->siguiente = actual->siguiente;
                    actual->siguiente->anterior = nuevo;
                    nuevo->anterior = actual;
                    actual->siguiente = nuevo;
                    break;
                }

                actual = actual->siguiente;
            }

            if(actual->siguiente == NULL) //Inserción al final
            {
                actual->siguiente = nuevo;
                nuevo->anterior = actual;
            }
        }
    }
}

Encabezado * ListaEncabezados::getEncabezado(int id)
{
    Encabezado * actual = primero;
    while(actual != NULL)
    {
        if(actual->id == id)
        {
            return actual;
        }

        actual = actual->siguiente;
    }

    return NULL;
}

Matriz::Matriz()
{
    this->eFilas = new ListaEncabezados();
    this->eColumnas = new ListaEncabezados();
    linealidad = new queue();
    ////////////////////////////////////////////////// NIVEL 0
    //////////////////////////////////// PIEZAS NEGRAS
    this->insertar(0, 0, 0, 'C', 'N');
    this->insertar(0, 7, 0, 'C', 'N');

    this->insertar(0, 1, 0, 'A', 'N');
    this->insertar(0, 6, 0, 'A', 'N');

    this->insertar(0, 2, 0, 'T', 'N');
    this->insertar(0, 5, 0, 'T', 'N');

    this->insertar(0, 3, 0, 'R', 'N');
    this->insertar(0, 4, 0, 'D', 'N');

    for(int i = 0; i<8; i++){
        this->insertar(1, i, 0, 'P', 'N');
    }
    //////////////////////////////////// PIEZAS BLANCAS
    this->insertar(7, 0, 0, 'C', 'B');
    this->insertar(7, 7, 0, 'C', 'B');

    this->insertar(7, 1, 0, 'A', 'B');
    this->insertar(7, 6, 0, 'A', 'B');

    this->insertar(7, 2, 0, 'T', 'B');
    this->insertar(7, 5, 0, 'T', 'B');

    this->insertar(7, 3, 0, 'D', 'B');
    this->insertar(7, 4, 0, 'R', 'B');

    for(int i = 0; i<8; i++){
        this->insertar(6, i, 0, 'P', 'B');
    }

    ////////////////////////////////////////////////// NIVEL 1
    //////////////////////////////////// PIEZAS NEGRAS
    this->insertar(0, 7, 1, 'C', 'N');
    this->insertar(0, 6, 1, 'A', 'N');
    this->insertar(0, 5, 1, 'T', 'N');
    for(int i = 5; i<8; i++){
        this->insertar(1, i, 1, 'P', 'N');
    }

    //////////////////////////////////// PIEZAS BLANCAS
    this->insertar(7, 0, 1, 'C', 'B');
    this->insertar(7, 1, 1, 'A', 'B');
    this->insertar(7, 2, 1, 'T', 'B');
    for(int i = 0; i<3; i++){
        this->insertar(6, i, 1, 'P', 'B');
    }

    ////////////////////////////////////////////////// NIVEL 2
    //////////////////////////////////// PIEZAS NEGRAS
    this->insertar(0, 0, 2, 'C', 'N');
    this->insertar(0, 1, 2, 'A', 'N');
    this->insertar(0, 2, 2, 'T', 'N');
    for(int i = 0; i<3; i++){
        this->insertar(1, i, 2, 'P', 'N');
    }

    //////////////////////////////////// PIEZAS BLANCAS
    this->insertar(7, 7, 2, 'C', 'B');
    this->insertar(7, 6, 2, 'A', 'B');
    this->insertar(7, 5, 2, 'T', 'B');
    for(int i = 5; i<8; i++){
        this->insertar(6, i, 2, 'P', 'B');
    }
}

Nodo* Matriz::getValueAt(int fila, int columna, int nivel){
    Encabezado * eFila = eFilas->getEncabezado(fila);
    if(eFila)
    {
        Nodo * actual = eFila->acceso;
        while(actual != NULL)
        {
            if(actual->fila == fila && actual->columna == columna){
                if(nivel==0 && actual->Nivel0)
                    return actual->Nivel0;
                if(nivel==1 && actual)
                     return actual;
                if(nivel==2 && actual->Nivel2)
                    return actual->Nivel2;
            }
            actual = actual->derecha;
        }
    }
    return NULL;
}

Nodo* Matriz::buscarEnColumna(int columna, int nivel, char pieza, char color){
    Encabezado * eColumna = eColumnas->getEncabezado(columna);
    if(eColumna){
        Nodo * actual = eColumna->acceso;
        while(actual!=NULL){
                if(nivel==0 && actual->Nivel0){
                    if(actual->Nivel0->pieza == pieza && actual->Nivel0->color == color){
                        return actual->Nivel0;
                    }
                }
                if(nivel==1 && actual){
                     if(actual->pieza == pieza && actual->color == color){
                        return actual;
                     }
                }
                if(nivel==2 && actual->Nivel2){
                    if(actual->Nivel2->pieza == pieza && actual->Nivel2->color == color){
                        return actual->Nivel2;
                    }
                }
            actual = actual->abajo;
        }
    }
}

Nodo* Matriz::buscarEnFila(int fila, int nivel, char pieza, char color){
    Encabezado * eFila = eFilas->getEncabezado(fila);
    if(eFila){
        Nodo * actual = eFila->acceso;
        while(actual!=NULL){
                if(nivel==0 && actual->Nivel0){
                    if(actual->Nivel0->pieza == pieza && actual->Nivel0->color == color){
                        return actual->Nivel0;
                    }
                }
                if(nivel==1 && actual){
                     if(actual->pieza == pieza && actual->color == color){
                        return actual;
                     }
                }
                if(nivel==2 && actual->Nivel2){
                    if(actual->Nivel2->pieza == pieza && actual->Nivel2->color == color){
                        return actual->Nivel2;
                    }
                }
            actual = actual->derecha;
        }
    }
}

void Matriz::_insertar(int fila, int columna, int nivel, char pieza, char color)
{
    if(!getValueAt(fila,columna, nivel)){
        Nodo * nuevo = new Nodo(fila, columna, pieza, color);

        //INSERCION_FILAS
        Encabezado * eFila = eFilas->getEncabezado(fila);
        if(eFila == NULL) //Si no existe encabezado se crea.
        {
            eFila = new Encabezado(fila);
            eFilas->insertar(eFila);
            eFila->acceso = nuevo;
        }
        else
        {
            if(nuevo->columna < eFila->acceso->columna) //Inserción al inicio
            {
                nuevo->derecha = eFila->acceso;
                eFila->acceso->izquierda = nuevo;
                eFila->acceso = nuevo;
            }
            else
            {
                Nodo * actual = eFila->acceso;
                while(actual->derecha != NULL)
                {
                    if(nuevo->columna < actual->derecha->columna) //Inserción en el medio
                    {
                        nuevo->derecha = actual->derecha;
                        actual->derecha->izquierda = nuevo;
                        nuevo->izquierda = actual;
                        actual->derecha = nuevo;
                        break;
                    }

                    actual = actual->derecha;
                }

                if(actual->derecha == NULL) //Inserción al final
                {
                    actual->derecha = nuevo;
                    nuevo->izquierda = actual;
                }
            }
        }
        //FIN_FILAS

        //INSERCION_COLUMNAS
        Encabezado * eColumna = eColumnas->getEncabezado(columna);
        if(eColumna == NULL) //Si no existe encabezado se crea.
        {
            eColumna = new Encabezado(columna);
            eColumnas->insertar(eColumna);
            eColumna->acceso = nuevo;
        }
        else
        {
            if(nuevo->fila < eColumna->acceso->fila) //Inserción al inicio
            {
                nuevo->abajo = eColumna->acceso;
                eColumna->acceso->arriba = nuevo;
                eColumna->acceso = nuevo;
            }
            else
            {
                Nodo * actual = eColumna->acceso;
                while(actual->abajo != NULL)
                {
                    if(nuevo->fila < actual->abajo->fila) //Inserción en el medio
                    {
                        nuevo->abajo = actual->abajo;
                        actual->abajo->arriba = nuevo;
                        nuevo->arriba = actual;
                        actual->abajo = nuevo;
                        break;
                    }

                    actual = actual->abajo;
                }

                if(actual->abajo == NULL) //Inserción al final
                {
                    actual->abajo = nuevo;
                    nuevo->arriba = actual;
                }
            }
        }
        //FIN_COLUMNAS
    }else{
        if(getValueAt(fila,columna,nivel)->pieza == ' '){
            getValueAt(fila,columna,nivel)->pieza = pieza;
            getValueAt(fila,columna,nivel)->color = color;
        }else{
        cout<<"Error al insertar (valor existente): "<<Matriz::getValueAt(fila,columna, nivel)->pieza<<" - "<<Matriz::getValueAt(fila,columna, nivel)->color<<endl;
        }
    }
}

void Matriz::insertar(int fila, int columna, int nivel, char pieza, char color)
{
  if(nivel==1){
      _insertar(fila,columna, nivel, pieza, color);
  }else{

      if(!getValueAt(fila,columna,1)){
          _insertar(fila, columna, 1, ' ', ' ');
      }
      if(nivel==0){
          getValueAt(fila,columna,1)->Nivel0 = new Nodo(fila, columna, pieza, color);
          getValueAt(fila,columna,1)->Nivel0->Nivel1 = getValueAt(fila,columna,1);
      }else if(nivel==2){
          getValueAt(fila,columna,1)->Nivel2 = new Nodo(fila, columna, pieza, color);
          getValueAt(fila,columna,1)->Nivel2->Nivel1 = getValueAt(fila,columna,1);
      }
  }
}

void Matriz::eliminar(int fila, int columna, int nivel)
{
    //cout<<"******************************** ELIMINAR ********************************"<<endl;
    Nodo * tmp = getValueAt(fila,columna,nivel);
    if(tmp){
        if(nivel == 0){
            getValueAt(fila,columna,1)->Nivel0 = NULL;
            free(tmp);
        }else if(nivel == 1){
            if(tmp->Nivel0 || tmp->Nivel2){
                tmp->pieza = ' ';
                tmp->color = ' ';
            }else{
                actualizar_columna(tmp,eColumnas->getEncabezado(columna));
                actualizar_fila(tmp, eFilas->getEncabezado(fila));
                free(tmp);
            }
        }else if(nivel == 2){
            getValueAt(fila,columna,1)->Nivel2 = NULL;
            free(tmp);
        }

    }else{
        cout<<"Error al eliminar (valor NO existente): "<<endl;
    }
}

void Matriz::actualizar_columna(Nodo* eliminar, Encabezado* columna){
    if(eliminar->arriba){
        if(eliminar->abajo){
            eliminar->arriba->abajo = eliminar->abajo;
            eliminar->abajo->arriba = eliminar->arriba;
        }else {
            eliminar->arriba->abajo = NULL;
        }
    }else{
        if(eliminar->abajo){
            columna->acceso = eliminar->abajo;
            eliminar->abajo->arriba = eliminar->arriba;
        }else{
            columna->acceso = NULL;
        }
    }

    if(!columna->acceso){
        if(columna->anterior&&columna->siguiente){
            columna->anterior->siguiente = columna->siguiente;
        }else if(!columna->anterior&&columna->siguiente){
            eColumnas->primero = columna->siguiente;
        }else{
            eColumnas->primero = NULL;
        }
        free(columna);
    }
}

void Matriz::actualizar_fila(Nodo* eliminar, Encabezado* fila){
    if(eliminar->izquierda){
        if(eliminar->derecha){
            eliminar->izquierda->derecha = eliminar->derecha;
            eliminar->derecha->izquierda = eliminar->izquierda;
        }else {
            eliminar->izquierda->derecha = NULL;
        }
    }else{
        //cout<<"es acceso: "<<eliminar->fila<<"."<<eliminar->columna<<endl;
        if(fila->acceso->derecha){
            fila->acceso = fila->acceso->derecha;
            eliminar->derecha->izquierda = eliminar->izquierda;
        }else{
            fila->acceso = NULL;
        }
    }

    if(!fila->acceso){
        if(fila->anterior&&fila->siguiente){
            fila->anterior->siguiente = fila->siguiente;
        }else if(!fila->anterior&&fila->siguiente){
            eFilas->primero = fila->siguiente;
        }else{
            eFilas->primero = NULL;
        }
        free(fila);
    }
}

void Matriz::imagenLinealizacion(){
    FILE *f = fopen("/home/ferflo/Documentos/Qt/Graficas/linealizacion.dot","w");
    fprintf(f,"digraph G {\n");
    fprintf(f,"\n\tgraph [splines=true overlap=false]; rankdir=LR;\n");
    fprintf(f,"\tedge[color=\"#FF847C\"];\n");
    fprintf(f,"\tgraph [bgcolor=\"#2A363B\"];");
    fprintf(f,"\tnode[style=filled color=\"#99B898\" fillcolor=\"#2A363B\" fontname=\"Montzerat Light\" fontcolor=\"#FECEA8\" shape=rectangle];\n\n");

    if(linealidad->head!=NULL){
        node* cursor = linealidad->head;
        if(cursor->next==NULL){
            fprintf(f, "\"%c.%c - %d.%d\"", cursor->pieza, cursor->color, cursor->fila,cursor->columna);
        }else{
            while(cursor->next!=NULL){
                fprintf(f, "\"%c.%c - %d.%d\"", cursor->pieza, cursor->color, cursor->fila,cursor->columna);
                fprintf(f," -> ");
                fprintf(f, "\"%c.%c - %d.%d\"", cursor->next->pieza, cursor->next->color, cursor->next->fila,cursor->next->columna);
                cursor = cursor->next;
            }
        }
    }
    fprintf(f,"\n}");
    fclose(f);
    system("dot -Tpng </home/ferflo/Documentos/Qt/Graficas/linealizacion.dot >/home/ferflo/Documentos/Qt/Graficas/linealizacion.png");
}

void Matriz::recorrerFilas(int nivel)
{

    Encabezado * eFila = eFilas->primero;
    cout << "Recorrido Por Filas, Nivel "<<nivel<<": "<<endl;

    while(eFila != NULL)
    {
        Nodo * actual = eFila->acceso;
        while(actual != NULL)
        {
            //cout << actual->pieza << "." << actual->color;
            if(nivel==1 && actual->pieza != ' '){
                //cout << actual->fila << "." << actual->columna;
                cout << actual->pieza << "." << actual->color;
                linealidad->eque(linealidad,actual->pieza,actual->color,actual->fila,actual->columna);
                if(eFila->siguiente != NULL || actual->derecha != NULL)
                {
                    cout << " -> ";
                }
            }

            else if(nivel==0){
                if(actual->Nivel0){
                    //cout << actual->Nivel0->fila << "." << actual->Nivel0->columna;
                    cout << actual->Nivel0->pieza << "." << actual->Nivel0->color;
                    linealidad->eque(linealidad,actual->Nivel0->pieza,actual->Nivel0->color,actual->Nivel0->fila,actual->Nivel0->columna);
                    if(eFila->siguiente != NULL || actual->derecha != NULL)
                    {
                        cout << " -> ";
                    }
                }
            }

            else if(nivel==2){
                if(actual->Nivel2){
                    //cout << actual->Nivel2->fila << "." << actual->Nivel2->columna;
                    cout << actual->Nivel2->pieza << "." << actual->Nivel2->color;
                    linealidad->eque(linealidad,actual->Nivel2->pieza,actual->Nivel2->color,actual->Nivel2->fila,actual->Nivel2->columna);
                    if(eFila->siguiente != NULL || actual->derecha!= NULL)
                    {
                        cout << " -> ";

                    }
                }
            }
            actual = actual->derecha;
        }
        cout<<endl;
        eFila = eFila->siguiente;
    }

    cout << endl;

}

void Matriz::recorrerColumnas(int nivel)
{
    Encabezado * eColumna = eColumnas->primero;
    cout << "Recorrido Por Columnas, Nivel "<<nivel<<": "<<endl;

    while(eColumna != NULL)
    {
        Nodo * actual = eColumna->acceso;
        while(actual != NULL)
        {
            if(nivel==1 && actual->pieza != ' '){
                //cout << actual->fila << "." << actual->columna;
                cout << actual->pieza << "." << actual->color;
                linealidad->eque(linealidad,actual->pieza,actual->color,actual->fila,actual->columna);
                if(eColumna->siguiente != NULL || actual->abajo != NULL)
                {
                    cout << " -> ";
                }
            }

            else if(nivel==0){
                if(actual->Nivel0){
                    //cout << actual->Nivel0->fila << "." << actual->Nivel0->columna;
                    cout << actual->Nivel0->pieza << "." << actual->Nivel0->color;
                    linealidad->eque(linealidad,actual->Nivel0->pieza,actual->Nivel0->color,actual->Nivel0->fila,actual->Nivel0->columna);
                    if(eColumna->siguiente != NULL || actual->abajo != NULL)
                    {
                        cout << " -> ";
                    }
                }
            }

            else if(nivel==2){
                if(actual->Nivel2){
                    //cout << actual->Nivel2->fila << "." << actual->Nivel2->columna;
                    cout << actual->Nivel2->pieza << "." << actual->Nivel2->color;
                    linealidad->eque(linealidad,actual->Nivel2->pieza,actual->Nivel2->color,actual->Nivel2->fila,actual->Nivel2->columna);
                    if(eColumna->siguiente != NULL || actual->abajo!= NULL)
                    {
                        cout << " -> ";
                    }
                }
            }

            actual = actual->abajo;
        }
        cout<<endl;
        eColumna = eColumna->siguiente;
    }

    cout << endl;
}

