#ifndef SYMMETRICAL_H
#define SYMMETRICAL_H

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

bool isSymmetrical(Node *root);
// Add helper function(s) here

#endif