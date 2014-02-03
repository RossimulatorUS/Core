#ifndef DISTRIBUTEUR_H
#define DISTRIBUTEUR_H

#include "vehicule.h"
#include <iostream>
#include <vector>
#include <thread>

class Distributeur // Singleton
{    
    private:
        Distributeur();
        Distributeur(Distributeur const&); // Ne pas implementer
        void operator=(Distributeur const&); // Ne pas implementer

        int nb_threads_;
        std::vector<std::thread> threads_;

    public:
        static Distributeur& get_distributeur();
        int ajouter_vechicule(Vehicule);

        // Inutile
        void increment(){++tst;}
        void afficher(){std::cout << tst << std::endl;}
        int tst;
};

#endif // DISTRIBUTEUR_H
