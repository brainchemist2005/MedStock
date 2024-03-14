/*  AUTEUR(S):
    1) Bouargan Zakariae BOUZ90340206
*/

#include "stock.h"


Stock& Stock::operator+=(const Medication& med) {
    root = insert(root, med);
    return *this;
}

int Stock::getHeight(const AVLNode* node) {
    if (!node) return 0;
    return node->height;
}

int Stock::getBalance(const AVLNode* node) {
    if (!node) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

AVLNode* Stock::rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = nullptr;

    if (x != nullptr) {
        T2 = x->right;
        x->right = y;
    }
    y->left = T2;

    // Update heights
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    if (x != nullptr) {
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    }

    return x; // New root
}


AVLNode* Stock::leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = nullptr;

    if (y != nullptr) {
        T2 = y->left;
        y->left = x;
    }
    x->right = T2;

    // Update heights
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    if (y != nullptr) {
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    }

    return y; // New root
}


AVLNode* Stock::insert(AVLNode* node, const Medication& med) {
    if (node == nullptr) {
        return new AVLNode(med);
    }

    if (med.name < node->data.name) {
        node->left = insert(node->left, med);
    } else if (node->data.name < med.name) {
        node->right = insert(node->right, med);
    } else {
        node->data.quantity += med.quantity;
        return node;
    }



    // Step 2: Update height of this ancestor node
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    // Step 3: Get the balance factor to check whether this node became unbalanced
    int balance = getBalance(node);

    // Step 4: If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && med.expirationDate < node->left->data.expirationDate) {
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && node->right->data.expirationDate < med.expirationDate) {
        return leftRotate(node);
    }

    // Left Right Case
    if (balance > 1 && node->left->data.expirationDate < med.expirationDate) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && med.expirationDate < node->right->data.expirationDate) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }


    // Return the (unchanged) node pointer
    return node;
}

void Stock::printInOrder(const AVLNode* node) {
    if (node == nullptr) {
        return; // Base case: empty subtree
    }
    printInOrder( node->left); // Visit left subtree
    // Process current node: print medication information
    cout <<  node->data.name << " "
        << node->data.quantity << " "
        << node->data.expirationDate << std::endl;
    printInOrder( node->right); // Visit right subtree
}

Medication *Stock::search(AVLNode *node, const string &name) {
    if (node == nullptr) {
        return nullptr; // Base case: not found
    }

    if (name < node->data.name) {
        // If the search key is less than the node's key, search in the left subtree
        return search(node->left, name);
    } else if (name > node->data.name) {
        // If the search key is greater than the node's key, search in the right subtree
        return search(node->right, name);
    } else {
        // Found a node with a matching key
        return &(node->data);
    }
}

std::ostream& operator << (std::ostream& os, Stock& stock){

	return os;
}

