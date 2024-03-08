/*  AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/

#include "stock.h"


Stock& Stock::operator+=(const Stock& autre)
{
    // À compléter.
    return *this;
}



std::ostream& operator << (std::ostream& os, Stock& stock){

	return os;
}

