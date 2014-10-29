#ifndef MODULE_H
#define MODULE_H

#include <thread>

class Module
{

protected:

    // Thread d'execution
    std::thread execution_;

    bool is_initialised_;

    // Variables de communication avec le Cortex
    volatile bool* execute_;
    bool terminate_;

    // Fonction d'initialisation
    virtual void init();

public:
    Module();
    bool is_initialized() const;
    void terminate();
};

#endif // MODULE_H
