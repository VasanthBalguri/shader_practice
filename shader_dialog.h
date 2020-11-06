#ifndef SHADER_DIALOG_H
#define SHADER_DIALOG_H
#include "shader_dialog.h"
#include <QDialog>

namespace Ui {
class ShaderDialog;
}

class ShaderDialog : public QDialog
{
    Q_OBJECT
public slots:
    void getShaders();
    void readVertexShader();
    void readGeomShader();
    void readFragmentShader();
    void saveVertexShader();
    void saveGeomShader();
    void saveFragmentShader();
signals:
    void executeShaders(QString vertexShader,QString fragShader,QString geomShader);
public:
    explicit ShaderDialog(QWidget *parent = 0);
    ~ShaderDialog();
    QString openFileDialog();
    void saveFileDialog(QString data);

private:
    Ui::ShaderDialog *ui;
    QString vertexShader;
    QString fragShader;
    QString geomShader;
};

#endif // SHADER_DIALOG_H
