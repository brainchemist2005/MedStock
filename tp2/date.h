/*  AUTEUR(S):
    1) BOUARGAN Zakariae BOUZ90340206
*/

#if !defined(__DATE_H__)
#define __DATE_H__

#include <iostream>

using namespace std;

class Date{
  public:
    Date();

    Date(const string& Syear, const string& Smonth, const string& Sday);

    int year,month,day;


	// � compl�ter
    bool operator <(const Date& date) const;
    int operator - (const Date& date)const;

  private:

  friend std::ostream& operator << (std::ostream&, const Date& date);
  friend std::istream& operator >> (std::istream&, Date& date);
};

#endif
