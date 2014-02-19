#include <iostream>
#include <thread>
#include "cortex.h"

Cortex::Cortex(std::vector<Noeud> noeuds)
    : distributeur_(&threads_vehicule_), poissoneur_(noeuds, &distributeur_)
{
    load_informations();
    reserve_ressources();

    std::cout << "Construction du cortex " << std::endl;
    std::cout << "Quantite de noeuds : " << noeuds.size() << std::endl;
}

void Cortex::load_informations()
{
   physical_threads_ = get_physical_threads();
}

void Cortex::reserve_ressources()
{
    if(physical_threads_)
    {
        // Demarrer un nombre intelligent de threads en fonction de la qte. disponible.
        for(unsigned int i = 0; i < physical_threads_ * COEF_MULT_PHYSIQUE; ++i)
            threads_vehicule_.push_back(VehiculeThread(threads_vehicule_.size()));
    }
    else
    {
        // Demarrer les threads qui seront utilises par le distributeur
        for(unsigned int i = 0; i < NB_THREADS_DE_BASE; ++i)
            threads_vehicule_.push_back(VehiculeThread(threads_vehicule_.size()));
    }
}

unsigned int Cortex::get_physical_threads()
{
    // Implementer pour tous les OS
    return std::thread::hardware_concurrency();
}

void Cortex::ajouter_thread()
{
    threads_vehicule_.push_back(VehiculeThread(threads_vehicule_.size()));
}
