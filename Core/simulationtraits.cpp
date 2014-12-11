#include "simulationtraits.h"

int law_to_comboboxindex(simulation_traits::law law)
{
    switch(law)
    {
        case simulation_traits::UNIFORM : return 0; break;
        case simulation_traits::BERNOUILLI : return 1; break;
        case simulation_traits::EXPONENTIAL : return 2; break;
    }
}

simulation_traits::law comboboxindex_to_law(int index)
{
    switch(index)
    {
        case 0 : return simulation_traits::UNIFORM; break;
        case 1 : return simulation_traits::BERNOUILLI; break;
        case 2 : return simulation_traits::EXPONENTIAL; break;
    }
}

int intersectionbehavior_to_comboboxindex(simulation_traits::intersection behavior)
{
    switch(behavior)
    {
        case simulation_traits::GO : return 0; break;
        case simulation_traits::STOPSIGN : return 1; break;
        case simulation_traits::TLIGHT : return 2; break;
    }
}

simulation_traits::intersection comboboxindex_to_intersectionbehavior(int index)
{
    switch(index)
    {
        case 0 : return simulation_traits::GO; break;
        case 1 : return simulation_traits::STOPSIGN; break;
        case 2 : return simulation_traits::TLIGHT; break;
    }
}
