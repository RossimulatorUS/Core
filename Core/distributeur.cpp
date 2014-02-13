#include "distributeur.h"

Distributeur::Distributeur()
{
}

Distributeur& Distributeur::get()
{
    static Distributeur singleton;
    return singleton;
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
