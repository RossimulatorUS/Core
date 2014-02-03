#include <random> // poisson_distribution()
#include <iostream>
#include <chrono>
#include "source.h"

Source::Source() : coefficient_poisson_(5.0) // Valeur arbitraire
{

}

Source::Source(double coefficient) : coefficient_poisson_(coefficient)
{

}

int Source::generer_trafic()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);

    std::poisson_distribution<int> distribution (5.2);

    for (int i=0; i<10; ++i)
    std::cout << distribution(generator) << " ";

    return 0;
}
