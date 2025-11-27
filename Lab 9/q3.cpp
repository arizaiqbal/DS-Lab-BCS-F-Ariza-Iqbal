#include <iostream>
using namespace std;

class Node
{
public:
    int key, height;
    Node *left;
    Node *right;

    Node(int k)
    {
        key = k;
        height = 1;
        left = right = NULL;
    }
};

int h(Node *n) { return n ? n->height : 0; }
int bal(Node *n) { return n ? h(n->left) - h(n->right) : 0; }

Node *fix(Node *n)
{
    n->height = 1 + max(h(n->left), h(n->right));
    return n;
}

Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *t2 = x->right;

    x->right = y;
    y->left = t2;

    fix(y);
    fix(x);

    return x;
}

Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *t2 = y->left;

    y->left = x;
    x->right = t2;

    fix(x);
    fix(y);

    return y;
}

Node *insertNode(Node *root, int key)
{
    if (!root)
        return new Node(key);

    if (key < root->key)
        root->left = insertNode(root->left, key);
    else
        root->right = insertNode(root->right, key);

    fix(root);

    int balance = bal(root);

    if (balance > 1 && key < root->left->key)
        return rightRotate(root);

    if (balance < -1 && key > root->right->key)
        return leftRotate(root);

    if (balance > 1 && key > root->left->key)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && key < root->right->key)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void print(Node *r)
{
    if (!r)
        return;
    print(r->left);
    cout << r->key << " ";
    print(r->right);
}

int main()
{
    Node *root = NULL;
    int arr[] = {10, 5, 15, 3, 7};

    for (int i = 0; i < 7; i++)
        root = insertNode(root, arr[i]);

    root = insertNode(root, 12);

    cout << "Final Balanced AVL Tree: ";
    print(root);

    return 0;
}
