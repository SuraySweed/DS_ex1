#ifndef GENERIC_AVL_TREE_H_
#define GENERIC_AVL_TREE_H_

#include <iostream>

template <class T>
class Node {
public:
	Node(const T& data_t);
	//Node(const T& data_t, Node<T>* parent, Node<T>* left, Node<T>* right, int height);
	Node(const Node<T>& node);
	Node<T>& operator=(const Node<T>& node);
	~Node();

	T* data;
	Node* parent;
	Node* left;
	Node* right;
	int height;
};

template <class T>
class AVLTree {
private:
	Node<T>* _root;
	
	int max(int num1, int num2);
	void rightRotate(Node<T>* root);
	void leftRotate(Node<T>* root);
	void balanceTree(Node<T>* root);
	void auxInsert(Node<T>* root, Node<T>* newNode);
	Node<T>* findMinNodeInSubTree(Node<T>* subTreeRoot);
	void auxRemove(Node<T>* root, Node<T>* node);
	void deleteTree(Node<T>* root);

public:
	AVLTree<T>();
	AVLTree<T>(const AVLTree<T>& avlTree);
	~AVLTree();

	int getHeight(Node<T>* node);
	int getBalance(Node<T>* node);
	void insert(const T& data);
	Node<T>* find(Node<T>* root, const T& data);
	bool remove(const T& data);
	//T* inorder(Node<T>* root, int num, T* arr[]);
};



template<class T>
inline Node<T>::Node(const T& data_t) : data(new T(data_t)), parent(nullptr), left(nullptr), right(nullptr), height(0) {}

/*
template<class T>
inline Node<T>::Node(const T& data_t, Node<T>* parent, Node<T>* left, Node<T>* right, int height){}
*/

template<class T>
inline Node<T>::Node(const Node<T>& node)
{
	data = new T(*(node.data));
	if (node.left) {
		left = new Node<T>(*(node.left));
	}
	else {
		left = nullptr;
	}
	if (node.right) {
		right = new Node<T>(*(node.right));
	}
	else {
		right = nullptr;
	}

}

template<class T>
inline Node<T>& Node<T>::operator=(const Node<T>& node)
{
	if (this == &node) {
		return *this;
	}
	data = new T(*(node.data));
	if (node.left) {
		left = new Node<T>(*(node.left));
	}
	else {
		left = nullptr;
	}
	if (node.right) {
		right = new Node<T>(*(node.right));
	}
	else {
		right = nullptr;
	}
	return *this;
}

template<class T>
inline Node<T>::~Node()
{
	delete data;
}


template<class T>
inline int AVLTree<T>::max(int num1, int num2)
{
	return ((num1 > num2) ? num1 : num2);
}

template<class T>
inline void AVLTree<T>::rightRotate(Node<T>* root)
{
	Node<T>* newRoot = root->left;
	root->left = newRoot->right;
	newRoot->right = root;

	if (root->parent == nullptr) {
		_root = newRoot;
		newRoot->parent = nullptr;
	}
	else {
		if (root->parent->left == root) {
			root->parent->left = newRoot;
		}
		else {
			root->parent->right = newRoot;
		}
		newRoot->parent = root->parent;
	}
	root->parent = newRoot;
}

template<class T>
inline void AVLTree<T>::leftRotate(Node<T>* root)
{
	Node<T>* newRoot = root->right;
	root->right = newRoot->left;
	newRoot->left = root;

	//adjust tree
	if (root->parent == NULL) {
		_root = newRoot;
		newRoot->parent = NULL;
	}
	else {
		if (root->parent->left == root) {
			root->parent->left = newRoot;
		}
		else {
			root->parent->right = newRoot;
		}
		newRoot->parent = root->parent;
	}
	root->parent = newRoot;
}

template<class T>
inline void AVLTree<T>::balanceTree(Node<T>* root)
{
	int balance_factor = getBalance(root);
	if (balance_factor > 1) {
		if (getBalance(root->left) < 0)
			leftRotate(root->left);
		rightRotate(root);
	}
	else if (balance_factor < -1) {
		if (getBalance(root->right) > 0)
			rightRotate(root->right);
		leftRotate(root);
	}
}

template<class T>
inline void AVLTree<T>::auxInsert(Node<T>* root, Node<T>* newNode)
{
	if (root && (*(newNode->data) <= *(root->data))) {
		if (root->left) {
			auxInsert(root->left, newNode);
		}
		else {
			root->left = newNode;
			newNode->parent = root;
		}
	}

	else {
		if (root->right) {
			auxInsert(root->right, newNode);
		}
		root->right = newNode;
		newNode->parent = root;
	}

	balanceTree(root);
}

template<class T>
inline Node<T>* AVLTree<T>::findMinNodeInSubTree(Node<T>* subTreeRoot)
{
	while (subTreeRoot && subTreeRoot->left) {
		subTreeRoot = subTreeRoot->left;
	}
	return subTreeRoot;
}

template<class T>
inline void AVLTree<T>::auxRemove(Node<T>* root, Node<T>* node)
{
	if (*(root->data) == *(node->data)) {
		if (root->left == nullptr && root->right == nullptr) {
			if (root->parent == nullptr) {
				//root = nullptr;
				delete root;
			}
			else {
				if (root->parent->left == root)
					root->parent->left = nullptr;
				else
					root->parent->right = nullptr;
			}

			//root = nullptr;
		}
		else if (root->left != nullptr && root->right == nullptr) {
			root->left->parent = root->parent;

			if (root->parent != nullptr) {
				if (root->parent->left == root)
					root->parent->left = root->left;
				else
					root->parent->right = root->left;
			}
			delete node;
		}
		else if (root->left == nullptr && root->right != nullptr) {
			root->right->parent = root->parent;
			if (root->parent != nullptr) {
				if (root->parent->left == root)
					root->parent->left = root->right;
				else
					root->parent->right = root->right;
			}
			delete node;
		}
		else {
			Node<T>* tmp = findMinNodeInSubTree(root->right);
			*(root->data) = *(tmp->data);
			auxRemove(root->right, tmp);
		}
	}
	else if (*(root->data) > *(node->data))
		auxRemove(root->left, node);
	else
		auxRemove(root->right, node);

	balanceTree(root);
}


template<class T>
inline AVLTree<T>::AVLTree() : _root(nullptr) {}

template<class T>
inline AVLTree<T>::AVLTree(const AVLTree<T>& avlTree)
{
}


template<class T>
inline void AVLTree<T>::deleteTree(Node<T>* root)
{
	if (root == NULL)
		return;
	deleteTree(root->left);
	deleteTree(root->right);
	delete root;
}

template<class T>
inline AVLTree<T>::~AVLTree()
{
	deleteTree (this->_root);
}

template<class T>
inline int AVLTree<T>::getHeight(Node<T>* node)
{
	int height = 0;
	if (node) {
		int leftHeight = getHeight(node->left);
		int rightHeight = getHeight(node->right);
		height = 1 + max(leftHeight, rightHeight);
	}
	return height;
}

template<class T>
inline int AVLTree<T>::getBalance(Node<T>* node)
{
	int balanceFactor = 0;
	if (node) {
		balanceFactor = getHeight(node->left) - getHeight(node->right);
	}
	return balanceFactor;
}

template<class T>
inline void AVLTree<T>::insert(const T& data)
{
	Node<T>* newNode = new Node<T>(data);

	if (!_root)
		_root = newNode;
	else {
		auxInsert(_root, newNode);
	}
	return;
}

template<class T>
inline Node<T>* AVLTree<T>::find(Node<T>* root, const T& data)
{
	if (root) {
		if (*(root->data) == data)
			return root;
		else if (data < *(root->data))
			return find(root->left, data);
		else
			return find(root->right, data);
	}

	return nullptr;
}

template<class T>
inline bool AVLTree<T>::remove(const T& data)
{
	Node<T>* node = find(_root, data);
	if (!_root || !node)
		return false;
	else
		auxRemove(_root, node);
	return true;
}

#endif