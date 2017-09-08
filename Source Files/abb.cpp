#include <abb.h>
#include <string.h>
ABB abb_crearNodo(char* usuario, int partidas_ganadas, int partidas_perdidas)
{
     ABB nuevoNodo = new(struct nodo);
     nuevoNodo->jugador = crearJugador(usuario,partidas_ganadas,partidas_perdidas);
     nuevoNodo->izq = NULL;
     nuevoNodo->der = NULL;

     return nuevoNodo;
}

void abb_insertar(ABB &arbol, char* usuario, int partidas_ganadas, int partidas_perdidas)
{
     if(arbol==NULL)
     {
           arbol = abb_crearNodo(usuario, partidas_ganadas,partidas_perdidas);
     }
     else if(strcmp(usuario,arbol->jugador->usuario)<0) //strcmp(usuario,arbol->jugador->usuario)<0  a < arbol->nro
          abb_insertar(arbol->izq,usuario,partidas_ganadas,partidas_perdidas);
     else if(strcmp(usuario,arbol->jugador->usuario)>0) //strcmp(usuario,arbol->jugador->usuario)>0  a > arbol->nro
          abb_insertar(arbol->der, usuario,partidas_ganadas,partidas_perdidas);
}

void abb_preOrden(ABB arbol)
{
     if(arbol!=NULL)
     {

          cout << arbol->jugador->usuario <<" ";
          abb_preOrden(arbol->izq);
          abb_preOrden(arbol->der);
     }
}

void abb_enOrden(ABB arbol)
{
     if(arbol!=NULL)
     {
          abb_enOrden(arbol->izq);
          cout << arbol->jugador->usuario << " ";
          abb_enOrden(arbol->der);
     }
}

void abb_postOrden(ABB arbol)
{
     if(arbol!=NULL)
     {
          abb_postOrden(arbol->izq);
          abb_postOrden(arbol->der);
          cout << arbol->jugador->usuario << " ";
     }
}

void abb_verArbol(ABB arbol, FILE *f)
{
     if(arbol!=NULL)
    {
         if(arbol->izq){
           cout << arbol->izq->jugador->usuario << " <- ";
           if(f){
           fprintf(f, "\"");
           fprintf(f,arbol->jugador->usuario);
           fprintf(f, "\"");
           fprintf(f, " -> ");
           fprintf(f, "\"");
           fprintf(f,arbol->izq->jugador->usuario);
           fprintf(f, "\";\n");
           }
         }if(arbol->izq||arbol->der){
         cout << arbol->jugador->usuario <<" ";
         }
         if(arbol->der){
             cout << " -> "<< arbol->der->jugador->usuario;
             if(f){
             fprintf(f, "\"");
             fprintf(f,arbol->jugador->usuario);
             fprintf(f, "\"");
             fprintf(f, " -> ");
             fprintf(f, "\"");
             fprintf(f,arbol->der->jugador->usuario);
             fprintf(f, "\";\n");
             }
         }
         cout << endl;
         abb_verArbol(arbol->izq, f);
         abb_verArbol(arbol->der, f);
    }

}

void abb_generar_imagen(ABB arbol){
    FILE *f = fopen("/home/ferflo/Documentos/Qt/Graficas/ABB.dot","w");
    fprintf(f,"digraph G {\n");
    fprintf(f,"\n\tgraph [splines=true overlap=false];\n");
    fprintf(f,"\tedge[color=\"#FF847C\"];\n");
    fprintf(f,"\tgraph [bgcolor=\"#2A363B\"];");
    fprintf(f,"\tnode[style=filled color=\"#99B898\" fillcolor=\"#2A363B\" fontname=\"Montzerat Light\" fontcolor=\"#FECEA8\" shape=rectangle];\n\n");

    abb_verArbol(arbol, f);

    fprintf(f,"\n}");
    fclose(f);
    system("dot -Tpng </home/ferflo/Documentos/Qt/Graficas/ABB.dot >/home/ferflo/Documentos/Qt/Graficas/ABB.png");

}

bool abb_esHoja(ABB root){
    if(!root->der && !root->izq)
        return true;
    return false;
}
bool abb_1hijoder(ABB root){
    if(root->der && !root->izq)
        return true;
    return false;
}
bool abb_1hijoizq(ABB root){
    if(!root->der && root->izq)
        return true;
    return false;
}
bool abb_2hijos(ABB root){
    if(root->der && root->izq)
        return true;
    return false;
}

ABB abb_nodo_mayor(ABB arbol){
    if(arbol->der){
        abb_nodo_mayor(arbol->der);
    }else{
        return arbol;
    }
}

ABB Padre(ABB padre, ABB hijo){
    if(padre->der == hijo || padre->izq == hijo){
        return padre;
    }else{
        if(strcmp(hijo->jugador->usuario, padre->jugador->usuario)>0){
            Padre(padre->der, hijo);
        }else{
            Padre(padre->izq, hijo);
        }
    }
}


void abb_eliminar(ABB arbol, ABB padre, char* usuario){
   Jugador aux;
    if(strcmp(usuario, padre->jugador->usuario)==0){

    }
   else if(strcmp(usuario, arbol->jugador->usuario)==0){
       if(abb_esHoja(arbol)){
            cout<<arbol->jugador->usuario << " es una hoja";
            cout<<", Su padre es: "<<padre->jugador->usuario << endl;
            if(strcmp(padre->der->jugador->usuario, arbol->jugador->usuario)==0){
                padre->der = NULL;
            }else{
                padre->izq = NULL;
            }
            free(arbol);
       }else if(abb_1hijoder(arbol)){
            cout<<arbol->jugador->usuario << " Tiene Hijo derecho"<<endl;
            cout<<", Su padre es: "<<padre->jugador->usuario << endl;
            if(padre->der){
                if(strcmp(padre->der->jugador->usuario, arbol->jugador->usuario)==0){
                    padre->der = arbol->der;
                }else{
                    padre->izq = arbol->der;
                }
            }else{
                padre->izq = arbol->der;
            }
            free(arbol);
       }else if(abb_1hijoizq(arbol)){
            cout<<arbol->jugador->usuario << " Tiene Hijo izquierdo"<<endl;
            cout<<", Su padre es: "<<padre->jugador->usuario << endl;
            if(padre->der){
                if(strcmp(padre->der->jugador->usuario, arbol->jugador->usuario)==0){
                    padre->der = arbol->izq;
                }else{
                    padre->izq = arbol->izq;
                }
            }else{
                padre->izq = arbol->izq;
            }
            free(arbol);
       }else if(abb_2hijos(arbol)){
            cout<<arbol->jugador->usuario << " Tiene dos hijos";
            cout<<" El padre es: "<<padre->jugador->usuario;
            ABB nodo = abb_nodo_mayor(arbol->izq);
            ABB p = Padre(padre,nodo);
            cout<<" Nodo mayor: "<<nodo->jugador->usuario;
            cout<<" Padre de nodo mayor: "<<p->jugador->usuario<<endl;
            if(p->der == nodo){
                 Padre(padre,nodo)->der = NULL;
            }else{
                Padre(padre,nodo)->izq = NULL;
            }
            aux.partidas_ganadas = arbol->jugador->partidas_ganadas;
            aux.partidas_perdidas = arbol->jugador->partidas_perdidas;
            aux.usuario = arbol->jugador->usuario;

            arbol->jugador->partidas_ganadas = nodo->jugador->partidas_ganadas;
            arbol->jugador->partidas_perdidas = nodo->jugador->partidas_perdidas;
            arbol->jugador->usuario = nodo->jugador->usuario;





       }
   }else{
        if(strcmp(usuario, arbol->jugador->usuario)>0){
            if(arbol->der){
                abb_eliminar(arbol->der, arbol, usuario);
            }else{
                cout<<"no se encontro el dato"<<endl;
            }
        }else if(strcmp(usuario, arbol->jugador->usuario)<0){
            if(arbol->izq){
                abb_eliminar(arbol->izq, arbol, usuario);
            }else{
                cout<<"no se encontro el dato"<<endl;
            }
        }
   }
}

Jugador *crearJugador(char* usuario, int partidas_ganadas, int partidas_perdidas){
    Jugador *a = (Jugador *)malloc(sizeof(Jugador));
    a->usuario = usuario;
    a->partidas_ganadas = partidas_ganadas;
    a->partidas_perdidas = partidas_perdidas;
    return a;
}
