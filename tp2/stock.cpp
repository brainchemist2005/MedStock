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
    // Base case: The spot for insertion is found
    if (node == nullptr) {
        return new AVLNode(med);
    }

    // Check for exact match (same name and expiration date) first
    if (node->data.name == med.name && node->data.expirationDate == med.expirationDate) {
        node->data.quantity += med.quantity; // Exact match found, updating quantity
        return node;
    }

    // Decide on the insertion path: left or right subtree
    if (med.name < node->data.name || (med.name == node->data.name && med.expirationDate < node->data.expirationDate)) {
        // Go left
        node->left = insert(node->left, med);
    } else {
        // Go right
        node->right = insert(node->right, med);
    }

    // Update height of the current node
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    // Calculate the balance factor to check whether this node has become unbalanced
    int balance = getBalance(node);

    // Perform rotations if necessary to maintain the AVL property

    // Left Left Case
    if (balance > 1 && (med.name < node->left->data.name || (med.name == node->left->data.name && med.expirationDate < node->left->data.expirationDate))) {
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && (med.name > node->right->data.name || (med.name == node->right->data.name &&  node->right->data.expirationDate < med.expirationDate ))) {
        return leftRotate(node);
    }

    // Left Right Case
    if (balance > 1 && (med.name > node->left->data.name || (med.name == node->left->data.name && node->left->data.expirationDate < med.expirationDate ))) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && (med.name < node->right->data.name || (med.name == node->right->data.name && med.expirationDate < node->right->data.expirationDate))) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the node pointer (potentially updated)
    return node;
}



void Stock::printInOrder(const AVLNode* node, Date date) {
    if (node == nullptr) {
        return; // Base case: empty subtree
    }


    printInOrder( node->left, date); // Visit left subtree
    // Process current node: print medication information
    if (date < node->data.expirationDate && node->data.quantity > 0) {
        cout << node->data.name << " "
             << node->data.quantity << " "
             << node->data.expirationDate << std::endl;
    }
    printInOrder( node->right, date); // Visit right subtree


}

void Stock::searchHelper(AVLNode *node, const string &name, const Date &maintenant, int desiredQuantity, Medication *&bestMatch, Date &closestExpiration) {
    if (node == nullptr) {
        return; // Base case: not found
    }

    searchHelper(node->left, name, maintenant, desiredQuantity, bestMatch, closestExpiration);

    // Check if current node matches the criteria: name matches, not expired, and sufficient quantity
    if (node->data.name == name && maintenant < node->data.expirationDate && node->data.quantity >= desiredQuantity) {
        // Update bestMatch if no match found yet or found one with a closer expiration date
        if (bestMatch == nullptr || (node->data.expirationDate < closestExpiration)) {
            bestMatch = &(node->data);
            closestExpiration = node->data.expirationDate;
        }
    }

    searchHelper(node->right, name, maintenant, desiredQuantity, bestMatch, closestExpiration);
}

// Adjusted public search function to include desiredQuantity
Medication *Stock::search(const string &name, const Date &maintenant, int desiredQuantity) {
    Medication *bestMatch = nullptr;
    Date closestExpiration; // Initialize with max possible date
    searchHelper(root, name, maintenant, desiredQuantity, bestMatch, closestExpiration); // Start the search from the root
    return bestMatch;
}


std::ostream& operator << (std::ostream& os, Stock& stock){

	return os;
}

