#include "signaleur.h"

Signaleur::Signaleur()
    : execution_(&Signaleur::signaler, this)
{

}

void Signaleur::signaler()
{

}
