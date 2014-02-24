#ifndef SIGNALEUR_H
#define SIGNALEUR_H

#include <thread>

class Signaleur
{
    // Thread du Signaleur
    std::thread execution_;

    // Fonction d'initialisation
    void signaler();

public:
    Signaleur();
};

#endif // SIGNALEUR_H
