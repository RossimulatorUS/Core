#ifndef CORTEX_H
#define CORTEX_H

#include <atomic>
#include <thread>
#include <vector>
#include <list>

#include "analyseur.h"
#include "distributeur.h"
#include "poissoneur.h"
#include "signaleur.h"
#include "vehiculethread.h"

class Analyseur;

class Cortex
{
friend class Analyseur;

public:
    // COEF -> La quantite de threads physiques que nous pouvons demarrer en fonction du materiel
    enum {NB_THREADS_DE_BASE = 2, COEF_MULT_PHYSIQUE = 1};
    enum mode_execution {MANUEL = 0, SEMI = 1, AUTO = 2};

private:

    // Mettre un module en attente
    volatile bool execution_distributeur_;
    volatile bool execution_poissoneur_;
    std::list<volatile bool> execution_deplaceurs_;
    volatile bool execution_signaleur_;

    // Fonctions d'initialisation
    void load_informations();
    void reserve_ressources();
    unsigned int get_physical_threads();

    // Materiel disponible pour l'execution
    unsigned int physical_threads_;

    // Commandes
    void ajouter_thread();
    void terminer();

    // Threads qui commencent a travailler sur leurs donnees a la construction
    std::vector<VehiculeThread*>* threads_vehicule_;

    // Modules
    Analyseur* analyste_;
    Distributeur* distributeur_;
    Poissoneur* poissoneur_;
    Signaleur* signaleur_;

    // Vehicules se deplacant dans le reseau routier
    std::list<Vehicule*>* vehicules_;

    // Delais simulation
    bool fin_simulation;

public:
    Cortex(std::vector<Noeud>, std::list<Vehicule *> *);

    // API -> Commandes interpretees
    void interpreter();
    void executer();
    //unsigned int qte_threads_vehicule();

};

#endif // CORTEX_H
