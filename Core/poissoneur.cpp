#include <QDebug>
#include "poissoneur.h"

Poissoneur::Poissoneur(std::vector<Vehicule*>* all_vehicules, std::vector<Noeud> noeuds, Distributeur* distributeur, bool* terminer, bool* attendre)
    : distributeur_(distributeur),
      all_vehicules_(all_vehicules)
{
    // Estime de la quantite de sources sur le reseau
    noeuds_.reserve(noeuds.size() / 2);

    // On garde seulement les noeuds qui sont des sources dans le poissoneur
    for(auto i(std::begin(noeuds)); i != std::end(noeuds); ++i)
        if(i->est_source())
            noeuds_.emplace_back(*i);

    terminer_ = terminer;
    attendre_ = attendre;
    execution_ = std::thread(&Poissoneur::initialiser, this);
}

void Poissoneur::initialiser()
{
    // Attendre que le distributeur soit initialise
    while(!distributeur_->est_initialise())
        std::this_thread::yield();

    std::vector<Noeud>::iterator iterateur(std::begin(noeuds_));

    // Variable qui devront etre supprimees
    Route* route = new Route(&*iterateur, &*(iterateur+1));
    int i = 0;

    // Indication que le poissonneur est pret
    est_initialise_ = true;
    Historique_dexecution::temps temps_initial;

    // Pour chaque noeud source
    while(!(*attendre_))
    {
        // Demarrer chronometre
        temps_initial = Historique_dexecution::get_time();

        // Si le noeud est pret a poissoner, ajouter un vehicule sur le reseau
        if(iterateur->est_du() && i < 10)
        {
            Vehicule* vec = new Vehicule(&noeuds_[0], &noeuds_[1], route);
            all_vehicules_->emplace_back(vec);
            distributeur_->ajouter_vehicule(vec);
            ++i;
            //sleep(1);
            std::chrono::milliseconds dura( 1000 );
            std::this_thread::sleep_for(dura);
        }

        // Pour looper dans les noeuds
        if(iterateur == end(noeuds_))
            iterateur = begin(noeuds_);

        // Arreter chronometre
        historique_.ajouter_temps(Historique_dexecution::get_time() - temps_initial);

        qDebug() << "Temps parcours : " << historique_.get_dernier_temps().count();
    }

    /*
     * On va avoir besoin d'un pointeur sur le vecteur de noeuds original pour choisir
     * aleatoirement un noeud puit
     */
}
