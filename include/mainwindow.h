#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include "funcion.hpp"
//#include "EquationSystem.hpp"
#include "qfunctionline.h"
#include <QWidget>
#include <QMainWindow>
#include <iostream>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QListView>
#include <QStringListModel>
#include <QString>
#include <vector>
#include <QTextItem>
#include <QModelIndex>
#include <QListWidgetItem>

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
        void on_zoomIn_clicked();
        void on_zoomOut_clicked();
        void on_NewPage_clicked();
        void on_coordinateCheck_toggled(bool checked);
        void on_netCheck_toggled(bool checked);
    private:
        void represent(string);
        void newPage();
        void paintCoordinateNumbers(int spacing);
        void paintNet(int spacing);
        void eraseNet();
        void eraseCoordinateNumbers();
        void calculateSep();
        double zoom=1;
        QStringListModel *model = new QStringListModel();
        QList<QString> functionList;
        QList<QGraphicsSimpleTextItem*> coordinateNumbers;
        QList<QGraphicsLineItem*> net;
        QGraphicsScene *scene;
        funcion *fn=new funcion();
        Ui::MainWindow *ui;
        int i=0, separation=50;
};
#endif // MAINWINDOW_H
