#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QKeyEvent>

MainWindow::MainWindow(GammaLab *g, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    g(g)
{
    ui->setupUi(this);

    QStringList outputs = g->getOutputs();
    ui->listWidget->addItems(outputs);

    qApp->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    bool ret = false;

     if (event->type() == QEvent::KeyPress) {
         QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
         if (keyEvent->key() == Qt::Key_Escape) {
             this->close();
             ret = true;
         } else if (keyEvent->key() == Qt::Key_7) {
             on_pushButton_0_7_clicked();
             ret = true;
         } else if (keyEvent->key() == Qt::Key_8) {
             on_pushButton_0_8_clicked();
             ret = true;
         } else if (keyEvent->key() == Qt::Key_9) {
             on_pushButton_0_9_clicked();
             ret = true;
         } else if (keyEvent->key() == Qt::Key_0) {
             on_pushButton_1_0_clicked();
             ret = true;
         } else if (keyEvent->key() == Qt::Key_1) {
             on_pushButton_1_0_clicked();
             ret = true;
         }
     }

    if (!ret) {
        ret = QMainWindow::eventFilter(watched, event);
    }

    return ret;
}

void MainWindow::on_pushButton_0_7_clicked()
{
    g->setAllOutputsGamma("0.7");
}

void MainWindow::on_pushButton_0_8_clicked()
{
    g->setAllOutputsGamma("0.8");
}

void MainWindow::on_pushButton_0_9_clicked()
{
    g->setAllOutputsGamma("0.9");
}

void MainWindow::on_pushButton_1_0_clicked()
{
    g->setAllOutputsGamma("1");
}
