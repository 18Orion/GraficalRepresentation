#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "funcion.hpp"
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
    private:
        void represent(string);
        void nuevaPagina();
        void paintCoordinateNumbers();
        void paintNet(int spacing);
        int zoom=1;
        QStringListModel *model = new QStringListModel();
        QList<QString> functionList;
        QGraphicsScene *scene;
        funcion *fn=new funcion();

        Ui::MainWindow *ui;
        int i=0;
};
#endif // MAINWINDOW_H
