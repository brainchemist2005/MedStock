/*  AUTEUR(S):
    1) Bouargan Zakariae BOUZ90340206
*/
#if !defined(__STOCK_H__)
#define __STOCK_H__

#include <iostream>
#include <string>
#include "date.h"
using namespace std;

struct Medication {
    std::string name;
    int quantity;
    Date expirationDate;
    bool expired;

    Medication(string& n, int q, Date& e , Date maintenant)
            : name(n), quantity(q), expirationDate(e) {
        if(maintenant < expirationDate)
            expired = true;
        else
            expired = false;
    }


    Medication(string& n, int q) : name(n) , quantity(q) {}

    bool operator<(const Date& other) const {
        return expirationDate - other;
    }
};

struct AVLNode {
    Medication data;
    AVLNode* left= nullptr;
    AVLNode* right = nullptr;
    int height;

    AVLNode(Medication med)
            : data(std::move(med)), height(1) {}
};

class Stock {
public:
    Stock() : root(nullptr) {}
    Stock& operator+=(const Medication& med);
    friend std::ostream& operator<<(std::ostream& os, const Stock& stock);
    void insert(const Medication& med) {
        root = insert(root, med);
    }
    Medication* searcher(const std::string& name,const Date maintenant) {
        return search(name, maintenant);
    }

    void printInOrder(Date date){
        printInOrder(root, date);
    }


private:
    AVLNode* root;

    int getHeight(const AVLNode* node);
    int getBalance(const AVLNode* node);
    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);
    AVLNode* insert(AVLNode* node, const Medication& med);
    Medication* search(const std::string& name,const Date &maintenant);
    void printInOrder(const AVLNode* node, Date date);


    void searchHelper(AVLNode *node, const string &name, const Date &maintenant, Medication *&bestMatch);
};

#endif