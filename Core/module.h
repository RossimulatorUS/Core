#ifndef MODULE_H
#define MODULE_H

#include <thread>

class Module
{

protected:

    // Thread d'execution
    std::thread execution_;

    bool est_initialise_;

    // Variables de communication avec le Cortex
    /*const*/ bool* attendre_;
    /*const*/ bool* terminer_;

    // Fonction d'initialisation
    virtual void initialiser();

public:
    Module();
    bool est_initialise() const;
};

#endif // MODULE_H
