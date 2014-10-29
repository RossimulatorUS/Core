#include <assert.h>
#include "module.h"

Module::Module() :
    is_initialised_(false),
    terminate_(false)
{}

bool Module::is_initialized() const
{
    return is_initialised_;
}

void Module::init()
{
    bool ce_module_n_a_pas_de_fonction_d_initialisation(false);
    assert(ce_module_n_a_pas_de_fonction_d_initialisation);
}

void Module::terminate()
{
    terminate_ = true;
    execution_.join();
}
