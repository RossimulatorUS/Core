#ifndef VEHICULETHREAD_H
#define VEHICULETHREAD_H

#include <thread>
#include <vector>
#include "vehicule.h"

class VehiculeThread
{
    // Materiel
    std::vector<Vehicule> vehicules_;
    std::thread execution_;
    bool terminer;
    unsigned int id_;

    // Fonction d'initialisation
    void demarrer_traitement();

public:

     VehiculeThread(unsigned int);
     void ajouter_vehicule(Vehicule);
     void termine();
};

#endif // VEHICULETHREAD_H
