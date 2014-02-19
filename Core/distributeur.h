#ifndef DISTRIBUTEUR_H
#define DISTRIBUTEUR_H

#include <thread>
#include <vector>
#include <vehiculethread.h>
#include <vehicule.h>

// Singleton
// TODO : Heritage d'une classe incopiable

class Distributeur
{
    // Vehicules en attente d'etre distribues
    std::vector<Vehicule> vehicules_;

    // Threads du cortex qui sont utilisables pour calcul des deplacements
    std::vector<VehiculeThread>* threads_;

    // Thread du Distributeur
    std::thread execution_;

    // Fonction d'initialisation
    void distribuer();

    bool terminer;

public:
    Distributeur(std::vector<VehiculeThread>*);
    void ajouter_vehicule(Vehicule);

    void termine();
};

#endif // DISTRIBUTEUR_H
