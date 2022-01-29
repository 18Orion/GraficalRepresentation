#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    scene=new QGraphicsScene(0,0,300,300);
    scene->setBackgroundBrush(Qt::white);
    scene->addLine(QLineF(-500,0,500,0));
    scene->addLine(QLineF(0,-500,0,500));
    ui->grafica->setScene(scene);
    ui->grafica->centerOn(0,0);
}

MainWindow::~MainWindow()
{
    delete fn;
    delete ui;
    delete scene;
}

void MainWindow::on_enter_clicked(){
    represent(ui->functionEdit->toPlainText().toStdString());
}


void MainWindow::represent(string input){
    if (input.find("x")!=string::npos){
        fn->prepare(input);
        for(i=-ui->grafica->width()/2;i<=ui->grafica->width()/2;i+=1){
            scene->addLine(i,fn->solve(i),i+1,fn->solve(i+1));
        }
    }else{
//
    }
}


