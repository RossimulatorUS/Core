#ifndef VEHICULETHREAD_H
#define VEHICULETHREAD_H

#include <thread>
#include <vector>
#include "vehicule.h"

class VehiculeThread
{
     std::vector<Vehicule> vehicules_;
     void traitement();
     bool terminer;

     std::thread execution_;

public:

     VehiculeThread();
     void ajouter_vehicule(Vehicule);

     void termine();

};

#endif // VEHICULETHREAD_H
