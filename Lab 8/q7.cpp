#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(NULL), right(NULL) {}
};
 
Node* insertBST(Node* root, int val) {
    if (root == NULL) return new Node(val);

    if (val < root->data)
        root->left = insertBST(root->left, val);
    else
        root->right = insertBST(root->right, val);

    return root;
}
 
void inorder(Node* root, vector<int>& arr) {
    if (root == NULL) return;
    inorder(root->left, arr);
    arr.push_back(root->data);
    inorder(root->right, arr);
}
 
float findMedian(Node* root) {
    if (root == NULL) return 0;

    vector<int> arr;
    inorder(root, arr);  

    int n = arr.size();

    if (n % 2 != 0) {
        return arr[n/2];  
    }
    else {
        int first = arr[(n/2) - 1];  
        int second = arr[n/2];       
        return (first + second) / 2.0;
    }
}

int main() {
    Node* root = NULL;
 
    int values[] = {20, 10, 5, 15, 30, 25, 35};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++)
        root = insertBST(root, values[i]);

    cout << "Median = " << findMedian(root) << endl;

    return 0;
}
