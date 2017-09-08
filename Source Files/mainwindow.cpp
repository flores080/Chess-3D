#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QVBoxLayout"
#include <qmessagebox.h>
#include <qthread.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    blancas = 0;
    negras = 0;
    Timer = new QTimer(this);
    connect(Timer,SIGNAL(timeout()),this,SLOT(crono()));
    ui->setupUi(this);
    ui->no_tablero->hide();
    ui->tipo_linealizacion->hide();
    this->setGeometry(96,52,1170,700);
    turno = 0;
    matriz = new Matriz();
    arbol = NULL;
    setPiezas();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete matriz;
}
void MainWindow::crono(){
    if(min==0){
        tiempo--;
        min = 59;
    }else{
        min--;
    }
    if(min==0 && tiempo ==0){
        Nodo * tmp;
        for(int i=0; i<3; i++){
            for(int j=0; j<8; j++){
                for(int k=0; k<8; k++){
                    tmp = matriz->getValueAt(j,k,i);
                    if(tmp){
                        if(tmp->color == 'N'){
                            negras++;
                        }else if(tmp->color == 'B'){
                            blancas++;
                        }
                    }
                }
            }
        }
        if(negras>blancas){
             QMessageBox::information(this,"!","Gano Jugador Negro");
        }else if(blancas>negras){
            QMessageBox::information(this,"!","Gano Jugador Blanco");
        }else{
            QMessageBox::information(this,"!","Empate");
        }
        this->close();
    }
    ui->txt_TiempoRestante->setText(QString::number(tiempo)+":"+QString::number(min));
}
QLabel *MainWindow::label(int _x, int _y, int _z){
    if(_z==0){
        if(_y==0){
            if(_x==0)
                return ui->H_1;
            if(_x==1)
                return ui->H_2;
            if(_x==2)
                return ui->H_3;
            if(_x==3)
                return ui->H_4;
            if(_x==4)
                return ui->H_5;
            if(_x==5)
                return ui->H_6;
            if(_x==6)
                return ui->H_7;
            if(_x==7)
                return ui->H_8;
        }else if(_y==1){
            if(_x==0)
                return ui->G_1;
            if(_x==1)
                return ui->G_2;
            if(_x==2)
                return ui->G_3;
            if(_x==3)
                return ui->G_4;
            if(_x==4)
                return ui->G_5;
            if(_x==5)
                return ui->G_6;
            if(_x==6)
                return ui->G_7;
            if(_x==7)
                return ui->G_8;
        }else if(_y==2){
            if(_x==0)
                return ui->F_1;
            if(_x==1)
                return ui->F_2;
            if(_x==2)
                return ui->F_3;
            if(_x==3)
                return ui->F_4;
            if(_x==4)
                return ui->F_5;
            if(_x==5)
                return ui->F_6;
            if(_x==6)
                return ui->F_7;
            if(_x==7)
                return ui->F_8;
        }else if(_y==3){
            if(_x==0)
                return ui->E_1;
            if(_x==1)
                return ui->E_2;
            if(_x==2)
                return ui->E_3;
            if(_x==3)
                return ui->E_4;
            if(_x==4)
                return ui->E_5;
            if(_x==5)
                return ui->E_6;
            if(_x==6)
                return ui->E_7;
            if(_x==7)
                return ui->E_8;
        }else if(_y==4){
            if(_x==0)
                return ui->D_1;
            if(_x==1)
                return ui->D_2;
            if(_x==2)
                return ui->D_3;
            if(_x==3)
                return ui->D_4;
            if(_x==4)
                return ui->D_5;
            if(_x==5)
                return ui->D_6;
            if(_x==6)
                return ui->D_7;
            if(_x==7)
                return ui->D_8;
        }else if(_y==5){
            if(_x==0)
                return ui->C_1;
            if(_x==1)
                return ui->C_2;
            if(_x==2)
                return ui->C_3;
            if(_x==3)
                return ui->C_4;
            if(_x==4)
                return ui->C_5;
            if(_x==5)
                return ui->C_6;
            if(_x==6)
                return ui->C_7;
            if(_x==7)
                return ui->C_8;
        }else if(_y==6){
            if(_x==0)
                return ui->B_1;
            if(_x==1)
                return ui->B_2;
            if(_x==2)
                return ui->B_3;
            if(_x==3)
                return ui->B_4;
            if(_x==4)
                return ui->B_5;
            if(_x==5)
                return ui->B_6;
            if(_x==6)
                return ui->B_7;
            if(_x==7)
                return ui->B_8;
        }else if(_y==7){
            if(_x==0)
                return ui->A_1;
            if(_x==1)
                return ui->A_2;
            if(_x==2)
                return ui->A_3;
            if(_x==3)
                return ui->A_4;
            if(_x==4)
                return ui->A_5;
            if(_x==5)
                return ui->A_6;
            if(_x==6)
                return ui->A_7;
            if(_x==7)
                return ui->A_8;
        }
    }else if(_z==1){
        if(_y==0){
            if(_x==0)
                return ui->H_1_1;
            if(_x==1)
                return ui->H_2_1;
            if(_x==2)
                return ui->H_3_1;
            if(_x==3)
                return ui->H_4_1;
            if(_x==4)
                return ui->H_5_1;
            if(_x==5)
                return ui->H_6_1;
            if(_x==6)
                return ui->H_7_1;
            if(_x==7)
                return ui->H_8_1;
        }else if(_y==1){
            if(_x==0)
                return ui->G_1_1;
            if(_x==1)
                return ui->G_2_1;
            if(_x==2)
                return ui->G_3_1;
            if(_x==3)
                return ui->G_4_1;
            if(_x==4)
                return ui->G_5_1;
            if(_x==5)
                return ui->G_6_1;
            if(_x==6)
                return ui->G_7_1;
            if(_x==7)
                return ui->G_8_1;
        }else if(_y==2){
            if(_x==0)
                return ui->F_1_1;
            if(_x==1)
                return ui->F_2_1;
            if(_x==2)
                return ui->F_3_1;
            if(_x==3)
                return ui->F_4_1;
            if(_x==4)
                return ui->F_5_1;
            if(_x==5)
                return ui->F_6_1;
            if(_x==6)
                return ui->F_7_1;
            if(_x==7)
                return ui->F_8_1;
        }else if(_y==3){
            if(_x==0)
                return ui->E_1_1;
            if(_x==1)
                return ui->E_2_1;
            if(_x==2)
                return ui->E_3_1;
            if(_x==3)
                return ui->E_4_1;
            if(_x==4)
                return ui->E_5_1;
            if(_x==5)
                return ui->E_6_1;
            if(_x==6)
                return ui->E_7_1;
            if(_x==7)
                return ui->E_8_1;
        }else if(_y==4){
            if(_x==0)
                return ui->D_1_1;
            if(_x==1)
                return ui->D_2_1;
            if(_x==2)
                return ui->D_3_1;
            if(_x==3)
                return ui->D_4_1;
            if(_x==4)
                return ui->D_5_1;
            if(_x==5)
                return ui->D_6_1;
            if(_x==6)
                return ui->D_7_1;
            if(_x==7)
                return ui->D_8_1;
        }else if(_y==5){
            if(_x==0)
                return ui->C_1_1;
            if(_x==1)
                return ui->C_2_1;
            if(_x==2)
                return ui->C_3_1;
            if(_x==3)
                return ui->C_4_1;
            if(_x==4)
                return ui->C_5_1;
            if(_x==5)
                return ui->C_6_1;
            if(_x==6)
                return ui->C_7_1;
            if(_x==7)
                return ui->C_8_1;
        }else if(_y==6){
            if(_x==0)
                return ui->B_1_1;
            if(_x==1)
                return ui->B_2_1;
            if(_x==2)
                return ui->B_3_1;
            if(_x==3)
                return ui->B_4_1;
            if(_x==4)
                return ui->B_5_1;
            if(_x==5)
                return ui->B_6_1;
            if(_x==6)
                return ui->B_7_1;
            if(_x==7)
                return ui->B_8_1;
        }else if(_y==7){
            if(_x==0)
                return ui->A_1_1;
            if(_x==1)
                return ui->A_2_1;
            if(_x==2)
                return ui->A_3_1;
            if(_x==3)
                return ui->A_4_1;
            if(_x==4)
                return ui->A_5_1;
            if(_x==5)
                return ui->A_6_1;
            if(_x==6)
                return ui->A_7_1;
            if(_x==7)
                return ui->A_8_1;
        }
    }else if(_z==2){
        if(_y==0){
            if(_x==0)
                return ui->H_1_2;
            if(_x==1)
                return ui->H_2_2;
            if(_x==2)
                return ui->H_3_2;
            if(_x==3)
                return ui->H_4_2;
            if(_x==4)
                return ui->H_5_2;
            if(_x==5)
                return ui->H_6_2;
            if(_x==6)
                return ui->H_7_2;
            if(_x==7)
                return ui->H_8_2;
        }else if(_y==1){
            if(_x==0)
                return ui->G_1_2;
            if(_x==1)
                return ui->G_2_2;
            if(_x==2)
                return ui->G_3_2;
            if(_x==3)
                return ui->G_4_2;
            if(_x==4)
                return ui->G_5_2;
            if(_x==5)
                return ui->G_6_2;
            if(_x==6)
                return ui->G_7_2;
            if(_x==7)
                return ui->G_8_2;
        }else if(_y==2){
            if(_x==0)
                return ui->F_1_2;
            if(_x==1)
                return ui->F_2_2;
            if(_x==2)
                return ui->F_3_2;
            if(_x==3)
                return ui->F_4_2;
            if(_x==4)
                return ui->F_5_2;
            if(_x==5)
                return ui->F_6_2;
            if(_x==6)
                return ui->F_7_2;
            if(_x==7)
                return ui->F_8_2;
        }else if(_y==3){
            if(_x==0)
                return ui->E_1_2;
            if(_x==1)
                return ui->E_2_2;
            if(_x==2)
                return ui->E_3_2;
            if(_x==3)
                return ui->E_4_2;
            if(_x==4)
                return ui->E_5_2;
            if(_x==5)
                return ui->E_6_2;
            if(_x==6)
                return ui->E_7_2;
            if(_x==7)
                return ui->E_8_2;
        }else if(_y==4){
            if(_x==0)
                return ui->D_1_2;
            if(_x==1)
                return ui->D_2_2;
            if(_x==2)
                return ui->D_3_2;
            if(_x==3)
                return ui->D_4_2;
            if(_x==4)
                return ui->D_5_2;
            if(_x==5)
                return ui->D_6_2;
            if(_x==6)
                return ui->D_7_2;
            if(_x==7)
                return ui->D_8_2;
        }else if(_y==5){
            if(_x==0)
                return ui->C_1_2;
            if(_x==1)
                return ui->C_2_2;
            if(_x==2)
                return ui->C_3_2;
            if(_x==3)
                return ui->C_4_2;
            if(_x==4)
                return ui->C_5_2;
            if(_x==5)
                return ui->C_6_2;
            if(_x==6)
                return ui->C_7_2;
            if(_x==7)
                return ui->C_8_2;
        }else if(_y==6){
            if(_x==0)
                return ui->B_1_2;
            if(_x==1)
                return ui->B_2_2;
            if(_x==2)
                return ui->B_3_2;
            if(_x==3)
                return ui->B_4_2;
            if(_x==4)
                return ui->B_5_2;
            if(_x==5)
                return ui->B_6_2;
            if(_x==6)
                return ui->B_7_2;
            if(_x==7)
                return ui->B_8_2;
        }else if(_y==7){
            if(_x==0)
                return ui->A_1_2;
            if(_x==1)
                return ui->A_2_2;
            if(_x==2)
                return ui->A_3_2;
            if(_x==3)
                return ui->A_4_2;
            if(_x==4)
                return ui->A_5_2;
            if(_x==5)
                return ui->A_6_2;
            if(_x==6)
                return ui->A_7_2;
            if(_x==7)
                return ui->A_8_2;
        }
    }
}

QPixmap MainWindow::Pieza(char _pieza, char color){
    if(_pieza == 'C'){
        if(color == 'N'){
            QPixmap pieza(":/pieza/Piezas/C_N.svg");
            pieza = pieza.scaled(QSize(30, 30), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            return pieza;
        }else{
            QPixmap pieza(":/pieza/Piezas/C_B.svg");
            pieza = pieza.scaled(QSize(30, 30), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            return pieza;
        }
    }else if(_pieza=='P'){
        if(color == 'N'){
            QPixmap pieza(":/pieza/Piezas/P_N.svg");
            pieza = pieza.scaled(QSize(30, 30), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            return pieza;
        }else{
            QPixmap pieza(":/pieza/Piezas/P_B.svg");
            pieza = pieza.scaled(QSize(30, 30), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            return pieza;
        }
    }else if(_pieza=='A'){
        if(color == 'N'){
            QPixmap pieza(":/pieza/Piezas/A_N.svg");
            pieza = pieza.scaled(QSize(30, 30), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            return pieza;
        }else{
            QPixmap pieza(":/pieza/Piezas/A_B.svg");
            pieza = pieza.scaled(QSize(30, 30), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            return pieza;
        }
    }else if(_pieza=='T'){
        if(color == 'N'){
            QPixmap pieza(":/pieza/Piezas/T_N.svg");
            pieza = pieza.scaled(QSize(30, 30), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            return pieza;
        }else{
            QPixmap pieza(":/pieza/Piezas/T_B.svg");
            pieza = pieza.scaled(QSize(30, 30), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            return pieza;
        }
    }else if(_pieza=='D'){
        if(color == 'N'){
            QPixmap pieza(":/pieza/Piezas/D_N.svg");
            pieza = pieza.scaled(QSize(30, 30), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            return pieza;
        }else{
            QPixmap pieza(":/pieza/Piezas/D_B.svg");
            pieza = pieza.scaled(QSize(30, 30), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            return pieza;
        }
    }else if(_pieza=='R'){
        if(color == 'N'){
            QPixmap pieza(":/pieza/Piezas/R_N.svg");
            pieza = pieza.scaled(QSize(30, 30), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            return pieza;
        }else{
            QPixmap pieza(":/pieza/Piezas/R_B.svg");
            pieza = pieza.scaled(QSize(30, 30), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            return pieza;
        }
    }
}

void MainWindow::setPiezas(){
      Nodo * tmp;
      for(int i=0; i<3; i++){
          for(int j=0; j<8; j++){
              for(int k=0; k<8; k++){
                  tmp = matriz->getValueAt(j,k,i);
                  if(tmp && tmp->pieza != ' '){
                      label(k,j,i)->clear();
                      label(k,j,i)->setPixmap(Pieza(tmp->pieza,tmp->color));
                  }else{
                      label(k,j,i)->clear();
                  }
              }
          }
      }
}

void MainWindow::on_txt_Tiempo_textChanged(const QString &arg1)
{

}

void MainWindow::on_cbx_tipoJuego_currentTextChanged(const QString &arg1)
{
    if(arg1=="Normal"){
       ui->txt_Tiempo->hide();
       ui->min->hide();
    }else{
       ui->txt_Tiempo->show();
       ui->min->show();
    }
}

void MainWindow::startTimer(int m){

}

void MainWindow::on_btn_mover_clicked()
{
    if(ui->cbx_tipoJuego->currentText()=="Tiempo"){
        tiempo = ui->txt_Tiempo->text().toInt();
        tiempo--;
        Timer->start(1000);
    }
    if(ui->txt_Movimiento->text().toStdString() != "" && ui->txt_Movimiento->text().toStdString().length() == 6){
        movimiento * tmp = new movimiento(ui->txt_Movimiento->text().toStdString());
        bool reyna = false;
        bool movimientoPermitido = false;
        cout<<turno<<".- "<<"X: "<<tmp->movx<<"Y: "<<tmp->movy;
        char color;
         if(turno % 2 == 0){
           color = 'N';
         }else{
            color = 'B';
         }
         cout<<" color: "<<color<<endl;

         if( (0 <= tmp->movx && tmp->movx <= 7) && (0 <= tmp->movy && tmp->movy <= 7)){
             Nodo * futuro = matriz->getValueAt(tmp->movy, tmp->movx, tmp->nivel);
             if(futuro){
                 if(futuro->pieza=='D'){
                     reyna = true;
                 }
             }
             switch(tmp->pieza){
             case 'P':
                    movimientoPermitido = moverPeonHacia(matriz, futuro, tmp->movy, tmp->movx, tmp->nivel, color, tmp->pieza); //LISTO!!!
                    break;
             case 'C':
                    movimientoPermitido = moverCaballoHacia(matriz, futuro, tmp->movy, tmp->movx, tmp->nivel, color, tmp->pieza);  //LISTO!!!
                 break;
             case 'A':
                    movimientoPermitido = moverAlfilHacia(matriz, futuro, tmp->movy, tmp->movx, tmp->nivel, color, tmp->pieza); //LISTO!!!
                 break;
             case 'T':
                    movimientoPermitido = moverTorreHacia(matriz, futuro, tmp->movy, tmp->movx, tmp->nivel, color, tmp->pieza); //LISTO!!!
                 break;
             case 'R':
                    movimientoPermitido = moverReylHacia(matriz, futuro, tmp->movy, tmp->movx, tmp->nivel, color, tmp->pieza);
                 break;
             case 'D':
                    movimientoPermitido = moverReynalHacia(matriz, futuro, tmp->movy, tmp->movx, tmp->nivel, color, tmp->pieza);
                 break;
             default:
                 break;
             }
             if(movimientoPermitido){
                 if(tmp->pieza == 'P'){
                    if(color == 'N'){
                        if(tmp->movy == 7){
                            int x = columnas[rand() % 8];
                            int y = filas[rand() % 8];
                            int niv;
                            char pie;
                            if(tmp->nivel == 2){
                                niv = 0;
                            }else{
                                niv = tmp->nivel+1;
                            }
                            while(matriz->getValueAt(y,x,niv)&&y!=7){
                                x = columnas[rand() % 8];
                                y = filas[rand() % 8];
                            }
                            if(tmp->nivel == 2){
                                pie = piezas[rand() % 5];
                                matriz->insertar(y,x,niv,pie,color);
                            }else{
                                matriz->insertar(y,x,niv,tmp->pieza,color);
                            }
                        }else{
                            matriz->insertar(tmp->movy, tmp->movx, tmp->nivel,tmp->pieza, color);
                        }
                    }else{
                        if(tmp->movy == 0){
                            int x = columnas[rand() % 8];
                            int y = filas[rand() % 8];
                            int niv;
                            char pie;
                            if(tmp->nivel == 2){
                                niv = 0;
                            }else{
                                niv = tmp->nivel+1;
                            }
                            while(matriz->getValueAt(y,x,niv)&&y!=0){
                                x = columnas[rand() % 8];
                                y = filas[rand() % 8];
                            }
                            if(tmp->nivel == 2){
                                pie = piezas[rand() % 5];
                                matriz->insertar(y,x,niv,pie,color);
                            }else{
                                matriz->insertar(y,x,niv,tmp->pieza,color);
                            }


                        }else{
                            matriz->insertar(tmp->movy, tmp->movx, tmp->nivel,tmp->pieza, color);
                        }
                    }
                 }else{
                     matriz->insertar(tmp->movy, tmp->movx, tmp->nivel,tmp->pieza, color);
                 }

                 setPiezas();
                 ui->txt_Consola->setText(ui->txt_Consola->toHtml() + ui->txt_Turno->text() + ": " + ui->txt_Movimiento->text() + "\n");
                 turno++;
                 if(turno % 2 == 0){
                     ui->txt_Turno->setText(ui->txt_Jugador1->currentText() + " (N)");
                 }else{
                     ui->txt_Turno->setText(ui->txt_Jugador2->currentText() + " (B)");
                 }
             }else{
                 QMessageBox::information(this, "!", "movimiento NO permitido");
             }
         }

    }
}

void MainWindow::on_txt_Jugador1_textChanged(const QString &arg1)
{
    if(turno == 0){
        ui->txt_Turno->setText(ui->txt_Jugador1->currentText() + " (N)");
    }
}

void MainWindow::on_btn_imagen_clicked()
{
    ui->img_grafica->clear();
    if(ui->tipo_Grafica->currentText() == "Arbol"){
        abb_generar_imagen(arbol);
        QPixmap arbol("/home/ferflo/Documentos/Qt/Graficas/ABB.png");
        system("gvfs-open /home/ferflo/Documentos/Qt/Graficas/ABB.png");
        ui->img_grafica->setPixmap(arbol);
    }else if(ui->tipo_Grafica->currentText()=="Estado de Tablero"){

    }else if(ui->tipo_Grafica->currentText()=="Linealizacion"){
        if(matriz->linealidad->head!=NULL){
            delete matriz->linealidad;
            matriz->linealidad = new queue();
        }
        if(ui->tipo_linealizacion->currentText()=="Columnas"){
            matriz->recorrerColumnas(ui->no_tablero->currentIndex());
        }else{
            matriz->recorrerFilas(ui->no_tablero->currentIndex());
        }
        matriz->imagenLinealizacion();
        QPixmap linealizacion("/home/ferflo/Documentos/Qt/Graficas/linealizacion.png");
        linealizacion = linealizacion.scaled(QSize(1140, 1140), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->img_grafica->setPixmap(linealizacion);
        system("gvfs-open /home/ferflo/Documentos/Qt/Graficas/linealizacion.png");
    }else if(ui->tipo_Grafica->currentText()=="Top 10"){
        a = new queue_prioridad();
        generarTop(a,arbol);
        nodo_q_p * cursor = a->head;
        FILE *f = fopen("/home/ferflo/Documentos/Qt/Graficas/Top.dot","w");
        fprintf(f,"digraph G {\n");
        fprintf(f,"\n\tgraph [splines=true overlap=false];\n");
        fprintf(f,"\tedge[color=\"#FF847C\"];\n");
        fprintf(f,"\tgraph [bgcolor=\"#2A363B\"];");
        fprintf(f,"\tnode[style=filled color=\"#99B898\" fillcolor=\"#2A363B\" fontname=\"Montzerat Light\" fontcolor=\"#FECEA8\" shape=rectangle];\n\n");

        while(cursor->next != NULL){
            fprintf(f, "\"%s.%d\"", cursor->usuario, cursor->partidas_ganadas);
            fprintf(f, "%s", " -> ");
            fprintf(f, "\"%s.%d\";\n", cursor->next->usuario, cursor->next->partidas_ganadas);
            cout<<cursor->usuario<<"."<<cursor->partidas_ganadas<<endl;
            cursor = cursor->next;
        }

        fprintf(f,"\n}");
        fclose(f);
        system("dot -Tpng </home/ferflo/Documentos/Qt/Graficas/Top.dot >/home/ferflo/Documentos/Qt/Graficas/Top.png");

        QPixmap TOP("/home/ferflo/Documentos/Qt/Graficas/Top.png");
        TOP = TOP.scaled(QSize(1140, 500), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->img_grafica->setPixmap(TOP);
        system("gvfs-open /home/ferflo/Documentos/Qt/Graficas/Top.png");

    }
}

void MainWindow::on_tipo_Grafica_currentTextChanged(const QString &arg1)
{
    if(ui->tipo_Grafica->currentText() == "Arbol"){
        ui->no_tablero->hide();
        ui->tipo_linealizacion->hide();
    }else if(ui->tipo_Grafica->currentText()=="Estado de Tablero"){
        ui->no_tablero->show();
        ui->tipo_linealizacion->hide();
    }else if(ui->tipo_Grafica->currentText()=="Linealizacion"){
        ui->no_tablero->show();
        ui->tipo_linealizacion->show();
    }else if(ui->tipo_Grafica->currentText()=="Top 10"){
        ui->no_tablero->hide();
        ui->tipo_linealizacion->hide();
    }
}

void MainWindow::on_btn_CargarJugadores_clicked()
{
    string file_name = QFileDialog::getOpenFileName(this,"Seleccionar un Archivo","/home/ferflo").toStdString();
    cout<<file_name<<endl;

    FILE *file;
    file = fopen(file_name.c_str(), "r");
    string tmp;

    string nombre="";
    string pganadas="";
    string pperdidas="";
    int c;

    char* cp;
    if (file) {
        c = getc(file);
        while (c != EOF){
            if(c!='_' && c!=';' && c!='\n'){
                tmp += c;
            }else{
                if(nombre== "" && pganadas == "" && pperdidas == ""){
                    nombre = tmp;
                }else if(pganadas == "" && pperdidas == ""){
                    pganadas = tmp;
                }else if(pperdidas==""){
                    pperdidas  = tmp;
                }else{
                    cp = new char[nombre.length() + 1];
                    strcpy(cp, nombre.c_str());

                    abb_insertar(arbol, cp,atoi(pganadas.c_str()),atoi(pperdidas.c_str()));
                    cout<<"nombre: "<<nombre<<" pganadas: "<<atoi(pganadas.c_str())<<" pperdidas: "<<atoi(pperdidas.c_str())<<endl;

                    nombre="";
                    pganadas="";
                    pperdidas="";
                }
                tmp = "";
            }
            c = getc(file);
        }
        fclose(file);
    }
    Colocar_Jugadores(arbol,ui->txt_Jugador1, ui->txt_Jugador2, ui->txt_Eliminar_Jugador);

    QMessageBox::information(this,"!","Jugadores cargados EXITOSAMENTE");

}

void MainWindow::Colocar_Jugadores(ABB arbol, QComboBox * cbx1, QComboBox * cbx2, QComboBox * cbx3)
{

     if(arbol!=NULL)
     {
          Colocar_Jugadores(arbol->izq, cbx1, cbx2, cbx3);
          Colocar_Jugadores(arbol->der, cbx1, cbx2, cbx3);
          cbx1->addItem(arbol->jugador->usuario);
          cbx2->addItem(arbol->jugador->usuario);
          cbx3->addItem(arbol->jugador->usuario);
     }
}

void MainWindow::generarTop(queue_prioridad * a, ABB arbol){
    if(arbol!=NULL){
        generarTop(a, arbol->izq);
        generarTop(a, arbol->der);
        a->eque(a,arbol->jugador->usuario,arbol->jugador->partidas_ganadas,arbol->jugador->partidas_perdidas);
    }
}

void MainWindow::on_txt_Jugador1_currentTextChanged(const QString &arg1)
{
    if(turno == 0){
        ui->txt_Turno->setText(ui->txt_Jugador1->currentText() + " (N)");
    }
}

void MainWindow::on_btn_Eliminar_Jugador_clicked()
{
    abb_eliminar(arbol,arbol,(char*)ui->txt_Eliminar_Jugador->currentText().toStdString().c_str());
    if(ui->txt_Eliminar_Jugador->currentText()!=""){
    ui->txt_Eliminar_Jugador->clear();
    ui->txt_Jugador1->clear();
    ui->txt_Jugador2->clear();
    Colocar_Jugadores(arbol,ui->txt_Jugador1, ui->txt_Jugador2, ui->txt_Eliminar_Jugador);
    }else{
        QMessageBox::information(this, "!", "arbool de jugadores VACIO");
    }
}

void MainWindow::on_pushButton_clicked()
{
    startTimer(10);
}

void MainWindow::on_btn_insertarJugador_clicked()
{
    abb_insertar(arbol,(char*)ui->txt_insertarJugador->text().toStdString().c_str(),0,0);
    if(ui->txt_Eliminar_Jugador->currentText()!=""){
    ui->txt_Eliminar_Jugador->clear();
    ui->txt_Jugador1->clear();
    ui->txt_Jugador2->clear();
    }
     Colocar_Jugadores(arbol,ui->txt_Jugador1, ui->txt_Jugador2, ui->txt_Eliminar_Jugador);
}
