#ifndef CARTE_H
#define CARTE_H

class Carte // Singleton
{
    private:
        Carte();
        Carte(Carte const&); // Ne pas implementer
        void operator=(Carte const&); // Ne pas implementer

    public:
        static Carte& get_carte();
};

#endif // CARTE_H
