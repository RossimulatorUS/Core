#ifndef CORTEX_H
#define CORTEX_H

#include <vector>
#include <vehiculethread.h>
#include "distributeur.h"
#include "poissoneur.h"

class Cortex
{

    // Informations du systeme pour optimiser nombre de threads
    // et les autres facteurs

    // COEF -> La quantite de threads physiques que nous pouvons demarrer en fonction du materiel
    enum {NB_THREADS_DE_BASE = 4, COEF_MULT_PHYSIQUE = 3};

    // Temps de calcul alloue a chaque module
    unsigned int pourcentage_temps_calcul_poissoneur_;
    unsigned int pourcentage_temps_calcul_distributeur_;
    std::vector<unsigned int> pourcentage_temps_calcul_deplaceurs_;
    unsigned int pourcentage_temps_calcul_signaleur_;
    unsigned int pourcentage_temps_calcul_OpenGL_;

    // Fonctions d'initialisation
    void load_informations();
    void reserve_ressources();
    unsigned int get_physical_threads();

    // Materiel disponible pour l'execution
    unsigned int physical_threads_;

    // Threads qui commencent a travailler sur leurs donnees a la construction
    std::vector<VehiculeThread> threads_vehicule_;

    Distributeur distributeur_;
    Poissoneur poissoneur_;
    // Signaleur signaleur_;

public:
    Cortex(std::vector<Noeud>);
    void ajouter_thread();

};

#endif // CORTEX_H
