#include <iostream>
#include <thread>
#include "cortex.h"

Cortex::Cortex(std::vector<Noeud> noeuds)
    : threads_vehicule_(4), distributeur_(&threads_vehicule_), poissoneur_(noeuds, &distributeur_)
{
    load_informations();
    reserve_ressources();

    std::cout << "Quantite de noeuds : " << noeuds.size() << std::endl;
}

void Cortex::load_informations()
{
   physical_threads = get_physical_threads();
}

void Cortex::reserve_ressources()
{
    if(physical_threads)
    {
        // Demarrer un nombre intelligent de threads en fonction de la qte. disponible.
    }
    else
    {
        // Demarrer les threads qui seront utilises par le distributeur
        for(unsigned int i = 0; i < NB_THREADS_DE_BASE; ++i)
            threads_vehicule_.push_back(VehiculeThread());
    }
}

void Cortex::deplacement(size_t numero_thread)
{
    // Travailler sur threads_vehicules[numero_thread]
}

unsigned int Cortex::get_physical_threads()
{
    // Implementer pour tous les OS
    return std::thread::hardware_concurrency();
}

void Cortex::ajouter_thread()
{
    threads_vehicule_.push_back(VehiculeThread());
}
