#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gammalab.h"

#define n2s(x) QString::number(x)

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(GammaLab* g, QWidget *parent = 0);
    ~MainWindow();

    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_pushButton_0_7_clicked();
    void on_pushButton_0_8_clicked();
    void on_pushButton_0_9_clicked();
    void on_pushButton_1_0_clicked();

private:
    Ui::MainWindow *ui;
    GammaLab* g;
};

#endif // MAINWINDOW_H
