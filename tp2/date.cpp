/*  AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/
#include "date.h"
#include <cstdio>
#include <iomanip>
#include <assert.h>
#include <ctime>

//Date sans argument: initialise une date avec les données de la date actuelle
Date::Date(){
	time_t now = time(0);
	tm* dt = localtime(&now);
	// annee = 1900 + dt->tm_year;
	//mois = 1+dt->tm_mon;
	//jour = dt->tm_mday;

}
bool Date::operator <(const Date& d) const{
    // À compléter:
    return false;
}
int Date::operator - (const Date& date) const { // retorne le nombre des jours entre deux dates
	// À compléter:
	return 0;
}
std::ostream& operator << (std::ostream& os, const Date& d){
    int a=2024, m=6, j=7; // <<=== utilisez le paramètre d au lieu de 2024-06-07
    char chaine[40];
    sprintf(chaine, "%04d-%02d-%02d", a, m, j);
    os << chaine;
    return os;
}

std::istream& operator >> (std::istream& is, Date& d){
    int a=0, m=0, j=0;
    char t1=0,t2=0;
    is >> a >> t1 >> m >> t2 >> j;
    assert(t1=='-');
    assert(t2=='-');
    // À compléter: transférez les valeur a,m,j dans l'objet d.
    return is;
}



