#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "funcion.hpp"
#include <QWidget>
#include <QMainWindow>
#include <iostream>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
    private slots:
        void on_enter_clicked();

    private:
        QPointF center;
        QGraphicsScene *scene;
        string function;
        funcion *fn=new funcion();
        void represent(string);
        Ui::MainWindow *ui;
        int i=0;
};
#endif // MAINWINDOW_H
