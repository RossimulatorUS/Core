#include <algorithm>
#include <chrono>
#include "historique_dexecution.h"

Historique_dexecution::Historique_dexecution()
    : taille_buffer_(10)
{
    // Moyenne sera sur taille_buffer_ donnees
    derniers_temps_execution_ = boost::circular_buffer<temps>(taille_buffer_);
}

Historique_dexecution::temps Historique_dexecution::moyenne() const
{
    return moyenne_;
}

Historique_dexecution::temps Historique_dexecution::get_time()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
}

void Historique_dexecution::calculer_moyenne_mobile()
{
    temps moyenne_tmp;
    std::for_each(derniers_temps_execution_.begin(), derniers_temps_execution_.end(), [&](temps tmp){moyenne_tmp += tmp;});
    moyenne_ =  moyenne_tmp / derniers_temps_execution_.size();
}

Historique_dexecution::temps Historique_dexecution::get_dernier_temps() const
{
    return derniers_temps_execution_.back();
}

void Historique_dexecution::ajouter_temps(temps nouveau)
{
    derniers_temps_execution_.push_back(nouveau);
}
