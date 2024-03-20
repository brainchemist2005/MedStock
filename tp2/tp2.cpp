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
#include <vector>

using namespace std;

std::vector<Medication> table;

void insert(const Medication& value) {
    bool found = false;
    size_t updateIndex = 0;

    for (size_t i = 0; i < table.size(); ++i) {
        if (table[i].name == value.name) {
            table[i].quantity += value.quantity;
            found = true;
            updateIndex = i;
            break;
        }
    }

    if (found) {
        Medication updatedMed = table[updateIndex];
        table.erase(table.begin() + updateIndex);
        insert(updatedMed);
    } else {
        size_t insertPos = 0;
        while (insertPos < table.size() && table[insertPos].name < value.name) {
            ++insertPos;
        }
        table.insert(table.begin() + insertPos, value);
    }
}


int tp2(istream& entree,Stock& stock){
    Date maintenant;
    int i=0;

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
            int traitement;
            cout << "PRESCRIPTION " << ++i << endl;
            while(entree && nomMed!=";"){
            	int dose;
            	int rep;
            	entree >> dose >> rep;
                traitement = dose*rep;
                Medication *med = stock.searcher(nomMed,maintenant);
                if(med != nullptr && med-> quantity >= traitement){
                        cout << med->name << " " << dose << " " << rep << "  OK" << endl;
                        med->quantity -= traitement;
                }

                else {
                    cout << nomMed <<" " << dose << " " << rep << "  COMMANDE" << endl;
                    Medication med(nomMed,dose*rep);
                    insert(med);
                }

            	entree >> nomMed;
            }

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
                Medication med(nomMed, quantite, dateexpiration, maintenant);
                stock.insert(med);
        		entree >> nomMed;
            }
        	// ? compl?ter
        	cout << "APPROV OK";
        }else if(typecommande=="STOCK"){
        	char pointvirgule=0;
            string prescription;
            entree >> pointvirgule;
            assert(pointvirgule==';');
            cout << "STOCK " << maintenant << endl;
            stock.printInOrder(maintenant);
        }else if(typecommande=="DATE"){
        	char pointvirgule=0;
        	entree >> maintenant >> pointvirgule;
        	assert(pointvirgule==';');
            if((int)table.size() == 0)
                cout << maintenant << " OK" << endl;

            else
                cout << maintenant << " COMMANDES :" << endl;

            for(int j=0 ; j< (int)table.size() ; j++)
                cout << table[j].name << " " << table[j].quantity << endl;
            table.clear();
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
    Stock stock;
    // Gestion de l'entr?e :
    //  - lecture depuis un fichier si un argument est sp?cifi?;
    //  - sinon, lecture depuis std::cin.
    if(argc>1){
         std::ifstream entree_fichier(argv[1]);
         if(entree_fichier.fail()){
             std::cerr << "Erreur d'ouverture du fichier '" << argv[1] << "'" << std::endl;
             return 1;
         }
          tp2(entree_fichier,stock);

         return 0;
    }else
         return tp2(std::cin,stock);
}




