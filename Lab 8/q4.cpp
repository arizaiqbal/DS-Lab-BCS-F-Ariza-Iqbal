#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node(int v) {
        data = v;
        left = right = NULL;
    }
};

class BST {
public:
    Node* root;
    BST() { root = NULL; }

    Node* insert(Node* node, int v) {
        if (!node) return new Node(v);
        if (v < node->data) node->left = insert(node->left, v);
        else if (v > node->data) node->right = insert(node->right, v);
        return node;
    }

    void insert(int v) {
        root = insert(root, v);
    }

    bool search(Node* node, int v) {
        if (!node) return false;
        if (node->data == v) return true;
        if (v < node->data) return search(node->left, v);
        return search(node->right, v);
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }
};

int main() {
    BST t;

    t.insert(40);
    t.insert(20);
    t.insert(60);
    t.insert(10);
    t.insert(30);
    t.insert(50);
    t.insert(70);

    int value;
    cout << "Enter value to search: ";
    cin >> value;

    if (t.search(t.root, value)) {
        cout << "Value already exists " << endl;
    } else {
        cout << "Value not found. Inserting it " << endl;
        t.insert(value);
    }

    cout << "Updated tree: ";
    t.inorder(t.root);

    return 0;
}
