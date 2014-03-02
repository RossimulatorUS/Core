#ifndef CORTEX_H
#define CORTEX_H

#include <vector>

#include "analyseur.h"
#include "distributeur.h"
#include "poissoneur.h"
#include "signaleur.h"
#include "vehiculethread.h"

class Cortex
{

public:
    // COEF -> La quantite de threads physiques que nous pouvons demarrer en fonction du materiel
    enum {NB_THREADS_DE_BASE = 2, COEF_MULT_PHYSIQUE = 3};
    enum mode_execution {MANUEL = 0, SEMI = 1, AUTO = 2};

private:
    // Temps de « sleep » entre chaque serie d'iteration
    unsigned int temps_attente_analyste_;
    unsigned int temps_attente_poissoneur_;
    unsigned int temps_attente_distributeur_;
    unsigned int temps_attente_deplaceurs_;
    unsigned int temps_attente_signaleur_;
    unsigned int temps_attente_OpenGL_;

    // Nombre d'iteration entre chaque « sleep »
    unsigned int nombre_iterations_analyste_;
    unsigned int nombre_iterations_poissoneur_;
    unsigned int nombre_iterations_distributeur_;
    unsigned int nombre_iterations_deplaceurs_;
    unsigned int nombre_iterations_signaleur_;
    unsigned int nombre_iterations_OpenGL_;

    // Mettre un module en attente
    bool attente_analyste_;
    bool attente_distributeur_;
    bool attente_poissoneur_;
    bool attente_deplaceurs_;
    bool attente_signaleur_;
    bool attente_OpenGL_;

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
    std::vector<Vehicule*>* vehicules_;

    // Fin de la simulation
    bool fin_simulation;

public:
    Cortex(std::vector<Noeud>, std::vector<Vehicule*>*);

    // API -> Commandes interpretees
    void interpreter();

};

#endif // CORTEX_H
