#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qosg = new QtOSGWidget(1,1,this->centralWidget());
    shaders = new ShaderDialog;
    ui->setupUi(this);


    QGridLayout *g = new QGridLayout;
    g->addWidget(qosg);


    ui->centralWidget->setLayout(g);
    connect(ui->actionEdit_Shader,SIGNAL(triggered(bool)),shaders,SLOT(show()));
    connect(shaders,SIGNAL(executeShaders(QString,QString,QString)),this,SLOT(addshaders(QString,QString,QString)));
    connect(this,SIGNAL(executeShaders(std::string,std::string,std::string)),qosg,SLOT(executeShader(std::string,std::string,std::string)));
    qosg->setScene(createScene());
}

void MainWindow::addshaders(QString vertexShader,QString fragShader,QString geomShader)
{
   std::string strVertexShader = vertexShader.toStdString();
   std::string strFragShader = fragShader.toStdString();
   std::string strGeomShader = geomShader.toStdString();
   emit(executeShaders(strVertexShader,strFragShader,strGeomShader));
}

MainWindow::~MainWindow()
{
    delete ui;
}
