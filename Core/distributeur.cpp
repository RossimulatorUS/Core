#include <iostream>
#include "distributeur.h"

Distributeur::Distributeur(std::vector<VehiculeThread>* threads, bool* terminer, bool* attendre)
    : threads_(threads),
      terminer_(terminer),
      attendre_(attendre),
      execution_(&Distributeur::initialiser, this)
{}

void Distributeur::initialiser()
{
    while(!terminer)
   {
        if(!vehicules_.size())
            std::cout << "RossimulatorUS >> : " << std::flush; // Une seconde -> devrait etre en fonction du temps de calcul

    // Trouver un thread libre

    // Distribuer

    }
}

void Distributeur::ajouter_vehicule(Vehicule vehicule)
{
    vehicules_.push_back(vehicule);
}

