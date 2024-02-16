#include "Menuprincipal.h"
#include "ui_Menuprincipal.h"
#include "genero.h"
#include "ctunnes.h"
#include <QDoubleValidator>
#include <QMessageBox>
#include <QTimeEdit>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->horizontalSlider, &QSlider::valueChanged, this, &MainWindow::update_label);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_pressed()
{
    ui->Filtro->setCurrentIndex(1);
}


void MainWindow::on_pushButton_pressed()
{
    ui->Filtro->setCurrentIndex(0);
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->Filtro->setCurrentIndex(1);
}

void MainWindow::on_pushButton_3_pressed()
{
    ui->Filtro->setCurrentIndex(2);
}


void MainWindow::on_pushButton_7_pressed()
{
    ui->Filtro->setCurrentIndex(0);
}


void MainWindow::on_pushButton_4_pressed()
{
    ui->Filtro->setCurrentIndex(3);
}

void MainWindow::on_pushButton_8_pressed()
{
    ui->Filtro->setCurrentIndex(0);
}

void MainWindow::on_pushButton_5_pressed()
{
     ui->Filtro->setCurrentIndex(4);
}

void MainWindow::on_pushButton_9_pressed()
{
    ui->Filtro->setCurrentIndex(0);
}

void MainWindow::on_pushButton_6_pressed()
{
     ui->Filtro->setCurrentIndex(5);
}

void MainWindow::on_pushButton_10_pressed()
{
     ui->Filtro->setCurrentIndex(0);
}

void MainWindow::on_pushButton_15_pressed()
{
    close();
}


void MainWindow::on_pushButton_11_pressed()
{
    double precio;
    QString qname = ui->nombre->text().simplified();
    string name = qname.toStdString();
    QString qcant=ui->cantante->text().simplified();
    string cantante = qcant.toStdString();
    QString qgenero = ui->genero->currentText().simplified();
    string genero = qgenero.toStdString();
    QString qprecio = ui->precio->text().simplified();
    precio = qprecio.toDouble();
    Genero::Generos gen;

    if(!qname.isEmpty() && !qcant.isEmpty() && !qgenero.isEmpty() && !qprecio.isEmpty()){
        if(genero=="Dance"){gen=Genero::DANCE;}
        if(genero=="Electronica"){gen = Genero::ELECTRONICA;}
        if(genero=="Pop"){gen = Genero::POP;}
        if(genero=="Ranchera"){gen = Genero::RANCHERA;}
        if(genero=="Rap"){gen = Genero::RAP;}
        if(genero=="Reggae"){gen = Genero::REGGAE;}
        if(genero=="Rock"){gen = Genero::ROCK;}
        QTime tiempo = ui->timeEdit->time();
        QString timeString = tiempo.toString("mm:ss");
        string duracion =timeString.toStdString();
        ctunes object;
        object.addSong(name,cantante,gen,precio,duracion);

    }else{
        QMessageBox::warning(this, "Error", "Llene todos los campos.");
    }
}
    void MainWindow::update_label(int value)
    {
        ui->update_label->setText(QString("Rate: %1").arg(value));
    }

    void MainWindow::on_pushButton_14_pressed()
    {
        ctunes object;
        QString cadena = QString::fromStdString(object.infoSong(ui->codigo_info->text().toInt()));
        ui->texto_info->setText(cadena);
    }

void MainWindow::on_pushButton_12_pressed()
{
    ctunes object;
    int code = ui->codigo_review->text().toInt();
    int estrellas = ui->horizontalSlider->value();
    if (!object.verificar_codigo(code)) {
        QMessageBox::warning(this, "Error", "El código no existe.");
        return;
    }

    object.reviewSong(code, estrellas);

}


void MainWindow::on_pushButton_13_pressed()
{
 ctunes object;
    int code = ui->code_downloads->text().toInt();
    QString nombre = ui->cliente_downloads->text().simplified();
    string cliente = nombre.toStdString();
    object.downloadSong(code,cliente);
    ui->textBrowser->setText(QString::fromStdString(object.downloadSong(code,cliente)));

}


