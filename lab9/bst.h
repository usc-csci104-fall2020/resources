#ifndef BST_H
#define BST_H

#include <vector>

class Node {
public:
	Node(Node *left, Node *right, int key) {
		this->left = left;
		this->right = right;
		this->key = key;
	};

	Node(int key) {
		this->left = nullptr;
		this->right = nullptr;
		this->key = key;
	}

    Node *left;
    Node *right;
    int key;
};

int rangeSum(Node *root, int L, int R);
bool isBalanced(Node *root);
std::vector<std::vector<int>> levelOrder(Node* root);

#endif