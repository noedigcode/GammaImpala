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

void GammaLab::setAllOutputsGamma(QString g)
{
    for (int i=0; i < outputs.count(); i++) {
        QProcess p;
        p.start(QString("xrandr --output %1 --gamma %2:%2:%2").arg(outputs[i], g));
        p.waitForFinished();
    }
}
