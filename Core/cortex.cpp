#include <string>
#include <thread>
#include "cortex.h"

Cortex::Cortex(std::vector<Noeud> noeuds, std::list<Vehicule*>* vehicules)
    : //attente_analyste_(false),
      attente_distributeur_(false),
      attente_poissoneur_(false),
      fin_simulation(false)
{
    /*
     * Ajouter variable a la construction
     * pour savoir si les temps d'attente
     * et nombre d'iterations sont decides par algortihmes
     * automatiquement, semi-automatiquement ou manuellement
     */

    vehicules_ = vehicules;
    threads_vehicule_ = new std::vector<VehiculeThread*>();

    load_informations();
    reserve_ressources();

    analyste_ = new Analyseur(&fin_simulation, this);
    distributeur_ = new Distributeur(threads_vehicule_, &fin_simulation, &attente_distributeur_);
    poissoneur_ = new Poissoneur(vehicules_, noeuds, distributeur_, &fin_simulation, &attente_poissoneur_);
    signaleur_ = new Signaleur();
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
            ajouter_thread();
    }
    else
    {
        // Demarrer les threads qui seront utilises par le distributeur
        for(unsigned int i = 0; i < NB_THREADS_DE_BASE; ++i)
            ajouter_thread();
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
    VehiculeThread* v = new VehiculeThread();
    threads_vehicule_->emplace_back(v);
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
        //std::cout << physical_threads_ << " " << temps_attente_analyste_ << std::endl;
        //std::cout << "RossimulatorUS >> : " << std::flush;
        //std::cin >> commande;
        //std::cout << commande << "\n" << std::flush;

        // Switch
    }
}

/*unsigned int Cortex::qte_threads_vehicule()
{
    return threads_vehicule_->size();
}*/
