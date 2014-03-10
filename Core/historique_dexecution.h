#ifndef GTE_H
#define GTE_H

#include <chrono>
#include "boost/circular_buffer.hpp"

// Gestionnaire de Temps d'Execution
class Historique_dexecution
{
public:
    typedef std::chrono::nanoseconds temps;

private:
    // Moyenne mobile -- boost::circular_buffer
    boost::circular_buffer<temps> derniers_temps_execution_;
    boost::circular_buffer<temps>::size_type taille_buffer_;
    temps moyenne_;

public:
    Historique_dexecution();

    void ajouter_temps(temps);
    void calculer_moyenne_mobile();
    temps get_dernier_temps() const;
    temps moyenne() const;

    static temps get_time();
};

#endif // GTE_H
