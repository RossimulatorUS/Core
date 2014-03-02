#include "analyseur.h"

Analyseur::Analyseur(bool* terminer, bool* attendre)/*
    : terminer_(terminer),
      attendre_(attendre),
      execution_(&Analyseur::initialiser, this)*/
{
    terminer_ = terminer;
    attendre_ = attendre;
    execution_ = std::thread(&Analyseur::initialiser, this);
}

void Analyseur::initialiser()
{

}
