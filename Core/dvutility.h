#ifndef DVUTILITY_H
#define DVUTILITY_H

#include <map>

#define DV_INFINITY 999999;
class Noeud;    //forward declaration




class DVMessage
{
public:
    using cost_type = float;
private:
    Noeud* origin_;
    std::map<Noeud*, Noeud*> paths_;
    std::map<Noeud*, cost_type> costs_;
public:
    DVMessage(Noeud *origin, std::map<Noeud*, Noeud*> paths, std::map<Noeud*, cost_type> costs);

    //getters
    std::map<Noeud *, Noeud *> paths() const;
    std::map<Noeud *, cost_type> costs() const;
    Noeud* origin() const;
};

#endif // DVUTILITY_H
