#ifndef DISTRIBUTEUR_H
#define DISTRIBUTEUR_H

#include <vector>
#include <vehiculethread.h>
#include <vehicule.h>

// Singleton
// TODO : Heritage d'une classe incopiable

class Distributeur
{
    // Vehicules en attente d'etre distribues
    std::vector<Vehicule> vehicules_;

    // Threads du cortex qui sont utilisables
    std::vector<VehiculeThread>* threads_;

    bool terminer;

public:
    Distributeur(std::vector<VehiculeThread>*);
    void ajouter_vehicule(Vehicule);

    void distribuer();
    void termine();
};

#endif // DISTRIBUTEUR_H
