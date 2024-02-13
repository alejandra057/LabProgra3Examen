#include "Menuprincipal.h"
#include "ui_Menuprincipal.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
