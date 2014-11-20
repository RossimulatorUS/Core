#ifndef SIMULATIONTRAITS_H
#define SIMULATIONTRAITS_H

struct simulation_traits{
    using node_id_type = unsigned long long;
    using road_id_type = unsigned long long;
    using road_cost_type = double;

    enum law {BERNOUILLI, EXPONENTIAL, UNIFORM};
    enum intersection {GO, STOPSIGN, TLIGHT};
};

#endif // SIMULATIONTRAITS_H
