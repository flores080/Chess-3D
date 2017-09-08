#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qlabel.h>
#include <MatrizOrtogonal.h>
#include <logica.h>
#include <iostream>
#include <qtimer.h>
#include <qdatetime.h>
#include <qfiledialog.h>
#include <abb.h>
#include <qcombobox.h>
#include <q_p.h>
#include <qtimer.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int blancas, negras;
    int tiempo = 0;
    int min = 60;
    ABB arbol;
    Matriz * matriz;
    queue_prioridad * a;
    int turno;
    QLabel *label(int _x, int _y, int _z);
    QPixmap Pieza(char _pieza, char _color);

    void setPiezas();
    void startTimer(int m);
    explicit MainWindow(QWidget *parent = 0);
    void Colocar_Jugadores(ABB arbol, QComboBox * cbx1, QComboBox * cbx2, QComboBox * cbx3);
    void generarTop(queue_prioridad * a, ABB arbol);
    char piezas[5] = {'P', 'A', 'T', 'R', 'C'};
    int filas[8] = {0,1,2,3,4,5,6,7};
    int columnas[8] = {0,1,2,3,4,5,6,7};
    ~MainWindow();

public slots:
    void crono();
private slots:
    void on_txt_Tiempo_textChanged(const QString &arg1);

    void on_cbx_tipoJuego_currentTextChanged(const QString &arg1);

    void on_btn_mover_clicked();

    void on_txt_Jugador1_textChanged(const QString &arg1);

    void on_btn_imagen_clicked();

    void on_tipo_Grafica_currentTextChanged(const QString &arg1);

    void on_btn_CargarJugadores_clicked();

    void on_txt_Jugador1_currentTextChanged(const QString &arg1);

    void on_btn_Eliminar_Jugador_clicked();

    void on_pushButton_clicked();

    void on_btn_insertarJugador_clicked();

private:
    Ui::MainWindow *ui;
    QTimer * Timer;
};

#endif // MAINWINDOW_H
