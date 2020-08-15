#include "gammalab.h"
#include "mainwindow.h"

#include <QApplication>

#include <iostream>

void print(QString msg)
{
    std::cout << msg.toStdString() << "\n";
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GammaLab g;

    QStringList args = a.arguments();
    for (int i=1; i < args.count(); i++) {
        QString arg = args[i];
        bool ok = false;
        arg.toFloat(&ok);
        if (ok) {
            print("Setting gamma of all outputs to " + arg);
            g.getOutputs();
            g.setAllOutputsGamma(arg);
            return 0;
        } else {
            if ( (arg == "-h") || (arg == "--help") || (arg == "help") ) {
                print("GammaImpala");
                print("G van der Kolf 2019-2020");
                print("");
                print("Usage: GammaImpala [gamma]");
                print("   gamma: float value of gamma, e.g. 0.8");
                print("If no arguments are provided the GUI is shown.");
                print("");
                return 0;
            } else {
                print("Invalid argument '" + arg + "', use help for more info.");
                return 1;
            }
        }
    }

    MainWindow w(&g);
    w.show();

    return a.exec();
}
