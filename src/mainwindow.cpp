#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    newPage();
}

MainWindow::~MainWindow()
{
    eraseNet();
    eraseCoordinateNumbers();
    delete fn;
    delete ui;
    delete scene;
    delete model;
    delete eq;
}

void MainWindow::on_enter_clicked(){
    represent(ui->functionEdit->toPlainText().toStdString());
}

void MainWindow::on_zoomIn_clicked(){
    if(zoom*100<250){
        zoom=zoom*1.25;
        ui->grafica->scale(1.25,1.25);
        ui->zoom->setText(QString::number(ceil(zoom*100))+"%");
    }
}

void MainWindow::on_zoomOut_clicked(){
    if(zoom*100>50&&zoom*0.75*100>=50){
        zoom=zoom*0.75;
        ui->grafica->scale(0.75,0.75);
        ui->zoom->setText(QString::number(ceil(zoom*100))+"%");
    }
}

void MainWindow::represent(string input){
    functionList.append(QString::fromStdString(input));
    model->setStringList(functionList);
    double difference=ui->interval->toPlainText().toDouble();
    if (!(input.find(";")!=string::npos)&&input.find("x")!=string::npos){
        fn->prepare(input);
        for(double i=-ui->grafica->width()/2;i<=ui->grafica->width()/2;i+=difference){
            scene->addLine(i,fn->solve(i),i+1,fn->solve(i+1));
        }
    }else if(input.find(";")!=string::npos){
        string eq1,eq2;
        int i=0;
        double *x=0, *y=0;
        bool inEq2=false;
        for(i=0; i<input.length();i++){
            if(input[i]!=';'){
                if(!inEq2) eq1+=input[i];
                if(inEq2) eq2+=input[i];
            }else{
                inEq2=true;
            }
        }
        eq->introduceEquations(eq1,eq2);
        eq->solve(x,y);
        fn->prepare(eq1);
        for(double i=-ui->grafica->width()/2;i<=ui->grafica->width()/2;i+=difference){
            scene->addLine(i,fn->solve(i),i+1,fn->solve(i+1));
        }
        fn->prepare(eq2);
        for(double i=-ui->grafica->width()/2;i<=ui->grafica->width()/2;i+=difference){
            scene->addLine(i,fn->solve(i),i+1,fn->solve(i+1));
        }
        scene->addEllipse(*x-1,*y-1,2,2);
        delete x;
        delete y;
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
    newPage();
}

void MainWindow::newPage(){
    eraseCoordinateNumbers();
    eraseNet();
    scene=new QGraphicsScene(ui->grafica->width()/2,ui->grafica->height()/2,-ui->grafica->width(),-ui->grafica->height());
    QPen axisPen(Qt::blue);
    scene->addLine(QLineF(-ui->grafica->width(),0,ui->grafica->width(),0),axisPen);
    scene->addLine(QLineF(0,-ui->grafica->height(),0,ui->grafica->height()),axisPen);
    scene->setBackgroundBrush(Qt::white);
    ui->grafica->setScene(scene);
    ui->grafica->setTransform(QTransform::fromScale(1, -1));
    functionList.clear();
    represent("0,0");
    model->setStringList(functionList);
    ui->lista->setModel(model);
    if(ui->netCheck->isChecked()){
        paintNet(50);
    }
    if(ui->coordinateCheck->isChecked()){
        paintCoordinateNumbers(50);
    }

}

void MainWindow::paintCoordinateNumbers(int spacing){
    for(int i=0;i<=ui->grafica->width();i+=spacing){
        QGraphicsSimpleTextItem *text = scene->addSimpleText(QString::number(i));
        coordinateNumbers.push_back(text);
        text->setPos(i,-1);
        text->setTransform(QTransform::fromScale(1, -1));
        text = scene->addSimpleText(QString::number(-i));
        coordinateNumbers.push_back(text);
        text->setPos(-i,-1);
        text->setTransform(QTransform::fromScale(1, -1));
    }
    for(int i=spacing;i<=ui->grafica->height();i+=spacing){
        QGraphicsSimpleTextItem *text = scene->addSimpleText(QString::number(i));
        coordinateNumbers.push_back(text);
        text->setPos(-1,i);
        text->setTransform(QTransform::fromScale(1, -1));
        text = scene->addSimpleText(QString::number(-i));
        coordinateNumbers.push_back(text);
        text->setPos(-1,-i);
        text->setTransform(QTransform::fromScale(1, -1));
    }
}

void MainWindow::paintNet(int spacing){
    QPen netPen(Qt::gray);
    for(i=spacing;i<ui->grafica->width();i+=spacing){
        net.push_back(scene->addLine(QLineF(i,-ui->grafica->width()/2,i,ui->grafica->width()/2),netPen));
        net.push_back(scene->addLine(QLineF(-i,-ui->grafica->width()/2,-i,ui->grafica->width()/2),netPen));
    }
    for(i=spacing;i<ui->grafica->height();i+=spacing){
        net.push_back(scene->addLine(QLineF(-ui->grafica->width(),i,ui->grafica->width(),i),netPen));
        net.push_back(scene->addLine(QLineF(-ui->grafica->width(),-i,ui->grafica->width(),-i),netPen));
    }
}

void MainWindow::eraseNet(){
    for(i=0;i<net.length();i++){
        delete net[i];
    }
    net.clear();
}

void MainWindow::eraseCoordinateNumbers(){
    for(i=0;i<coordinateNumbers.length();i++){
        delete coordinateNumbers[i];
    }
    coordinateNumbers.clear();
}

void MainWindow::on_netCheck_toggled(bool checked){
    if(checked){
        paintNet(50);
    }else eraseNet();
}

void MainWindow::on_coordinateCheck_toggled(bool checked){
    if(checked){
        paintCoordinateNumbers(50);
    }else eraseCoordinateNumbers();
}
