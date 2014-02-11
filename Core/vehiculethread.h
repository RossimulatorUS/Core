#ifndef VEHICULETHREAD_H
#define VEHICULETHREAD_H

#include <QThread>
#include "vehicule.h"

class VehiculeThread : public QThread
{
    Q_OBJECT
private:
    void run();


public:
    Vehicule *vehicule;

    VehiculeThread(QObject *parent = 0);
};

#endif // VEHICULETHREAD_H
