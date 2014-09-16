#ifndef VEHICULETHREAD_H
#define VEHICULETHREAD_H

#include <thread>
#include <vector>

#include "module.h"
#include "vehicule.h"

class VehiculeThread : public Module
{
    // Materiel
    std::list<Vehicule*> vehicules_;
    std::list<Vehicule*> toDelete;
    std::thread execution_;
    bool terminer;
    static unsigned int id_a_date_;
    unsigned int id_;

    // Fonction d'initialisation
    void demarrer_traitement(VehiculeThread *vt);

public:
     VehiculeThread(bool *terminer, volatile bool *executer);
     void ajouter_vehicule(Vehicule*);
     std::list<Vehicule*>::size_type nb_vehicules() const;
     void termine();
};

#endif // VEHICULETHREAD_H
