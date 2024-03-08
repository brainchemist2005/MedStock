/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
	Éric Beaudry
*/
#include "date.h"
#include <sstream>
#include <assert.h>
#include <vector> // std::vecteur est permis uniquement pour ce programme test.

int main()
{
    std::cout << "Vérification de la classe Date" << std::endl;
    std::stringstream str("1999-01-01 1999-01-02 1999-01-31 1999-12-01 1999-12-31 2016-12-01 2017-01-02 2017-02-01 2017-04-15 2017-05-04 2017-06-01 2017-10-17");
    std::vector<Date> dates;
    while(!str.eof()){
        Date d;
        str >> d >> std::ws;
        std::cout << d << std::endl;
        if(str) dates.push_back(d);
    }

    // Test du comparateur
    for(unsigned int i=0;i<dates.size();i++)
        for(unsigned int j=0;j<dates.size();j++){
             if(i<j){
                 if(!(dates[i]<dates[j]))
                     std::cout << "Erreur : dates[" << i << "]<dates[" << j << "] : " << dates[i] << "<" << dates[j] << " retourne faux!" << std::endl;
             }else if(j<i){
                 if(!(dates[j]<dates[i]))
                     std::cout << "Erreur : dates[" << j << "]<dates[" << i << "] : " << dates[j] << "<" << dates[i] << " retourne faux!" << std::endl;
             }else{ // i==j
                 if(dates[j]<dates[i])
                     std::cout << "Erreur : dates[" << j << "]<dates[" << i << "] : " << dates[j] << "<" << dates[i] << " retourne faux!" << std::endl;
             }
        }
    //Test du sustracteur
    for(unsigned int i=0;i<dates.size()-1;i++){
            std::cout << "("<< dates[i+1] << ") - ("<< dates[i] << ") = "<< dates[i+1]-dates[i] << std::endl;
    }
    std::cout << dates[0]-dates[1] <<std::endl;
    /*
     * 	(1999-01-01) - (1999-01-01) = 0
		(1999-01-02) - (1999-01-01) = 1
		(1999-01-31) - (1999-01-02) = 29
		(1999-12-01) - (1999-01-31) = 304
		(1999-12-31) - (1999-12-01) = 30
		(2016-12-01) - (1999-12-31) = 6180
		(2017-01-02) - (2016-12-01) = 32
		(2017-02-01) - (2017-01-02) = 30
		(2017-04-15) - (2017-02-01) = 73
		(2017-05-04) - (2017-04-15) = 19
		(2017-06-01) - (2017-05-04) = 28
		(2017-10-17) - (2017-06-01) = 138
		(2018-08-02) - (2018-07-01) = 32
     */
    std::cout << " --- FIN ---" << std::endl;
    return 0;
}




