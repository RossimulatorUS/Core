#include <iostream>
#include "distributeur.h"

Distributeur::Distributeur(std::vector<VehiculeThread>* threads)
    : threads_(threads), execution_(&Distributeur::distribuer, this), terminer(true)
{
    std::cout << "Construction du distributeur" << std::endl;
}

void Distributeur::ajouter_vehicule(Vehicule vehicule)
{
    vehicules_.push_back(vehicule);
}

void Distributeur::distribuer()
{
    if(!vehicules_.size())
        sleep(1); // Une seconde -> devrait etre en fonction du temps de calcul

    // Trouver un thread libre

    // Distribuer
}

void Distributeur::termine()
{
    terminer = true;
}
