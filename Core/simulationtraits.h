#ifndef SIMULATIONTRAITS_H
#define SIMULATIONTRAITS_H

struct simulation_traits{
    using node_id_type = unsigned long long;
    using road_id_type = unsigned long long;
    using road_cost_type = double;

    enum law {BERNOUILLI, EXPONENTIAL, UNIFORM};
    enum intersection {GO, STOPSIGN, TLIGHT};
};

int law_to_comboboxindex(simulation_traits::law law);
simulation_traits::law comboboxindex_to_law(int index);
int intersectionbehavior_to_comboboxindex(simulation_traits::intersection behavior);
simulation_traits::intersection comboboxindex_to_intersectionbehavior(int index);

#endif // SIMULATIONTRAITS_H
