#include <random> // poisson_distribution()
#include "source.h"

Source::Source() : coefficient_poisson_(5.0) // Valeur arbitraire
{

}

Source::Source(double coefficient) : coefficient_poisson_(coefficient)
{

}

int Source::generer_trafic()
{
    return 0;
}
