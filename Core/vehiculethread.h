#ifndef VEHICULETHREAD_H
#define VEHICULETHREAD_H

#include <thread>
#include <vector>
#include "vehicule.h"

class VehiculeThread // : public Module
{
    // Materiel
    std::vector<Vehicule*> vehicules_;
    std::thread execution_;
    bool terminer;
    static unsigned int id_a_date_;
    unsigned int id_;

    // Fonction d'initialisation
    void demarrer_traitement(VehiculeThread *vt);

public:
     VehiculeThread();
     void ajouter_vehicule(Vehicule*);
     void termine();
};

#endif // VEHICULETHREAD_H
