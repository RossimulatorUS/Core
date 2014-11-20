#ifndef SIMULATIONSTATUS_H
#define SIMULATIONSTATUS_H

#include <QtWidgets>

#include "cortex.h"

class SimulationStatus
{
    // Object controlled -- Possibly have a vector
    Cortex* cortex;

    // Simulation possible statuses
    enum Status {
        Running,
        Paused,
        Ready
    };

    // Actual status
    Status status;

public:

    // Initialisation
    SimulationStatus();

    // Actions
    void run();
    void pause();
    void stop();
};


#endif // SIMULATIONSTATUS_H
