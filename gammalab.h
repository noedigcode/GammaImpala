#ifndef GAMMALAB_H
#define GAMMALAB_H

#include <QObject>
#include <QProcess>

class GammaLab : public QObject
{
    Q_OBJECT
public:
    explicit GammaLab(QObject *parent = nullptr);

    QStringList getOutputs();
    void setAllOutputsGamma(QString g);

private:
    QStringList outputs;
};

#endif // GAMMALAB_H
