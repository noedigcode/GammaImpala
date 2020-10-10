#include "gammalab.h"

GammaLab::GammaLab(QObject *parent) : QObject(parent)
{

}

QStringList GammaLab::getOutputs()
{
    outputs.clear();

    QProcess p;
    p.start("xrandr --listmonitors");
    p.waitForFinished();

    QString out(p.readAll());
    QStringList lines = out.split("\n");
    for (int i=0; i < lines.count(); i++) {
        QString line = lines[i].trimmed();
        if (!line.count()) { continue; }
        if (line.at(0).isDigit()) {
            QStringList words = line.split(" ");
            outputs.append( words.last().trimmed() );
        }
    }

    return outputs;
}

float GammaLab::getBrightness(QString outputName)
{
    float brightness = 1.0;

    QProcess p;
    p.start("xrandr --verbose");
    p.waitForFinished();

    QString out(p.readAll());
    QStringList lines = out.split("\n");
    int state = 0;
    foreach (QString line, lines) {
        QStringList words = line.simplified().split(" ");
        if (state == 0) {
            // Look for output name
            if (words.value(1) == "connected") {
                // Found output line.
                if (words.value(0) == outputName) {
                    // Found desired output
                    state = 1;
                }
            }
        } else if (state == 1) {
            // Look for brightness line
            if (words.value(0) == "Brightness:") {
                // Found brightness line
                brightness = words.value(1).toFloat();
                break;
            }
        }
    }

    return brightness;
}

void GammaLab::setAllOutputsBrightness(float brightness)
{
    QString bstr = QString::number(brightness, 'f', 1);
    foreach (QString output, outputs) {
        QProcess p;
        p.start(QString("xrandr --output %1 --brightness %2").arg(output, bstr));
        p.waitForFinished();
    }
}

void GammaLab::setAllOutputsGamma(QString g)
{
    for (int i=0; i < outputs.count(); i++) {
        QProcess p;
        p.start(QString("xrandr --output %1 --gamma %2:%2:%2").arg(outputs[i], g));
        p.waitForFinished();
    }
}
