#include <QDebug>
#include <string>
#include <thread>
#include "cortex.h"

Cortex::Cortex(std::vector<Node> nodes, std::list<Vehicle*>* vehicles)
    : distributor_execution_(false),
      mover_execution_(std::list<volatile bool>()),
      signaler_execution_(false),
      opengl_fps_(60),
      end_simulation(false)
{
    /*
     * Ajouter variable a la construction
     * pour savoir si les temps d'attente
     * et nombre d'iterations sont decides par algortihmes
     * automatiquement, semi-automatiquement ou manuellement
     */

    vehicles_ = vehicles;
    vehicle_threads_ = new std::vector<VehicleThread*>();

    load_information();
    reserve_ressources();

    analyst_ = new Analyser(&end_simulation, this);
    distributor_ = new Distributor(vehicle_threads_, &end_simulation, &distributor_execution_, nodes, vehicles_);
    signaler_ = new Signaler(&end_simulation, &signaler_execution_);
}

void Cortex::load_information()
{
   physical_threads_ = get_physical_threads();
}

void Cortex::reserve_ressources()
{
    if(physical_threads_)
    {
        // Demarrer un nombre intelligent de threads en fonction de la qte. disponible.
        for(unsigned int i = 0; i < 1 * PHYSICAL_MULT_COEF; ++i)
            add_thread();
    }
    else
    {
        // Demarrer les threads qui seront utilises par le distributeur
        for(unsigned int i = 0; i < BASE_NB_OF_THREADS; ++i)
            add_thread();
    }
}

unsigned int Cortex::get_physical_threads()
{
    // Implementer pour tous les OS
    return std::thread::hardware_concurrency();
}

// Commande de l'interpreteur
void Cortex::add_thread()
{
    mover_execution_.emplace_back(false);
    VehicleThread* v = new VehicleThread(&end_simulation, &mover_execution_.back());
    vehicle_threads_->emplace_back(v);
}

// Commande de l'interpreteur
void Cortex::terminate()
{
    // Sauvegarder statistiques

    // Sauvegarder etat simulation?

    // termienr threads
    end_simulation = true;

}
unsigned int Cortex::opengl_fps() const
{
    return opengl_fps_;
}
