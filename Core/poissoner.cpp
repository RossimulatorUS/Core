#include <QDebug>

#include <algorithm>

#include "poissoner.h"

Poissoner::Poissoner(std::list<Vehicle *> *all_vehicles, std::vector<Node> nodes, Distributor* distributor, bool* terminate, volatile bool* execute)
    : distributor_(distributor),
      all_vehicles_(all_vehicles)
{
    // Estime de la quantite de sources sur le reseau
    nodes_.reserve(nodes.size() / 2);

    // On garde seulement les noeuds qui sont des sources dans le poissoneur
    for(auto i(std::begin(nodes)); i != std::end(nodes); ++i)
        if(i->is_source())
            nodes_.emplace_back(*i);

    terminate_ = terminate;
    execute_ = execute;
    execution_ = std::thread(&Poissoner::init, this);
}

void Poissoner::init()
{
    // Attendre que le distributeur soit initialise
    while(!distributor_->is_initialized())
        std::this_thread::yield();

    // Indication que le poissonneur est pret
    is_initialised_ = true;
    //Historique_dexecution::temps temps_initial;

    // Tant que la simulation n'est pas terminee
    while(!(*terminate_))
    {
        // Attendre prochain tic
        if(*execute_)
        {
            *execute_ = false;

            // Demarrer chronometre
            //temps_initial = Historique_dexecution::get_time();

            std::for_each(nodes_.begin(), nodes_.end(), [&](Node& node){

                // Si le noeud est pret a poissoner, ajouter un vehicule sur le reseau
                if(node.is_due())
                {
                    Vehicle* v = node.create_vehicle();
                    all_vehicles_->push_back(v);
                    distributor_->add_vehicle(v);
                }
            });


            // Arreter chronometre
            //historique_.ajouter_temps(Historique_dexecution::get_time() - temps_initial);
        }

        std::chrono::milliseconds timespan(1); // Max 20% de la plage perdu
        std::this_thread::sleep_for(timespan);
    }
}
