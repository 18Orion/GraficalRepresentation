#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "funcion.hpp"
#include <QWidget>
#include <QMainWindow>
#include <iostream>
#include <QGraphicsView>
#include <QListView>
#include <QStringListModel>
#include <QString>
#include <vector>
#include <QTextItem>

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
        //void on_lista_clicked();
    private:
        //vector<vector<QGraphicsLineItem>> itemsList;
        QStringListModel *model = new QStringListModel();
        QList<QString> functionList;
        QGraphicsScene *scene;
        funcion *fn=new funcion();
        void represent(string);
        Ui::MainWindow *ui;
        int i=0;
};
#endif // MAINWINDOW_H
