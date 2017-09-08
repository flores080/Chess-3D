#include <logica.h>
#include <string.h>
using namespace std;
// ANDREA URIZA
int convLetra(char letra){
    switch (letra) {
    case 'A':
        return 7;
        break;
    case 'B':
        return 6;
        break;
    case 'C':
        return 5;
        break;
    case 'D':
        return 4;
        break;
    case 'E':
        return 3;
        break;
    case 'F':
        return 2;
        break;
    case 'G':
        return 1;
        break;
    case 'H':
        return 0;
        break;
    default:
        return -1;
        break;
    }
}

movimiento::movimiento(string mov){
    string pieza;
    string nivel;
    string movx;
    string movy;

    char * pch;
    pch = strtok((char*)mov.c_str(), "-");
    pieza = pch;
    pch = strtok(NULL, "-");
    nivel = pch;
    pch = strtok(NULL, "-");
    movx = pch[1];
    movy = pch[0];
    pch = strtok(NULL, "-");

    this->pieza = pieza[0];
    this->nivel = atoi(nivel.c_str());
    this->movx= atoi(movx.c_str())-1;
    this->movy = convLetra(movy[0]);
}

int difx(int x, int movx){
    return movx-x;
}
int dify(int y, int movy){
    return movy-y;
}

bool caminoVacioCaballo(Matriz * matriz, int y1, int x1, int y2, int x2, int nivel){
    if(!matriz->getValueAt(y1,x1,nivel)){
        if(!matriz->getValueAt(y2,x2,nivel)){
            return true;
        }else if(matriz->getValueAt(y2,x2,nivel)->pieza == ' '){
            return true;
        }
    }else if(matriz->getValueAt(y1,x1,nivel)->pieza == ' '){
        if(!matriz->getValueAt(y2,x2,nivel)){
            return true;
        }else if(matriz->getValueAt(y2,x2,nivel)->pieza == ' '){
            return true;
        }
    }
    return false;
}

bool moverPeonHacia(Matriz * matriz, Nodo * futuro, int posy_fut, int posx_fut,  int nivel, char color, char pieza){
    if(color == 'N'){
        /////////////////////////////////////////////////////////////////////////MOVIMIENTO SIMPLE ADELANTE
         if(matriz->getValueAt(posy_fut-1,posx_fut,nivel)){
            if(matriz->getValueAt(posy_fut-1,posx_fut,nivel)->pieza == pieza &&
               matriz->getValueAt(posy_fut-1,posx_fut,nivel)->color == color){
                if(!futuro || futuro->pieza == ' '){
                    matriz->eliminar(posy_fut-1, posx_fut, nivel);
                    return true;
                }
            }
         }
         /////////////////////////////////////////////////////////////////////////MOVIMIENTO DIAGONAL ADELANTE
         else if(matriz->getValueAt(posy_fut-1,posx_fut-1,nivel)){
             if(matriz->getValueAt(posy_fut-1,posx_fut-1,nivel)->pieza == pieza &&
                matriz->getValueAt(posy_fut-1,posx_fut-1,nivel)->color == color &&
                mismaPiezaDifNivel(matriz->getValueAt(posy_fut-1,posx_fut-1, 1), pieza, color, nivel) &&
                posy_fut-1 != 1 &&
                (!futuro || futuro->pieza == ' ')){
                    matriz->eliminar(posy_fut-1, posx_fut-1, nivel);
                    return true;
             }
         }else if(matriz->getValueAt(posy_fut-1,posx_fut+1,nivel)){
             if(matriz->getValueAt(posy_fut-1,posx_fut+1,nivel)->pieza == pieza &&
                matriz->getValueAt(posy_fut-1,posx_fut+1,nivel)->color == color &&
                mismaPiezaDifNivel(matriz->getValueAt(posy_fut-1,posx_fut+1, 1), pieza, color, nivel) &&
                posy_fut-1 != 1 &&
                (!futuro || futuro->pieza == ' ')){
                    matriz->eliminar(posy_fut-1, posx_fut+1, nivel);
                    return true;
             }
         }
         ////////////////////////////////////////////////////////////////////////COMER
         else if(matriz->getValueAt(posy_fut+1,posx_fut-1,nivel)){
             if(matriz->getValueAt(posy_fut+1,posx_fut-1,nivel)->pieza == pieza &&
                matriz->getValueAt(posy_fut+1,posx_fut-1,nivel)->color == color &&
                futuro && futuro->pieza != ' ' && futuro->color == 'B'){
                    matriz->eliminar(futuro->fila, futuro->columna, nivel);
                    matriz->eliminar(posy_fut+1, posx_fut-1, nivel);
                    return true;
             }else{
                 return false;
          }
         }else if(matriz->getValueAt(posy_fut+1,posx_fut+1,nivel)){
             if(matriz->getValueAt(posy_fut+1,posx_fut+1,nivel)->pieza == pieza &&
                matriz->getValueAt(posy_fut+1,posx_fut+1,nivel)->color == color &&
                futuro && futuro->pieza != ' ' && futuro->color == 'B'){
                    matriz->eliminar(futuro->fila, futuro->columna, nivel);
                    matriz->eliminar(posy_fut+1, posx_fut+1, nivel);
                    return true;
             }
         }

    }else{
        /////////////////////////////////////////////////////////////////////////MOVIMIENTO SIMPLE ADELANTE
        if(matriz->getValueAt(posy_fut+1,posx_fut,nivel)){
            if(matriz->getValueAt(posy_fut+1,posx_fut,nivel)->pieza == pieza &&
               matriz->getValueAt(posy_fut+1,posx_fut,nivel)->color == color){
                if(!futuro || futuro->pieza == ' '){
                    matriz->eliminar(posy_fut+1, posx_fut, nivel);
                    return true;
                }
            }
        }
        /////////////////////////////////////////////////////////////////////////MOVIMIENTO DIAGONAL ADELANTE
        else if(matriz->getValueAt(posy_fut+1,posx_fut-1,nivel)){//****
            if(matriz->getValueAt(posy_fut+1,posx_fut-1,nivel)->pieza == pieza &&
               matriz->getValueAt(posy_fut+1,posx_fut-1,nivel)->color == color &&
               mismaPiezaDifNivel(matriz->getValueAt(posy_fut+1,posx_fut-1, 1), pieza, color, nivel) &&
               posy_fut+1 != 6 &&
               (!futuro || futuro->pieza == ' ')){
                   matriz->eliminar(posy_fut+1, posx_fut-1, nivel);
                   return true;
            }
        }else if(matriz->getValueAt(posy_fut+1,posx_fut+1,nivel)){
            if(matriz->getValueAt(posy_fut+1,posx_fut+1,nivel)->pieza == pieza &&
               matriz->getValueAt(posy_fut+1,posx_fut+1,nivel)->color == color &&
               mismaPiezaDifNivel(matriz->getValueAt(posy_fut+1,posx_fut+1, 1), pieza, color, nivel) &&
               posy_fut+1 != 6 &&
               (!futuro || futuro->pieza == ' ')){
                   matriz->eliminar(posy_fut+1, posx_fut+1, nivel);
                   return true;
            }
        }
        ////////////////////////////////////////////////////////////////////////COMER
        else if(matriz->getValueAt(posy_fut-1,posx_fut-1,nivel)){
            if(matriz->getValueAt(posy_fut-1,posx_fut-1,nivel)->pieza == pieza &&
               matriz->getValueAt(posy_fut-1,posx_fut-1,nivel)->color == color &&
               futuro && futuro->pieza != ' ' && futuro->color == 'N'){
                   matriz->eliminar(futuro->fila, futuro->columna, nivel);
                   matriz->eliminar(posy_fut-1, posx_fut-1, nivel);
                   return true;
            }
        }else if(matriz->getValueAt(posy_fut-1,posx_fut+1,nivel)){
            if(matriz->getValueAt(posy_fut-1,posx_fut+1,nivel)->pieza == pieza &&
               matriz->getValueAt(posy_fut-1,posx_fut+1,nivel)->color == color &&
               futuro && futuro->pieza != ' ' && futuro->color == 'N'){
                   matriz->eliminar(futuro->fila, futuro->columna, nivel);
                   matriz->eliminar(posy_fut-1, posx_fut+1, nivel);
                   return true;
            }
        }
    }
    return false;
}
bool moverCaballoHacia(Matriz * matriz, Nodo * futuro, int posy_fut, int posx_fut,  int nivel, char color, char pieza){
    if(matriz->getValueAt(posy_fut-1,posx_fut+2,nivel)){
        cout<<"-1 +2"<<endl;
        if(matriz->getValueAt(posy_fut-1,posx_fut+2,nivel)->pieza == pieza &&
           matriz->getValueAt(posy_fut-1,posx_fut+2,nivel)->color == color &&
            (caminoVacioCaballo(matriz,posy_fut-1,posx_fut,posy_fut-1,posx_fut+1,nivel)||
             caminoVacioCaballo(matriz,posy_fut,posx_fut+1,posy_fut,posx_fut+2,nivel))){    ////////////////////// -1 || +-2 //YA
            if(!futuro || futuro->pieza == ' '){
                matriz->eliminar(posy_fut-1,posx_fut+2,nivel);
                return true;
            }else if(futuro && futuro->color!=color && futuro->color != ' '){
                matriz->eliminar(posy_fut-1,posx_fut+2,nivel);
                matriz->eliminar(futuro->fila,futuro->columna,nivel);
                return true;
            }
        }
    }
    if(matriz->getValueAt(posy_fut-1,posx_fut-2,nivel)){
        cout<<"-1 -2"<<endl;
        if(matriz->getValueAt(posy_fut-1,posx_fut-2,nivel)->pieza == pieza &&
           matriz->getValueAt(posy_fut-1,posx_fut-2,nivel)->color == color &&
                (caminoVacioCaballo(matriz,posy_fut-1,posx_fut,posy_fut-1,posx_fut-1,nivel)||
                 caminoVacioCaballo(matriz,posy_fut,posx_fut-1,posy_fut,posx_fut-2,nivel))){ ////                            //YA
            if(!futuro || futuro->pieza == ' '){
                matriz->eliminar(posy_fut-1,posx_fut-2,nivel);
                return true;
            }else if(futuro && futuro->color!=color && futuro->color != ' '){
                matriz->eliminar(posy_fut-1,posx_fut-2,nivel);
                matriz->eliminar(futuro->fila,futuro->columna,nivel);
                return true;
            }
        }
    }
    if(matriz->getValueAt(posy_fut+1,posx_fut+2,nivel)){
        cout<<"+1 +2"<<endl;
        if(matriz->getValueAt(posy_fut+1,posx_fut+2,nivel)->pieza == pieza &&
           matriz->getValueAt(posy_fut+1,posx_fut+2,nivel)->color == color &&
                (caminoVacioCaballo(matriz,posy_fut+1,posx_fut,posy_fut+1,posx_fut+1,nivel)||
                 caminoVacioCaballo(matriz,posy_fut,posx_fut+1,posy_fut,posx_fut+2,nivel))){////////////////////// +1 || +-2 //YA
            if(!futuro || futuro->pieza == ' '){
                matriz->eliminar(posy_fut+1,posx_fut+2,nivel);
                return true;
            }else if(futuro && futuro->color!=color && futuro->color != ' '){
                matriz->eliminar(posy_fut+1,posx_fut+2,nivel);
                matriz->eliminar(futuro->fila,futuro->columna,nivel);
                return true;
            }
        }
    }
    if(matriz->getValueAt(posy_fut+1,posx_fut-2,nivel)){
        cout<<"+1 -2"<<endl;
        if(matriz->getValueAt(posy_fut+1,posx_fut-2,nivel)->pieza == pieza &&
           matriz->getValueAt(posy_fut+1,posx_fut-2,nivel)->color == color &&
                (caminoVacioCaballo(matriz,posy_fut+1,posx_fut,posy_fut+1,posx_fut-1,nivel)||
                 caminoVacioCaballo(matriz,posy_fut,posx_fut-1,posy_fut,posx_fut-2,nivel))){///                             //YA
            if(!futuro || futuro->pieza == ' '){
                matriz->eliminar(posy_fut+1,posx_fut-2,nivel);
                return true;
            }else if(futuro && futuro->color!=color && futuro->color != ' '){
                matriz->eliminar(posy_fut+1,posx_fut-2,nivel);
                matriz->eliminar(futuro->fila,futuro->columna,nivel);
                return true;
            }
        }
    }
    if(matriz->getValueAt(posy_fut-2,posx_fut+1,nivel)){
        cout<<"-2 +1"<<endl;
        if(matriz->getValueAt(posy_fut-2,posx_fut+1,nivel)->pieza == pieza &&
           matriz->getValueAt(posy_fut-2,posx_fut+1,nivel)->color == color &&
           (caminoVacioCaballo(matriz,posy_fut-1,posx_fut,posy_fut-2,posx_fut,nivel)||
            caminoVacioCaballo(matriz,posy_fut,posx_fut+1,posy_fut-1,posx_fut+1,nivel))){////////////////////// -2 || +-1  //YA
            if(!futuro || futuro->pieza == ' '){
                matriz->eliminar(posy_fut-2,posx_fut+1,nivel);
                return true;
            }else if(futuro && futuro->color!=color && futuro->color != ' '){
                matriz->eliminar(posy_fut-2,posx_fut+1,nivel);
                matriz->eliminar(futuro->fila,futuro->columna,nivel);
                return true;
            }
        }
    }
    if(matriz->getValueAt(posy_fut-2,posx_fut-1,nivel)){
        cout<<"-2 -1"<<endl;
        if(matriz->getValueAt(posy_fut-2,posx_fut-1,nivel)->pieza == pieza &&
           matriz->getValueAt(posy_fut-2,posx_fut-1,nivel)->color == color &&
           (caminoVacioCaballo(matriz,posy_fut-1,posx_fut,posy_fut-2,posx_fut,nivel)||
            caminoVacioCaballo(matriz,posy_fut,posx_fut-1,posy_fut-1,posx_fut-1,nivel))){///                               //YA
            if(!futuro || futuro->pieza == ' '){
                matriz->eliminar(posy_fut-2,posx_fut-1,nivel);
                return true;
            }else if(futuro && futuro->color!=color && futuro->color != ' '){
                matriz->eliminar(posy_fut-2,posx_fut-1,nivel);
                matriz->eliminar(futuro->fila,futuro->columna,nivel);
                return true;
            }
        }
    }
    if(matriz->getValueAt(posy_fut+2,posx_fut+1,nivel)){
        cout<<"+2 +1"<<endl;
        if(matriz->getValueAt(posy_fut+2,posx_fut+1,nivel)->pieza == pieza &&
           matriz->getValueAt(posy_fut+2,posx_fut+1,nivel)->color == color &&
           (caminoVacioCaballo(matriz,posy_fut+1,posx_fut,posy_fut+2,posx_fut,nivel)||
            caminoVacioCaballo(matriz,posy_fut,posx_fut+1,posy_fut+1,posx_fut+1,nivel))){////////////////////// +2 || +-1 //YA
            if(!futuro || futuro->pieza == ' '){
                matriz->eliminar(posy_fut+2,posx_fut+1,nivel);
                return true;
            }else if(futuro && futuro->color!=color && futuro->color != ' '){
                matriz->eliminar(posy_fut+2,posx_fut+1,nivel);
                matriz->eliminar(futuro->fila,futuro->columna,nivel);
                return true;
            }
        }
    }
    if(matriz->getValueAt(posy_fut+2,posx_fut-1,nivel)){
        cout<<"+2 -1"<<endl;
        if(matriz->getValueAt(posy_fut+2,posx_fut-1,nivel)->pieza == pieza &&
           matriz->getValueAt(posy_fut+2,posx_fut-1,nivel)->color == color &&
                (caminoVacioCaballo(matriz,posy_fut+1,posx_fut,posy_fut+2,posx_fut,nivel)||
                 caminoVacioCaballo(matriz,posy_fut,posx_fut-1,posy_fut+1,posx_fut-1,nivel))){///                       //YA
            if(!futuro || futuro->pieza == ' '){
                matriz->eliminar(posy_fut+2,posx_fut-1,nivel);
                return true;
            }else if(futuro && futuro->color!=color && futuro->color != ' '){
                matriz->eliminar(posy_fut+2,posx_fut-1,nivel);
                matriz->eliminar(futuro->fila,futuro->columna,nivel);
                return true;
            }
        }
    }
    return false;
}


bool moverTorreHacia(Matriz * matriz, Nodo * futuro, int posy_fut, int posx_fut,  int nivel, char color, char pieza){
    int y = posy_fut;
    int x = posx_fut;
    if(mismaPiezaDifNivel(matriz->getValueAt(y,x,1),pieza,color,nivel)){
        int niv = misma_Torre_nivel(matriz,matriz->getValueAt(y,x,1),pieza,color,nivel);
        if(!futuro){
            if(niv!=-1){
                matriz->eliminar(y,x,niv);
                return true;
            }
        }else if(futuro){
            if(futuro->pieza == ' '){
                if(niv!=-1){
                    matriz->eliminar(y,x,niv);
                    return true;
                }
            }
        }else{
            return false;
        }

    }
    while(y>=0 && x<=7){
        if(matriz->getValueAt(y,x,nivel)){
            if(matriz->getValueAt(y,x,nivel)->pieza == pieza &&
               matriz->getValueAt(y,x,nivel)->color == color){
                if(!futuro){
                    matriz->eliminar(y,x,nivel);
                    return true;
                }else if(futuro){
                    if(futuro->pieza == ' '){
                        matriz->eliminar(y,x,nivel);
                        return true;
                    }else if(futuro->color != color){
                        matriz->eliminar(y,x,nivel);
                        return true;
                    }else{
                        return false;
                    }
                }
            }else if(y!=posy_fut && x!=posx_fut && matriz->getValueAt(y,x,nivel)->pieza != ' '){
                break;
            }
        }
        y--;
        x++;
    } // y-- x++

    y = posy_fut;
    x = posx_fut;
    while(y>=0 && x>=0){
        if(matriz->getValueAt(y,x,nivel)){
            if(matriz->getValueAt(y,x,nivel)->pieza == pieza &&
               matriz->getValueAt(y,x,nivel)->color == color){
                if(!futuro){
                    matriz->eliminar(y,x,nivel);
                    return true;
                }else if(futuro){
                    if(futuro->pieza == ' '){
                        matriz->eliminar(y,x,nivel);
                        return true;
                    }else if(futuro->color != color){
                        matriz->eliminar(y,x,nivel);
                        return true;
                    }else{
                        return false;
                    }
                }
            }else if(y!=posy_fut && x!=posx_fut && matriz->getValueAt(y,x,nivel)->pieza != ' '){
                break;
            }
        }
        y--;
        x--;
    } // y-- x--
    y = posy_fut;
    x = posx_fut;
    while(y<=7 && x>=0){
        if(matriz->getValueAt(y,x,nivel)){
            if(matriz->getValueAt(y,x,nivel)->pieza == pieza &&
               matriz->getValueAt(y,x,nivel)->color == color){
                if(!futuro){
                    matriz->eliminar(y,x,nivel);
                    return true;
                }else if(futuro){
                    if(futuro->pieza == ' '){
                        matriz->eliminar(y,x,nivel);
                        return true;
                    }else if(futuro->color != color){
                        matriz->eliminar(y,x,nivel);
                        return true;
                    }else{
                        return false;
                    }
                }
            }else if(y!=posy_fut && x!=posx_fut && matriz->getValueAt(y,x,nivel)->pieza != ' '){
                break;
            }
        }

        y++;
        x--;
    } // y++ x--

    y = posy_fut;
    x = posx_fut;
    while(y<=7 && x<=7){
        if(matriz->getValueAt(y,x,nivel)){
            if(matriz->getValueAt(y,x,nivel)->pieza == pieza &&
               matriz->getValueAt(y,x,nivel)->color == color){
                if(!futuro){
                    matriz->eliminar(y,x,nivel);
                    return true;
                }else if(futuro){
                    if(futuro->pieza == ' '){
                        matriz->eliminar(y,x,nivel);
                        return true;
                    }else if(futuro->color != color){
                        matriz->eliminar(y,x,nivel);
                        return true;
                    }else{
                        return false;
                    }
                }
            }else if(y!=posy_fut && x!=posx_fut && matriz->getValueAt(y,x,nivel)->pieza != ' '){
                break;
            }
        }

        y++;
        x++;
    } // y++ x++
    return false;
}
bool moverAlfilHacia(Matriz * matriz, Nodo * futuro, int posy_fut, int posx_fut,  int nivel, char color, char pieza){
    int x = posx_fut;
    int y = posy_fut;
    if(mismaPiezaDifNivel(matriz->getValueAt(y,x,1),pieza,color,nivel)){
        int niv = mismo_Alfil_nivel(matriz,matriz->getValueAt(y,x,1),pieza,color,nivel);
        if(!futuro){
            if(niv!=-1){
                matriz->eliminar(y,x,niv);
                return true;
            }
        }else if(futuro){
            if(futuro->pieza == ' '){
                if(niv!=-1){
                    matriz->eliminar(y,x,niv);
                    return true;
                }
            }
        }else{
            return false;
        }

    }
    while(y>=0){ //Arriba
        if(matriz->getValueAt(y,x,nivel)){
            if(matriz->getValueAt(y,x,nivel)->pieza == pieza &&
               matriz->getValueAt(y,x,nivel)->color == color){
                if(!futuro){
                    matriz->eliminar(y,x,nivel);
                    return true;
                }else if(futuro){
                    if(futuro->pieza == ' '){
                        matriz->eliminar(y,x,nivel);
                        return true;
                    }else if(futuro->color != color){
                        matriz->eliminar(y,x,nivel);
                        return true;
                    }else{
                        return false;
                    }
                }
            }else if(y!=posy_fut && matriz->getValueAt(y,x,nivel)->pieza != ' '){
                break;
            }
        }
        y--;
    }
    x = posx_fut;
    y = posy_fut;
    while(y<=7){ //Abajo
        if(matriz->getValueAt(y,x,nivel)){
            if(matriz->getValueAt(y,x,nivel)->pieza == pieza &&
               matriz->getValueAt(y,x,nivel)->color == color){
                if(!futuro){
                    matriz->eliminar(y,x,nivel);
                    return true;
                }else if(futuro){
                    if(futuro->pieza == ' '){
                        matriz->eliminar(y,x,nivel);
                        return true;
                    }else if(futuro->color != color){
                        matriz->eliminar(y,x,nivel);
                        return true;
                    }else{
                        return false;
                    }
                }
            }else if(y!=posy_fut && matriz->getValueAt(y,x,nivel)->pieza != ' '){
                break;
            }
        }
        y++;
    }
    x = posx_fut;
    y = posy_fut;
    while(x>=0){ //Derecha
        if(matriz->getValueAt(y,x,nivel)){
            if(matriz->getValueAt(y,x,nivel)->pieza == pieza &&
               matriz->getValueAt(y,x,nivel)->color == color){
                if(!futuro){
                    matriz->eliminar(y,x,nivel);
                    return true;
                }else if(futuro){
                    if(futuro->pieza == ' '){
                        matriz->eliminar(y,x,nivel);
                        return true;
                    }else if(futuro->color != color){
                        matriz->eliminar(y,x,nivel);
                        return true;
                    }else{
                        return false;
                    }
                }
            }else if(x!=posx_fut && matriz->getValueAt(y,x,nivel)->pieza != ' '){
                break;
            }
        }
        x--;
    }
    x = posx_fut;
    y = posy_fut;
    while(x<=7){ //Izquierda
        if(matriz->getValueAt(y,x,nivel)){
            if(matriz->getValueAt(y,x,nivel)->pieza == pieza &&
               matriz->getValueAt(y,x,nivel)->color == color){
                if(!futuro){
                    matriz->eliminar(y,x,nivel);
                    return true;
                }else if(futuro){
                    if(futuro->pieza == ' '){
                        matriz->eliminar(y,x,nivel);
                        return true;
                    }else if(futuro->color != color){
                        matriz->eliminar(y,x,nivel);
                        return true;
                    }else{
                        return false;
                    }
                }
            }else if(x!=posx_fut && matriz->getValueAt(y,x,nivel)->pieza != ' '){
                break;
            }
        }
        x++;
    }

    return false;
}


bool moverReylHacia(Matriz * matriz, Nodo * futuro, int posy_fut, int posx_fut,  int nivel, char color, char pieza){
    if(mismaPiezaDifNivel(matriz->getValueAt(posy_fut,posx_fut,1),pieza,color,nivel)){
        int niv = misma_pieza_nivel(matriz->getValueAt(posy_fut,posx_fut,1),pieza,color,nivel);
        if(!futuro){
            if(niv!=-1){
                matriz->eliminar(posy_fut,posx_fut,niv);
                return true;
            }
        }else if(futuro){
            if(futuro->pieza == ' '){
                if(niv!=-1){
                    matriz->eliminar(posy_fut,posx_fut,niv);
                    return true;
                }
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
    if(moverAlfilHacia(matriz,futuro,posy_fut,posx_fut,nivel,color,pieza)||
       moverTorreHacia(matriz,futuro,posy_fut,posx_fut,nivel,color,pieza)){
        return true;
    }
    return false;
}

bool casillavacia(Matriz * matriz, int _y, int _x, int nivel){
    if(!matriz->getValueAt(_y,_x,nivel)||matriz->getValueAt(_y,_x,nivel)->pieza == ' '){
        return true;
    }
    return false;
}

bool reyAlrededor(Matriz * matriz, int _y, int _x, int nivel){
    if(matriz->getValueAt(_y+1,_x,nivel)){
        if(matriz->getValueAt(_y+1,_x,nivel)->pieza == 'R'){
            return true;
        }
    }if(matriz->getValueAt(_y-1,_x,nivel)){
        if(matriz->getValueAt(_y-1,_x,nivel)->pieza == 'R'){
            return true;
        }
    }if(matriz->getValueAt(_y,_x+1,nivel)){
        if(matriz->getValueAt(_y,_x+1,nivel)->pieza == 'R'){
            return true;
        }
    }if(matriz->getValueAt(_y,_x-1,nivel)){
        if(matriz->getValueAt(_y,_x-1,nivel)->pieza == 'R'){
            return true;
        }
    }if(matriz->getValueAt(_y+1,_x+1,nivel)){
        if(matriz->getValueAt(_y+1,_x+1,nivel)->pieza == 'R'){
            return true;
        }
    }if(matriz->getValueAt(_y-1,_x-1,nivel)){
        if(matriz->getValueAt(_y-1,_x-1,nivel)->pieza == 'R'){
            return true;
        }
    }if(matriz->getValueAt(_y+1,_x-1,nivel)){
        if(matriz->getValueAt(_y+1,_x-1,nivel)->pieza == 'R'){
            return true;
        }
    }if(matriz->getValueAt(_y-1,_x+1,nivel)){
        if(matriz->getValueAt(_y-1,_x+1,nivel)->pieza == 'R'){
            return true;
        }
    }
    return false;
}

bool moverReynalHacia(Matriz * matriz, Nodo * futuro, int posy_fut, int posx_fut,  int nivel, char color, char pieza){
    if(mismaPiezaDifNivel(matriz->getValueAt(posy_fut,posx_fut,1),pieza,color,nivel)){
        int niv = misma_pieza_nivel(matriz->getValueAt(posy_fut,posx_fut,1),pieza,color,nivel);
        cout<<"misma pieza"<<endl;
        if(reyAlrededor(matriz,posy_fut,posx_fut,niv)){
            if(!futuro){
                if(niv!=-1){
                    matriz->eliminar(posy_fut,posx_fut,niv);
                    return true;
                }
            }else if(futuro){
                if(futuro->pieza == ' '){
                    if(niv!=-1){
                        matriz->eliminar(posy_fut,posx_fut,niv);
                        return true;
                    }
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }
    }

    if(matriz->getValueAt(posy_fut-1, posx_fut,nivel)){
        if(matriz->getValueAt(posy_fut-1, posx_fut,nivel)->pieza == pieza &&
           matriz->getValueAt(posy_fut-1, posx_fut,nivel)->color == color){
            if(!futuro || futuro->pieza == ' '){
                matriz->eliminar(posy_fut-1, posx_fut, nivel);
                return true;
            }else if(futuro->color!=color){
                matriz->eliminar(posy_fut-1, posx_fut, nivel);
                return true;
            }
        }
    }if(matriz->getValueAt(posy_fut-2,posx_fut,nivel)){
        if(matriz->getValueAt(posy_fut-2,posx_fut,nivel)->pieza == pieza &&
                matriz->getValueAt(posy_fut-2, posx_fut,nivel)->color == color){
            if(!futuro || futuro->pieza == ' '){
                matriz->eliminar(posy_fut-2, posx_fut, nivel);
                return true;
            }else if(futuro->color!=color){
                matriz->eliminar(posy_fut-2, posx_fut, nivel);
                return true;
            }
        }
    }

    if(matriz->getValueAt(posy_fut+1,posx_fut,nivel)){
        if(matriz->getValueAt(posy_fut+1,posx_fut,nivel)->pieza == pieza &&
                matriz->getValueAt(posy_fut+1, posx_fut,nivel)->color == color){
        if(!futuro || futuro->pieza == ' '){
            matriz->eliminar(posy_fut+1, posx_fut, nivel);
            return true;
        }else if(futuro->color!=color){
            matriz->eliminar(posy_fut+1, posx_fut, nivel);
            return true;
        }
        }
    }if(matriz->getValueAt(posy_fut+2,posx_fut,nivel)){
        if(matriz->getValueAt(posy_fut+2,posx_fut,nivel)->pieza == pieza  &&
                matriz->getValueAt(posy_fut+2, posx_fut,nivel)->color == color){
        if(!futuro || futuro->pieza == ' '){
            matriz->eliminar(posy_fut+2, posx_fut, nivel);
            return true;
        }else if(futuro->color!=color){
            matriz->eliminar(posy_fut+2, posx_fut, nivel);
            return true;
        }
        }
    }

    if(matriz->getValueAt(posy_fut,posx_fut-1,nivel)){
        if(matriz->getValueAt(posy_fut,posx_fut-1,nivel)->pieza == pieza &&
                matriz->getValueAt(posy_fut, posx_fut-1,nivel)->color == color){
        if(!futuro || futuro->pieza == ' '){
            matriz->eliminar(posy_fut, posx_fut-1, nivel);
            return true;
        }else if(futuro->color!=color){
            matriz->eliminar(posy_fut, posx_fut-1, nivel);
            return true;
        }
        }
    }if(matriz->getValueAt(posy_fut,posx_fut-2,nivel)){
        if(matriz->getValueAt(posy_fut,posx_fut-2,nivel)->pieza == pieza &&
                matriz->getValueAt(posy_fut, posx_fut-2,nivel)->color == color){
        if(!futuro || futuro->pieza == ' '){
            matriz->eliminar(posy_fut, posx_fut-2, nivel);
            return true;
        }else if(futuro->color!=color){
            matriz->eliminar(posy_fut, posx_fut-2, nivel);
            return true;
        }
        }
    }

    if(matriz->getValueAt(posy_fut,posx_fut+1,nivel)){
        if(matriz->getValueAt(posy_fut,posx_fut+1,nivel)->pieza == pieza &&
                matriz->getValueAt(posy_fut, posx_fut+1,nivel)->color == color){
        if(!futuro || futuro->pieza == ' '){
            matriz->eliminar(posy_fut, posx_fut+1, nivel);
            return true;
        }else if(futuro->color!=color){
            matriz->eliminar(posy_fut, posx_fut+1, nivel);
            return true;
        }
        }
    }if(matriz->getValueAt(posy_fut,posx_fut+2,nivel)){
        if(matriz->getValueAt(posy_fut,posx_fut+2,nivel)->pieza == pieza &&
                matriz->getValueAt(posy_fut, posx_fut+2,nivel)->color == color){
        if(!futuro || futuro->pieza == ' '){
            matriz->eliminar(posy_fut, posx_fut+2, nivel);
            return true;
        }else if(futuro->color!=color){
            matriz->eliminar(posy_fut, posx_fut+2, nivel);
            return true;
        }
        }
    }

    if(matriz->getValueAt(posy_fut-1,posx_fut-1,nivel)){
        if(matriz->getValueAt(posy_fut-1,posx_fut-1,nivel)->pieza == pieza &&
                matriz->getValueAt(posy_fut-1, posx_fut-1,nivel)->color == color){
        if(!futuro || futuro->pieza == ' '){
            matriz->eliminar(posy_fut-1, posx_fut-1, nivel);
            return true;
        }else if(futuro->color!=color){
            matriz->eliminar(posy_fut-1, posx_fut-1, nivel);
            return true;
        }
        }
    }if(matriz->getValueAt(posy_fut-2,posx_fut-2,nivel)){
        if(matriz->getValueAt(posy_fut-2,posx_fut-2,nivel)->pieza == pieza &&
                matriz->getValueAt(posy_fut-2, posx_fut-2,nivel)->color == color){
        if(!futuro || futuro->pieza == ' '){
            matriz->eliminar(posy_fut-2, posx_fut-2, nivel);
            return true;
        }else if(futuro->color!=color){
            matriz->eliminar(posy_fut-2, posx_fut-2, nivel);
            return true;
        }
        }
    }

    if(matriz->getValueAt(posy_fut+1,posx_fut+1,nivel)){
        if(matriz->getValueAt(posy_fut+1,posx_fut+1,nivel)->pieza == pieza &&
                matriz->getValueAt(posy_fut+1, posx_fut+1,nivel)->color == color){
        if(!futuro || futuro->pieza == ' '){
            matriz->eliminar(posy_fut+1, posx_fut+1, nivel);
            return true;
        }else if(futuro->color!=color){
            matriz->eliminar(posy_fut+1, posx_fut+1, nivel);
            return true;
        }
        }
    }if(matriz->getValueAt(posy_fut+2,posx_fut+2,nivel)){
        if(matriz->getValueAt(posy_fut+2,posx_fut+2,nivel)->pieza == pieza &&
                matriz->getValueAt(posy_fut+2, posx_fut+2,nivel)->color == color){
        if(!futuro || futuro->pieza == ' '){
            matriz->eliminar(posy_fut+2, posx_fut+2, nivel);
            return true;
        }else if(futuro->color!=color){
            matriz->eliminar(posy_fut+2, posx_fut+2, nivel);
            return true;
        }
        }
    }

    if(matriz->getValueAt(posy_fut-1, posx_fut+1,nivel)){
        if(matriz->getValueAt(posy_fut-1, posx_fut+1,nivel)->pieza == pieza &&
                matriz->getValueAt(posy_fut-1, posx_fut+1,nivel)->color == color){
        if(!futuro || futuro->pieza == ' '){
            matriz->eliminar(posy_fut-1, posx_fut+1, nivel);
            return true;
        }else if(futuro->color!=color){
            matriz->eliminar(posy_fut-1, posx_fut+1, nivel);
            return true;
        }
        }
    }if(matriz->getValueAt(posy_fut-2,posx_fut+2,nivel)){
        if(matriz->getValueAt(posy_fut-2,posx_fut+2,nivel)->pieza == pieza &&
                matriz->getValueAt(posy_fut-2, posx_fut+2,nivel)->color == color){
        if(!futuro || futuro->pieza == ' '){
            matriz->eliminar(posy_fut-2, posx_fut+2, nivel);
            return true;
        }else if(futuro->color!=color){
            matriz->eliminar(posy_fut-2, posx_fut+2, nivel);
            return true;
        }
        }
    }

    if(matriz->getValueAt(posy_fut+1, posx_fut-1,nivel)){
        if(matriz->getValueAt(posy_fut+1, posx_fut-1,nivel)->pieza == pieza &&
                matriz->getValueAt(posy_fut+1, posx_fut-1,nivel)->color == color){
        if(!futuro || futuro->pieza == ' '){
            matriz->eliminar(posy_fut+1, posx_fut-1, nivel);
            return true;
        }else if(futuro->color!=color){
            matriz->eliminar(posy_fut+1, posx_fut-1, nivel);
            return true;
        }
        }
    }if(matriz->getValueAt(posy_fut+2,posx_fut-2,nivel)){
        if(matriz->getValueAt(posy_fut+2,posx_fut-2,nivel)->pieza == pieza &&
                matriz->getValueAt(posy_fut+2, posx_fut-2,nivel)->color == color){
        if(!futuro || futuro->pieza == ' '){
            matriz->eliminar(posy_fut+2, posx_fut-2, nivel);
            return true;
        }else if(futuro->color!=color){
            matriz->eliminar(posy_fut+2, posx_fut-2, nivel);
            return true;
        }
        }
    }
    return false;
}





bool mismaPiezaDifNivel(Nodo* nodo, char pieza, char color, int nivel){
    if(nodo){
        if(nivel == 0 ){
            if(nodo->pieza == pieza &&
               nodo->color == color){
                return true;
            }else if(nodo->Nivel2){
                if(nodo->Nivel2->pieza == pieza &&
                   nodo->Nivel2->color == color){
                    return true;
                }
            }
        }else if(nivel == 1){
            if(nodo->Nivel0){
                if(nodo->Nivel0->pieza == pieza &&
                   nodo->Nivel0->color == color){
                    return true;
                }
            }else if(nodo->Nivel2){
                if(nodo->Nivel2->pieza == pieza &&
                   nodo->Nivel2->color == color){
                    return true;
                }
            }
        }else if(nivel == 2){
            if(nodo->pieza == pieza &&
               nodo->color == color){
                return true;
            }else if(nodo->Nivel0){
                if(nodo->Nivel0->pieza == pieza &&
                   nodo->Nivel0->color == color){
                    return true;
                }
            }
        }
    }
    return false;
}

int misma_Torre_nivel(Matriz * matriz, Nodo * nodo, char pieza, char color, int nivel){
    if(nivel == 0 ){
        if(nodo->pieza == pieza &&
           nodo->color == color &&
           sepuedesubirTorre(matriz, nodo->fila,nodo->columna,pieza,color,1)){
            return 1;
        }else if(nodo->Nivel2){
            if(nodo->Nivel2->pieza == pieza &&
               nodo->Nivel2->color == color &&
               sepuedesubirTorre(matriz, nodo->fila,nodo->columna,pieza,color,2)){
                return 2;
            }
        }
    }else if(nivel == 1){
        if(nodo->Nivel0){
            if(nodo->Nivel0->pieza == pieza &&
               nodo->Nivel0->color == color &&
               sepuedesubirTorre(matriz, nodo->fila,nodo->columna,pieza,color,0)){
                return 0;
            }
        }else if(nodo->Nivel2){
            if(nodo->Nivel2->pieza == pieza &&
               nodo->Nivel2->color == color &&
               sepuedesubirTorre(matriz, nodo->fila,nodo->columna,pieza,color,2)){
                return 2;
            }
        }
    }else if(nivel == 2){
        if(nodo->pieza == pieza &&
           nodo->color == color &&
           sepuedesubirTorre(matriz, nodo->fila,nodo->columna,pieza,color,1)){
            return 1;
        }else if(nodo->Nivel0){
            if(nodo->Nivel0->pieza == pieza &&
               nodo->Nivel0->color == color &&
               sepuedesubirTorre(matriz, nodo->fila,nodo->columna,pieza,color,0)){
                return 0;
            }
        }
    }
    return -1;
}

int mismo_Alfil_nivel(Matriz * matriz, Nodo * nodo, char pieza, char color, int nivel){
    if(nivel == 0 ){
        if(nodo->pieza == pieza &&
           nodo->color == color &&
           sepuedesubirAlfil(matriz, nodo->fila,nodo->columna,pieza,color,1)){
            return 1;
        }else if(nodo->Nivel2){
            if(nodo->Nivel2->pieza == pieza &&
               nodo->Nivel2->color == color &&
               sepuedesubirAlfil(matriz, nodo->fila,nodo->columna,pieza,color,2)){
                return 2;
            }
        }
    }else if(nivel == 1){
        if(nodo->Nivel0){
            if(nodo->Nivel0->pieza == pieza &&
               nodo->Nivel0->color == color &&
               sepuedesubirAlfil(matriz, nodo->fila,nodo->columna,pieza,color,0)){
                return 0;
            }
        }else if(nodo->Nivel2){
            if(nodo->Nivel2->pieza == pieza &&
               nodo->Nivel2->color == color &&
               sepuedesubirAlfil(matriz, nodo->fila,nodo->columna,pieza,color,2)){
                return 2;
            }
        }
    }else if(nivel == 2){
        if(nodo->pieza == pieza &&
           nodo->color == color &&
           sepuedesubirAlfil(matriz, nodo->fila,nodo->columna,pieza,color,1)){
            return 1;
        }else if(nodo->Nivel0){
            if(nodo->Nivel0->pieza == pieza &&
               nodo->Nivel0->color == color &&
               sepuedesubirAlfil(matriz, nodo->fila,nodo->columna,pieza,color,0)){
                return 0;
            }
        }
    }
    return -1;
}

int misma_pieza_nivel(Nodo * nodo, char pieza, char color, int nivel){
    if(nivel == 0 ){
        if(nodo->pieza == pieza &&
           nodo->color == color){
            return 1;
        }else if(nodo->Nivel2){
            if(nodo->Nivel2->pieza == pieza &&
               nodo->Nivel2->color == color){
                return 2;
            }
        }
    }else if(nivel == 1){
        if(nodo->Nivel0){
            if(nodo->Nivel0->pieza == pieza &&
               nodo->Nivel0->color == color){
                return 0;
            }
        }else if(nodo->Nivel2){
            if(nodo->Nivel2->pieza == pieza &&
               nodo->Nivel2->color == color){
                return 2;
            }
        }
    }else if(nivel == 2){
        if(nodo->pieza == pieza &&
           nodo->color == color){
            return 1;
        }else if(nodo->Nivel0){
            if(nodo->Nivel0->pieza == pieza &&
               nodo->Nivel0->color == color){
                return 0;
            }
        }
    }
    return -1;
}


bool sepuedesubirTorre(Matriz * matriz, int _y, int _x, char pieza, char color, int nivel){
    int x=_x;
    int y=_y;
    int z= nivel;

    while(y>=0){ //Arriba
        if(matriz->getValueAt(y,x,z) && y!=_y){
            if(matriz->getValueAt(y,x,z)->pieza == pieza &&
               matriz->getValueAt(y,x,z)->color == color){
                return true;
            }
        }
        y--;
    }
    x = _x;
    y = _y;
    while(y<=7){ //Abajo
        if(matriz->getValueAt(y,x,z) && y!=_y){
            if(matriz->getValueAt(y,x,z)->pieza == pieza &&
               matriz->getValueAt(y,x,z)->color == color){
                return true;
            }
        }
        y++;
    }
    x = _x;
    y = _y;
    while(x>=0){ //Derecha
        if(matriz->getValueAt(y,x,z) && x!=_x){
            if(matriz->getValueAt(y,x,z)->pieza == pieza &&
               matriz->getValueAt(y,x,z)->color == color){
                return true;
            }
        }
        x--;
    }
    x = _x;
    y = _y;
    while(x<=7){ //Izquierda
        if(matriz->getValueAt(y,x,z) && x!=_x){
            if(matriz->getValueAt(y,x,z)->pieza == pieza &&
               matriz->getValueAt(y,x,z)->color == color){
                return true;
            }
        }
        x++;
    }
}

bool sepuedesubirAlfil(Matriz * matriz, int _y, int _x, char pieza, char color, int nivel){
    int x=_x;
    int y=_y;
    int z= nivel;

    while(y>=0 && x<=7){
        if(matriz->getValueAt(y,x,z) && y!=_y && x!=_x){
            if(matriz->getValueAt(y,x,z)->pieza == pieza &&
               matriz->getValueAt(y,x,z)->color == color){
                return true;
            }
        }
        y--;
        x++;
    } // y-- x++

    cout<<endl;
    y = _y;
    x = _x;
    while(y>=0 && x>=0){
        if(matriz->getValueAt(y,x,z) && y!=_y && x!=_x){
            if(matriz->getValueAt(y,x,z)->pieza == pieza &&
               matriz->getValueAt(y,x,z)->color == color){
                return true;
            }
        }
        y--;
        x--;
    } // y-- x--
    cout<<endl;
    y = _y;
    x = _x;
    while(y<=7 && x>=0){
        if(matriz->getValueAt(y,x,z) && y!=_y && x!=_x){
            if(matriz->getValueAt(y,x,z)->pieza == pieza &&
               matriz->getValueAt(y,x,z)->color == color){
                return true;
            }
        }
        y++;
        x--;
    } // y++ x--

    cout<<endl;
    y = _y;
    x = _x;
    while(y<=7 && x<=7){
        if(matriz->getValueAt(y,x,z) && y!=_y && x!=_x){
            if(matriz->getValueAt(y,x,z)->pieza == pieza &&
               matriz->getValueAt(y,x,z)->color == color){
                return true;
            }
        }
        y++;
        x++;
    } // y++ x++

}
