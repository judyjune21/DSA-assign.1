#include <iostream>
#include <cmath>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

Node* insert(Node* root, int data) {
    if (root == nullptr) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    return root;
}

Node* constructBSTFromArray(int arr[], int n) {
    Node* root = nullptr;
    for (int i = 0; i < n; i++) {
        root = insert(root, arr[i]);
    }
    return root;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

Node* deleteNode(Node* root, int key) {
    if (root == nullptr) {
        return root;
    }

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

int height(Node* root) {
    if (root == nullptr) {
        return -1;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return max(leftHeight, rightHeight) + 1;
}

void printNodeLevelAndHeight(Node* root, int nodeData, int level = 0) {
    if (root == nullptr) {
        cout << "Node not found!" << endl;
        return;
    }
    if (root->data == nodeData) {
        cout << "Level of Node " << nodeData << ": " << level << endl;
        cout << "Height of Node " << nodeData << ": " << height(root) << endl;
        return;
    }
    if (nodeData < root->data) {
        printNodeLevelAndHeight(root->left, nodeData, level + 1);
    } else {
        printNodeLevelAndHeight(root->right, nodeData, level + 1);
    }
}

void printTreeInOrder(Node* root) {
    if (root != nullptr) {
        printTreeInOrder(root->left);
        cout << root->data << " ";
        printTreeInOrder(root->right);
    }
}

int main() {
    int arr[] = {30, 20, 40, 10, 25, 35, 45, 5, 15};
    int n = sizeof(arr) / sizeof(arr[0]);

    Node* root = constructBSTFromArray(arr, n);

    cout << "Inorder Traversal of BST: ";
    printTreeInOrder(root);
    cout << endl;

    int nodeToDelete = 20;
    root = deleteNode(root, nodeToDelete);
    cout << "BST after deleting node: " << nodeToDelete << ": ";
    printTreeInOrder(root);
    cout << endl;

    cout << "Height of BST: " << height(root) << endl;

    int nodeToFind = 10;
    printNodeLevelAndHeight(root, nodeToFind);

    return 0;
}
