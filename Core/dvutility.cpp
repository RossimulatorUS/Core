#include "dvutility.h"

DVMessage::DVMessage(Noeud* origin, std::map<Noeud *, Noeud *> paths, std::map<Noeud *, DVMessage::cost_type> costs)
    :origin_(origin), paths_(paths), costs_(costs)
{

}

std::map<Noeud *, Noeud *> DVMessage::paths() const
{
    return paths_;
}


std::map<Noeud *, typename DVMessage::cost_type> DVMessage::costs() const
{
    return costs_;
}


Noeud* DVMessage::origin() const
{
    return origin_;
}
