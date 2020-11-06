#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QSplitter>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QDialog>
#include "shader_dialog.h"
#include "qtosgwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void addshaders(QString vertexShader,QString fragShader,QString geomShader);
signals:
    void executeShaders(std::string vertexShader,std::string fragmentShader,std::string geomShader);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QtOSGWidget* qosg;
    ShaderDialog* shaders;
};


#endif // MAINWINDOW_H
