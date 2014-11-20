#include "simulationstatus.h"

SimulationStatus::SimulationStatus() :
    status(Ready)
{

}

void SimulationStatus::run()
{
    status = Running;
}

void SimulationStatus::pause()
{
    status = Paused;
}

void SimulationStatus::stop()
{
    status = Ready;
}
