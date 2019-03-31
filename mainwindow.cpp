#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(GammaLab *g, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    g(g)
{
    ui->setupUi(this);

    QStringList outputs = g->getOutputs();
    ui->listWidget->addItems(outputs);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    g->setAllOutputsGamma("0.7");
}

void MainWindow::on_pushButton_2_clicked()
{
    g->setAllOutputsGamma("0.8");
}

void MainWindow::on_pushButton_3_clicked()
{
    g->setAllOutputsGamma("0.9");
}

void MainWindow::on_pushButton_4_clicked()
{
    g->setAllOutputsGamma("1");
}
