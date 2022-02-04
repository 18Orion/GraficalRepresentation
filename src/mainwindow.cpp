#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nuevaPagina();

}

MainWindow::~MainWindow()
{
    delete fn;
    delete ui;
    delete scene;
    delete model;
}

void MainWindow::on_enter_clicked(){
    represent(ui->functionEdit->toPlainText().toStdString());
}

void MainWindow::on_zoomIn_clicked(){
    zoom++;
    ui->grafica->scale(1.25,1.25);
}

void MainWindow::on_zoomOut_clicked(){
    if(zoom>1){
        zoom--;
        ui->grafica->scale(0.75,0.75);
    }
}

void MainWindow::represent(string input){
    functionList.append(QString::fromStdString(input));
    model->setStringList(functionList);
    double difference=ui->interval->toPlainText().toDouble();
    if (input.find("x")!=string::npos){
        fn->prepare(input);
        for(double i=-ui->grafica->width()/2;i<=ui->grafica->width()/2;i+=difference){
            scene->addLine(i,fn->solve(i),i+1,fn->solve(i+1));

        }

    }else if(input.find("y")!=string::npos){
        input.replace(0,input.length(),'y','x');
        fn->prepare(input);
        for(double i=-ui->grafica->width()/2;i<=ui->grafica->width()/2;i+=difference){
            scene->addLine(fn->solve(i),i,fn->solve(i+1),i+1);
        }

    }else if(input.find(",")!=string::npos){
        string x,y,a;
        bool xGot=false;
        for(i=0; i<input.length(); i++){
            if((isdigit(input[i])||input[i]=='.')&&!xGot) x+=input[i];
            if((isdigit(input[i])||input[i]=='.')&&xGot) y+=input[i];
            if(input[i]==',') xGot=true;
        }
        scene->addEllipse(stod(x)-1,stod(y)-1,2,2);
    }
}

void MainWindow::on_NewPage_clicked(){
    nuevaPagina();
}

void MainWindow::nuevaPagina(){
    scene=new QGraphicsScene(ui->grafica->width()/2,ui->grafica->height()/2,-ui->grafica->width(),-ui->grafica->height());
    paintNet(50);
    scene->setBackgroundBrush(Qt::white);
    ui->grafica->setScene(scene);
    //ui->grafica->scale(1,-1);
    ui->grafica->setTransform(QTransform::fromScale(1, -1));
    represent("0,0");
    functionList.clear();
    model->setStringList(functionList);
    ui->lista->setModel(model);
    paintCoordinateNumbers();
}

void MainWindow::paintCoordinateNumbers(){
    for(int i=0;i<=ui->grafica->width()/2;i+=50){
        QGraphicsSimpleTextItem *text = scene->addSimpleText(QString::number(i));
        text->setPos(i,-1);
        text->setTransform(QTransform::fromScale(1, -1));
        text = scene->addSimpleText(QString::number(-i));
        text->setPos(-i,-1);
        text->setTransform(QTransform::fromScale(1, -1));
    }
    for(int i=50;i<=ui->grafica->height()/2;i+=50){
        QGraphicsSimpleTextItem *text = scene->addSimpleText(QString::number(i));
        text->setPos(-1,i);
        text->setTransform(QTransform::fromScale(1, -1));
        text = scene->addSimpleText(QString::number(-i));
        text->setPos(-1,-i);
        text->setTransform(QTransform::fromScale(1, -1));
    }
}

void MainWindow::paintNet(int spacing){
    QPen netPen(Qt::gray);
    QPen axisPen(Qt::blue);
    scene->addLine(QLineF(-ui->grafica->width()/2,0,ui->grafica->width()/2,0),axisPen);
    scene->addLine(QLineF(0,-ui->grafica->height()/2,0,ui->grafica->height()/2),axisPen);
    for(i=spacing;i<ui->grafica->width()/2;i+=spacing){
        scene->addLine(QLineF(i,-ui->grafica->width()/2,i,ui->grafica->width()/2),netPen);
        scene->addLine(QLineF(-i,-ui->grafica->width()/2,-i,ui->grafica->width()/2),netPen);
    }
    for(i=spacing;i<ui->grafica->height()/2;i+=spacing){
        scene->addLine(QLineF(-ui->grafica->width()/2,i,ui->grafica->width()/2,i),netPen);
        scene->addLine(QLineF(-ui->grafica->width()/2,-i,ui->grafica->width()/2,-i),netPen);
    }
}
