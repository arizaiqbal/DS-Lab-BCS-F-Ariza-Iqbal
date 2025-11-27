#include <iostream>
using namespace std;

class AVL {
public:
    struct Node {
        int key, height;
        Node* left;
        Node* right;
        Node(int k) : key(k), height(1), left(NULL), right(NULL) {}
    };
    Node* root = NULL;

    int getHeight(Node* n) { return n ? n->height : 0; }

    int getBalance(Node* n) { return n ? getHeight(n->left) - getHeight(n->right) : 0; }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }

    Node* insertRec(Node* node, int key) {
        if (!node) return new Node(key);
        if (key < node->key) node->left = insertRec(node->left, key);
        else if (key > node->key) node->right = insertRec(node->right, key);

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key) return rightRotate(node);
        if (balance < -1 && key > node->right->key) return leftRotate(node);
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    void insert(int key) { root = insertRec(root, key); }

    void preorder(Node* r) {
        if (!r) return;
        cout << r->key << " ";
        preorder(r->left);
        preorder(r->right);
    }
};

int main() {
    AVL t;
    int arr[] = {50,30,70,20,40,60,80};
    for(int x : arr) t.insert(x);
    t.insert(55);

    t.root = t.leftRotate(t.root);

    t.preorder(t.root);
}
