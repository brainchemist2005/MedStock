/*  AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/
#if !defined(__STOCK_H__)
#define __STOCK_H__

#include <iostream>


class Stock{
  public:
	Stock& operator+=(const Stock& autre);

  private:

  friend std::ostream& operator << (std::ostream&, Stock&);
};

#endif

