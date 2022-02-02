#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPen pen(Qt::red);
    scene=new QGraphicsScene(ui->grafica->width()/2,ui->grafica->height()/2,-ui->grafica->width(),-ui->grafica->height());
    scene->addLine(QLineF(-ui->grafica->width()/2,0,ui->grafica->width()/2,0),pen);
    scene->addLine(QLineF(0,-ui->grafica->height()/2,0,ui->grafica->height()/2),pen);
    scene->setBackgroundBrush(Qt::white);
    ui->grafica->setScene(scene);
    represent("0,0");
    model->setStringList(functionList);
    ui->lista->setModel(model);
    ui->grafica->scale(1,-1);
    /*
    for(i=-ui->grafica->width()/20;i<ui->grafica->width()/20;i++){

    }
    for(i=-ui->grafica->height()/20;i<ui->grafica->height()/20;i++){
        QGraphicsTextItem *text=scene->addText(QString::number(i));
        text->setPos(0,i*10);
    }
    delete text;*/
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
        scene->addEllipse(stod(x)-5,stod(y)-5, 10,10);
    }
}
