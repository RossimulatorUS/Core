#include <iostream>
#include <string>
#include <thread>
#include "cortex.h"

Cortex::Cortex(std::vector<Noeud> noeuds)
    : analyste_(&fin_simulation, &attente_analyste_),
      distributeur_(&threads_vehicule_, &fin_simulation, &attente_distributeur_),
      poissoneur_(noeuds, &distributeur_, &fin_simulation, &attente_poissoneur_),
      fin_simulation(false)
{

    /*
     * Ajouter variable a la construction
     * pour savoir si les temps d'attente
     * et nombre d'iterations sont decides par algortihmes
     * automatiquement, semi-automatiquement ou manuellement
     */

    load_informations();
    reserve_ressources();
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

// Commande de l'interpreteur
void Cortex::ajouter_thread()
{
    threads_vehicule_.push_back(VehiculeThread(threads_vehicule_.size()));
}

// Commande de l'interpreteur
void Cortex::terminer()
{
    // Sauvegarder statistiques

    // Sauvegarder etat simulation?

    // termienr threads
    fin_simulation = true;

}

// API -> communique avec cortex, distributeur, poissoneur, signaleur
void Cortex::interpreter()
{
    std::string commande;
    while(commande != "exit")
    {
        std::cout << "RossimulatorUS >> : " << std::flush;
        std::cin >> commande;
        std::cout << commande << "\n" << std::flush;

        // Switch
    }
}
