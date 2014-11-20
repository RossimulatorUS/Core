#ifndef CORTEX_H
#define CORTEX_H

#include <vector>
#include <list>

#include "analyser.h"
#include "distributor.h"
#include "signaler.h"
#include "vehiclethread.h"

#include "simulationtraits.h"

class Analyser;

class Cortex
{
friend class Analyser;

    using node_id_type = typename simulation_traits::node_id_type;

public:
    // COEF -> La quantite de threads physiques que nous pouvons demarrer en fonction du materiel
    enum {BASE_NB_OF_THREADS = 2, PHYSICAL_MULT_COEF = 1};
    enum execution_mode {MANUAL = 0, SEMI = 1, AUTO = 2};

private:

    // Mettre un module en attente
    volatile bool distributor_execution_;
    std::list<volatile bool> mover_execution_;
    volatile bool signaler_execution_;

    // Fonctions d'initialisation
    void load_information();
    void reserve_ressources();
    unsigned int get_physical_threads();

    // Materiel disponible pour l'execution
    unsigned int physical_threads_;

    // Commandes
    void add_thread();

    // Threads qui commencent a travailler sur leurs donnees a la construction
    std::vector<VehicleThread*>* vehicle_threads_;

    // Modules
    Analyser* analyst_;
    Distributor* distributor_;
    Signaler* signaler_;

    // Vehicules se deplacant dans le reseau routier
    std::list<Vehicle*>* vehicles_;

    // Status
    unsigned int simulation_fps_;
    bool paused_;

public:
    Cortex();

    unsigned int simulation_fps() const;
    void terminate();

    void pause();
    void unpause();
};

#endif // CORTEX_H
