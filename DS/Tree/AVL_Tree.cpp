#include <iostream>
using namespace std;

// Creating AVL Tree Node
struct AVLNode {
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;
};

// Function to get the height of the tree.
int height(AVLNode* N) {
    if (N == nullptr)
        return 0;
    return N->height;
}

// Creating a helper function to get maximum of two integers.
AVLNode* newNode(int key) {
    AVLNode* node = new AVLNode();
    node->key = key;
    node->left = node->right = nullptr;
    node->height = 1; // new node starts at height 1
    return node;
}

//Implement insertion with balancing.
AVLNode* insert(AVLNode* node, int key) {
    // 1. Normal BST insert
    if (node == nullptr)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // duplicates not allowed

    // 2. Update height
    node->height = 1 + max(height(node->left), height(node->right));

    // 3. Balance the node
    int b = bal(node);

    // Left Left
    if (b > 1 && key < node->left->key)
        return rotR(node);

    // Right Right
    if (b < -1 && key > node->right->key)
        return rotL(node);

    // Left Right
    if (b > 1 && key > node->left->key) {
        node->left = rotL(node->left);
        return rotR(node);
    }

    // Right Left
    if (b < -1 && key < node->right->key) {
        node->right = rotR(node->right);
        return rotL(node);
    }

    return node; // unchanged if balanced
}

// Function to get the balance factor of each node.
int bal(AVLNode* N) {
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}

// Right rotate subtree rooted with y
void rotR(AVLNode*& y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Update root
    y = x;
}



//Algo of AVL Tree.
{
    if(bal(Ya)==+2){
        if(bal(LS)==+1){
            rotR(Ya);
        }
        else{
            rotL(LS);
            rotR(Ya);
        }
    }
    else if(bal(Ya)==-2){
        if(bal(RS)==-1){
            rotL(Ya);
        }
        else{
            rotR(RS);
            rotL(Ya);
        }
    }
}

//Add traversal functions preorder.
void preOrder(AVLNode* root) {
    if (root != nullptr) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

//Add traversal functions inorder.
void inOrder(AVLNode* root) {
    if (root != nullptr) {
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }
}

//Add traversal functions postorder.
void postOrder(AVLNode* root) {
    if (root != nullptr) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->key << " ";
    }
}

int main() {
    AVLNode* root = nullptr;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    cout << "Preorder traversal of AVL tree: ";
    preOrder(root);
    return 0;
}