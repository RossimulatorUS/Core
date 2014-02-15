#include "distributeur.h"

Distributeur::Distributeur(std::vector<VehiculeThread>* threads)
    : threads_(threads), terminer(true)
{

}

void Distributeur::ajouter_vehicule(Vehicule vehicule)
{
    vehicules_.push_back(vehicule);
}

void Distributeur::distribuer()
{
    terminer = false;
    // min(foreach vehiculethread.size())
}

void Distributeur::termine()
{
    terminer = true;
}
