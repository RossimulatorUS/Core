#include "analyseur.h"

Analyseur::Analyseur(bool* terminer, bool* attendre)
    : terminer_(terminer),
      attendre_(attendre),
      execution_(&Analyseur::initialiser, this)
{
}

void Analyseur::initialiser()
{

}
