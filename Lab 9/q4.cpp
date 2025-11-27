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

    void kthSmallest(Node* r, int& k, int& ans) {
        if (!r) return;
        kthSmallest(r->left, k, ans);
        k--;
        if (k == 0) { ans = r->key; return; }
        kthSmallest(r->right, k, ans);
    }

    void kthLargest(Node* r, int& k, int& ans) {
        if (!r) return;
        kthLargest(r->right, k, ans);
        k--;
        if (k == 0) { ans = r->key; return; }
        kthLargest(r->left, k, ans);
    }
};

int main() {
    AVL t;
    int arr[] = {50,30,70,20,40,60,80};
    for (int x : arr) t.insert(x);

    int k1 = 3, k2 = 2;
    int small = -1, large = -1;

    t.kthSmallest(t.root, k1, small);
    t.kthLargest(t.root, k2, large);

    cout << "Kth Smallest: " << small << endl;
    cout << "Kth Largest: " << large << endl;

    cout << "Left Height: " << t.getHeight(t.root->left) << endl;
    cout << "Right Height: " << t.getHeight(t.root->right) << endl;
}
