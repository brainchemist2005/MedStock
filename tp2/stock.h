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

    Medication(std::string n, int q, Date& e)
            : name(std::move(n)), quantity(q), expirationDate(e) {}


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
    static Date Stockdate();
    Stock() : root(nullptr) {}
    Stock& operator+=(const Medication& med);
    friend std::ostream& operator<<(std::ostream& os, const Stock& stock);
    void printInOrder(const AVLNode* node);
    void insert(const Medication& med) {
        root = insert(root, med);
    }

    AVLNode* getRoot()
    {
        return root;
    }

    void setRoot(AVLNode* root1) {
        root = root1;
    }

private:
    AVLNode* root;

    int getHeight(const AVLNode* node);
    int getBalance(const AVLNode* node);
    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);
    AVLNode* insert(AVLNode* node, const Medication& med);


};

#endif