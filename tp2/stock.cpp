/*  AUTEUR(S):
    1) Nom + Code permanent du l'Útudiant.e 1
    2) Nom + Code permanent du l'Útudiant.e 2
*/

#include "stock.h"


Stock& Stock::operator+=(const Stock& autre)
{
    // └ complÚter.
    return *this;
}



std::ostream& operator << (std::ostream& os, Stock& stock){

	return os;
}

