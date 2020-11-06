#include "shader_dialog.h"
#include "ui_shader_dialog.h"
#include <QMenuBar>
#include <QFileDialog>
#include <fstream>

ShaderDialog::ShaderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShaderDialog)
{
    ui->setupUi(this);
    connect(ui->execute,SIGNAL(clicked(bool)),this,SLOT(getShaders()));
    connect(ui->vertexOpenFile,SIGNAL(clicked(bool)),this,SLOT(readVertexShader()));
    connect(ui->geomOpenFile,SIGNAL(clicked(bool)),this,SLOT(readGeomShader()));
    connect(ui->fragmentOpenFile,SIGNAL(clicked(bool)),this,SLOT(readFragmentShader()));
    connect(ui->vertexSaveFile,SIGNAL(clicked(bool)),this,SLOT(saveVertexShader()));
    connect(ui->geomSaveFile,SIGNAL(clicked(bool)),this,SLOT(saveGeomShader()));
    connect(ui->fragmentSaveFile,SIGNAL(clicked(bool)),this,SLOT(saveFragmentShader()));
//    QMenuBar *m = new QMenuBar(this);
//    QMenu *m1 = new QMenu("&shader");
//    m1->addMenu("vertex shader");
//    m->addMenu(m1);
}

ShaderDialog::~ShaderDialog()
{
    delete ui;
}

void ShaderDialog::getShaders()
{
    vertexShader = ui->VertexShaderText->toPlainText();
    fragShader = ui->FragmentShaderText->toPlainText();
    geomShader = ui->GeomShaderText->toPlainText();
    emit(executeShaders(vertexShader,fragShader,geomShader));
}

QString ShaderDialog::openFileDialog()
{
    QFileDialog fileDialog(this);

    fileDialog.setFileMode(QFileDialog::AnyFile);
    fileDialog.setViewMode(QFileDialog::Detail);

    QStringList fileNames;
    if (fileDialog.exec() == QFileDialog::Accepted)
        fileNames = fileDialog.selectedFiles();
    else
        return "";

    if(fileNames.isEmpty())
    {
        return "";
    }
     QString filePath = fileNames.first();

     std::fstream f(filePath.toStdString(), std::fstream::in );
     std::string s;
     getline( f, s, '\0');
     f.close();

     return QString(s.c_str());
}


void ShaderDialog::saveFileDialog(QString data)
{
    QFileDialog fileDialog(this);

    fileDialog.setFileMode(QFileDialog::AnyFile);
    fileDialog.setViewMode(QFileDialog::Detail);
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);

    QStringList fileNames;
    if (fileDialog.exec() == QFileDialog::Accepted)
        fileNames = fileDialog.selectedFiles();
    else
        return;

    if(fileNames.isEmpty())
    {
       return;
    }
     QString filePath = fileNames.first();

     std::ofstream f;
     f.open(filePath.toStdString());
     f << data.toStdString();
     f.close();
}

void ShaderDialog::readVertexShader()
{
   ui->VertexShaderText->setPlainText(openFileDialog());
}
void ShaderDialog::readGeomShader()
{
    ui->GeomShaderText->setPlainText(openFileDialog());
}
void ShaderDialog::readFragmentShader()
{
    ui->FragmentShaderText->setPlainText(openFileDialog());
}

void ShaderDialog::saveVertexShader()
{
    saveFileDialog(ui->VertexShaderText->toPlainText());
}

void ShaderDialog::saveGeomShader()
{
    saveFileDialog(ui->GeomShaderText->toPlainText());
}

void ShaderDialog::saveFragmentShader()
{
    saveFileDialog(ui->FragmentShaderText->toPlainText());
}
