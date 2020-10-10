#include "gammalab.h"
#include "mainwindow.h"

#include <QApplication>

#include <iostream>

QStringList helpArgs({"-h", "--help", "h", "help",});
QStringList brightnessArgs({"-b", "--brightness", "b", "brightness"});
QStringList gammaArgs({"-g", "--gamma", "g", "gamma"});
QStringList downArgs({"-d", "--down", "d", "down"});
QStringList upArgs({"-u", "--up", "u", "up"});

void print(QString msg)
{
    std::cout << msg.toStdString() << "\n";
}

QString argListToString(QStringList args)
{
    QString s;
    foreach (QString a, args) {
        if (!s.isEmpty()) {
            s += ", ";
        }
        s += a;
    }
    return s;
}

void printHelp()
{
    print("GammaImpala");
    print("G van der Kolf 2019-2020");
    print("");
    print("Usage: gammaimpala [gamma]");
    print("       gammaimpala --gamma [gamma]");
    print("       gammaimpala --brightness [ [--down | --up] [brightness] ]");
    print("");
    print("Argument options:");
    print("    " + argListToString(helpArgs));
    print("    Prints the help message");
    print("");
    print("    " + argListToString(brightnessArgs));
    print("    Sets brightness if value specified, otherwise prints current setting.");
    print("    Relative setting can be made with up/down.");
    print("");
    print("    " + argListToString(gammaArgs));
    print("    Sets gamma to the specified value.");
    print("");
    print("    " + argListToString(upArgs));
    print("    Use to specify a relative brightness setting.");
    print("");
    print("    " + argListToString(downArgs));
    print("    Use to specify a relative brightness setting.");
    print("");
    print("If no arguments are provided the GUI is shown.");
    print("");
    print("Examples:");
    print("    Set gamma: gammaimpala 0.8");
    print("    Set gamma: gammaimpala gamma 0.8");
    print("    Print brightness: gammaimpala brightness");
    print("    Set brightness: gammaimpala brightness 0.9");
    print("    Set brightness relative up, using default relative value: gammaimpala b u");
    print("    Set brightness relative down by 0.1: gammaimpala b d 0.1");
    print("");
}

void printBrightness(GammaLab* g)
{
    QStringList outs = g->getOutputs();
    print("Brightness:");
    foreach (QString out, outs) {
        print(QString("    %1: %2").arg(out).arg(g->getBrightness(out)));
    }
}

int setBrightness(GammaLab* g, QString arg)
{
    bool ok = false;
    float f = arg.toFloat(&ok);
    if (ok) {
        print("Setting brightness of all outputs to " + arg);
        g->getOutputs();
        g->setAllOutputsBrightness(f);
        return 0;
    } else {
        print("Invalid argument for brightness: " + arg);
        return 1;
    }
}

int setBrightnessRelative(GammaLab* g, QString arg)
{
    bool ok = false;
    float rel = arg.toFloat(&ok);
    if (!ok) {
        print("Invalid argument for relative brightness: " + arg);
        return 1;
    }

    QStringList outs = g->getOutputs();
    if (outs.isEmpty()) {
        print("No outputs detected.");
        return 1;
    }

    float f = g->getBrightness(outs.first());
    setBrightness(g, QString::number(f + rel, 'f', 1));
}

int setGamma(GammaLab* g, QString arg)
{
    // Test if arg is float
    bool ok = false;
    arg.toFloat(&ok);
    if (ok) {
        print("Setting gamma of all outputs to " + arg);
        g->getOutputs();
        g->setAllOutputsGamma(arg);
        return 0;
    } else {
        print("Invalid argument for gamma: " + arg);
        return 1;
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GammaLab g;

    QStringList args = a.arguments();

    QString arg = args.value(1);
    if (!arg.isEmpty()) {
        if (helpArgs.contains(arg)) {
            // Print help
            printHelp();
            return 0;
        } else if (brightnessArgs.contains(arg)) {
            arg = args.value(2);
            if (arg.isEmpty()) {
                // Print brightness
                printBrightness(&g);
                return 0;
            } else if (upArgs.contains(arg)) {
                // Brightness up
                arg = args.value(3);
                if (arg.isEmpty()) {
                    // Brightness up by default value
                    return setBrightnessRelative(&g, "0.1");
                } else {
                    // Brightness up by specified value
                    return setBrightnessRelative(&g, arg);
                }
            } else if (downArgs.contains(arg)) {
                // Brightness down
                arg = args.value(3);
                if (arg.isEmpty()) {
                    // Brightness down by default value
                    return setBrightnessRelative(&g, "-0.1");
                } else {
                    // Brightness down by specified value
                    arg = "-" + arg;
                    return setBrightnessRelative(&g, arg);
                }
            } else {
                // Set brightness
                return setBrightness(&g, arg);
            }
        } else if (gammaArgs.contains(arg)) {
            arg = args.value(2);
            // Set gamma
            return setGamma(&g, arg);
        } else {
            // Use value as gamma
            return setGamma(&g, arg);
        }
    }

    // No arguments were specified / handled, start GUI.

    MainWindow w(&g);
    w.show();

    return a.exec();
}
