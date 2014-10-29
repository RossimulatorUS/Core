#include "simulationdata.h"
#include "vehiclethread.h"

unsigned int VehicleThread::id_to_date_ = 0;

VehicleThread::VehicleThread(volatile bool* execute)
    : execution_(&VehicleThread::init, this)
{
    vehicles_ = std::list<Vehicle*>();
    toDelete = std::list<Vehicle*>();

    execute_ = execute;

    id_ = id_to_date_;
    ++id_to_date_;
}

void VehicleThread::init()
{
    while(!terminate_)
    {
        if(*execute_)
        {
            *execute_ = false;

            for (auto itt = vehicles_.begin(); itt != vehicles_.end(); ++itt)
            {
                //remove the vehicule from the simluation data
                Vehicle* v = *itt;
                if (v->process() == false)
                {
                    SimulationData::getInstance().removeVehicle(v);
                    toDelete.push_back(v);
                }
            }

            for (auto itt = toDelete.begin(); itt != toDelete.end(); ++itt)
            {
                //remove the vehicule from the vehicule thread
                Vehicle *v = *itt;
                vehicles_.remove(v);
            }
        }

        std::chrono::milliseconds timespan(1);
        std::this_thread::sleep_for(timespan);
    }
}

void VehicleThread::add_vehicle(Vehicle* vehicle)
{
    vehicles_.push_back(vehicle);
}

std::list<Vehicle*>::size_type VehicleThread::nb_vehicles() const
{
    return vehicles_.size();
}

void VehicleThread::terminate()
{
    terminate_ = true;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    clear_data();
}

void VehicleThread::clear_data()
{
    vehicles_.clear();
    toDelete.clear();
}
