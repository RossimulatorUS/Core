#include <QDebug>
#include <string>
#include <thread>
#include "cortex.h"

Cortex::Cortex(std::vector<Noeud> noeuds, std::list<Vehicule*>* vehicules)
    : execution_distributeur_(false),
      execution_poissoneur_(false),
      execution_deplaceurs_(std::list<volatile bool>()),
      execution_signaleur_(false),
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
    distributeur_ = new Distributeur(threads_vehicule_, &fin_simulation, &execution_distributeur_);
    poissoneur_ = new Poissoneur(vehicules_, noeuds, distributeur_, &fin_simulation, &execution_poissoneur_);
    signaleur_ = new Signaleur(&fin_simulation, &execution_signaleur_);
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
        for(unsigned int i = 0; i < 1 * COEF_MULT_PHYSIQUE; ++i)
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
    execution_deplaceurs_.emplace_back(false);
    VehiculeThread* v = new VehiculeThread(&fin_simulation, &execution_deplaceurs_.back());
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
