#include <assert.h>
#include "module.h"

Module::Module()
    : est_initialise_(false)
{
}


bool Module::est_initialise() const
{
    return est_initialise_;
}

void Module::initialiser()
{
    bool ce_module_n_a_pas_de_fonction_d_initialisation(false);
    assert(ce_module_n_a_pas_de_fonction_d_initialisation);
}
