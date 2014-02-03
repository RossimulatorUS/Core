#include "distributeur.h"

Distributeur::Distributeur ()
    : nb_threads_(10), threads_(10), tst(0)
{}

Distributeur& Distributeur::get_distributeur()
{
    static Distributeur instance;
    return instance;
}

/* ajouter_vehicule
 * Il n'y aura pas de problemes de
 * synchronisation, le distributeur est
 * le seul qui peut ajouter des taches aux threads
 * ou a la route
 */

int Distributeur::ajouter_vechicule(Vehicule vehicule)
{
    // Trouver le thread le moisns charge

    // Ajouter le vehicule dans le thread

    // Ajouter le vehicule a la route

    // retourner le # du thread qui detient le vehicule
    return 0;
}
