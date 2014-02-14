#include "distributeur.h"

Distributeur::Distributeur(std::vector<VehiculeThread> *)
{

}

Distributeur::numero_thread Distributeur::ajouter_vehicule(Vehicule*)
{
    ++nombre_vehicules;
    return 0;
}

Distributeur::numero_thread Distributeur::ajouter_thread(VehiculeThread*)
{
    return 0;
}
