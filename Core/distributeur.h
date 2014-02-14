#ifndef DISTRIBUTEUR_H
#define DISTRIBUTEUR_H

#include <vector>
#include <vehiculethread.h>
#include <vehicule.h>

// Singleton
// TODO : Heritage d'une classe incopiable

class Distributeur
{
    //std::vector<VehiculeThread*> threads_;
    typedef unsigned int numero_thread;
    unsigned int nombre_vehicules;

public:
    Distributeur(std::vector<VehiculeThread>*);
    numero_thread ajouter_vehicule(Vehicule*);
    numero_thread ajouter_thread(VehiculeThread*);
};

#endif // DISTRIBUTEUR_H
