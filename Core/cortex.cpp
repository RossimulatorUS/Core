#include "cortex.h"

#include "simulationdata.h"

Cortex::Cortex()
    : distributor_execution_(false),
      mover_execution_(std::list<volatile bool>()),
      signaler_execution_(false),
      simulation_fps_(60),
      paused_(false)
{
    vehicles_ = SimulationData::getInstance().getVehiclesPointer();
    vehicle_threads_ = new std::vector<VehicleThread*>();

    load_information();
    reserve_ressources();

    analyst_ = new Analyser(this);
    distributor_ = new Distributor(vehicle_threads_,
                                   &distributor_execution_,
                                   SimulationData::getInstance().getNodes(),
                                   vehicles_);
    signaler_ = new Signaler(&signaler_execution_);
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
    return std::thread::hardware_concurrency();
}

void Cortex::add_thread()
{
    mover_execution_.emplace_back(false);
    VehicleThread* v = new VehicleThread(&mover_execution_.back());
    vehicle_threads_->emplace_back(v);
}

void Cortex::terminate()
{
    // terminer threads
    analyst_->terminate();
    distributor_->terminate();
    signaler_->terminate();

    for(auto vt = vehicle_threads_->begin(); vt != vehicle_threads_->end(); ++vt)
    {
        (*vt)->terminate();
    }

    delete vehicle_threads_;
}

unsigned int Cortex::simulation_fps() const
{
    return simulation_fps_;
}

void Cortex::pause()
{
    paused_ = true;
}

void Cortex::unpause()
{
    paused_ = false;
}

