/*
  INF3105 - Structures de donn?es et algorithmes
  Hiver 2020.
  TP2
*/
#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include <cmath>
#include <limits>
#include "date.h"
#include "stock.h"

using namespace std;

int tp2(istream& entree){
    Stock stock;
    Date maintenant;
    while(entree){
        string typecommande;
        entree >> typecommande;
        if(!entree) break; // d?tection fin ==> sortie

        if(typecommande=="PRESCRIPTION"){
            char deuxpoints=0;
            entree >> deuxpoints;
            assert(deuxpoints==':');
            string nomMed;
            entree >> nomMed;
            while(entree && nomMed!=";"){
            	int dose;
            	int rep;
            	entree >> dose >> rep;
            	// ? compl?ter ****
            	entree >> nomMed;
            }
            // ? compl?ter *****
            cout << "?";
        }else if(typecommande=="APPROV"){
        	string nomMed;
        	char deuxpoints=0;
        	entree >> deuxpoints;
        	assert(deuxpoints==':');
        	entree >> nomMed;
        	while(entree && nomMed!=";"){
        		int quantite;
        		Date dateexpiration;
        		entree >> quantite >> dateexpiration;
        		Medication med(nomMed,quantite,dateexpiration);
                stock.insert(med);
        		entree >> nomMed;
            }
        	// ? compl?ter
        	cout << "APPROV OK";
        }else if(typecommande=="STOCK"){
        	char pointvirgule=0,deuxpoints=0;
            string prescription;
            entree >> pointvirgule;
            assert(pointvirgule==';');
            cout << "Stock " << maintenant << endl;
            stock.printInOrder(stock.getRoot());
        }else if(typecommande=="DATE"){
        	char pointvirgule=0;
        	entree >> maintenant >> pointvirgule;
        	assert(pointvirgule==';');
            cout << maintenant << " OK" << endl;
        }else{
            cout << "Transaction '" << typecommande << "' invalide!" << endl;
            return 2;
        }
        cout << endl;
        entree >> ws; // force la lecture d'un espace blanc.
    }
    return 0;
}
// syntaxe d'appel : ./tp2 [nomfichier.txt]
int main(int argc, const char** argv){
    // Gestion de l'entr?e :
    //  - lecture depuis un fichier si un argument est sp?cifi?;
    //  - sinon, lecture depuis std::cin.
    if(argc>1){
         std::ifstream entree_fichier(argv[1]);
         if(entree_fichier.fail()){
             std::cerr << "Erreur d'ouverture du fichier '" << argv[1] << "'" << std::endl;
             return 1;
         }
         return tp2(entree_fichier);
    }else
         return tp2(std::cin);

    return 0;
}




