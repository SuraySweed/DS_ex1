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
	Node* left;
	Node* right;
};

template <class T>
class AVLTree {
private:
	Node<T>* _root;
	
	int max(int num1, int num2);
	Node<T>* rightRotate(Node<T>* root);
	Node<T>* leftRotate(Node<T>* root);
	Node<T>* balanceTree(Node<T>* root);
	Node<T>* auxInsert(Node<T>* root, Node<T>* newNode);
	Node<T>* findMinNodeInSubTree(Node<T>* subTreeRoot);
	void auxRemove(Node<T>* root, Node<T>* node);
	void deleteTree(Node<T>* root);

public:
	AVLTree<T>();
	AVLTree<T>(const AVLTree<T>& avlTree);
	~AVLTree();

	int getHeight(Node<T>* node);
	int getBalance(Node<T>* node);
	Node<T>* getRoot() { return _root; }
	Node<T>* insert(Node<T>* root, T* data);
	Node<T>* find(Node<T>* root, const T& data);
	//bool remove(const T& data);
	Node<T>* remove(Node<T>* root, T* data);
	//T* inorder(Node<T>* root, int num, T* arr[]);
};



template<class T>
inline Node<T>::Node(const T& data_t) : data(new T(data_t)), left(nullptr), right(nullptr) {}

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
inline Node<T>* AVLTree<T>::rightRotate(Node<T>* root)
{
	Node<T>* root_left = root->left;
	Node<T>* root_right = root_left->right;

	root_left->right = root;
	root->left = root_right;

	return root_left;
}

template<class T>
inline Node<T>* AVLTree<T>::leftRotate(Node<T>* root)
{
	Node<T>* root_right = root->right;
	Node<T>* root_left = root_right->left;

	root_right->left = root;
	root->right = root_left;

	return root_right;
}

template<class T>
inline Node<T>* AVLTree<T>::balanceTree(Node<T>* root)
{
	int balance_factor = getBalance(root);
	if (balance_factor > 1) {
		if (getBalance(root->left) < 0)
			root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	else if (balance_factor < -1) {
		if (getBalance(root->right) > 0)
			root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
}
/*
template<class T>
inline Node<T>* AVLTree<T>::auxInsert(Node<T>* root, Node<T>* newNode)
{
	if (root && (*(newNode->data) <= *(root->data))) {
		if (root->left) {
			root->left = auxInsert(root->left, newNode);
		}
		else {
			root->left = newNode;
			//newNode->parent = root;
		}
	}

	else {
		if (root->right) {
			root->right = auxInsert(root->right, newNode);
		}
		else {
			root->right = newNode;
			//newNode->parent = root;
		}
	}
	root = balanceTree(root);
	return root;
}
*/
template<class T>
inline Node<T>* AVLTree<T>::findMinNodeInSubTree(Node<T>* subTreeRoot)
{
	while (subTreeRoot && subTreeRoot->left) {
		subTreeRoot = subTreeRoot->left;
	}
	return subTreeRoot;
}

/*
template<class T>
inline void AVLTree<T>::auxRemove(Node<T>* root, Node<T>* node)
{
	if (root == node) {
		if (root->left == nullptr && root->right == nullptr) {
			if (root->parent == nullptr) {
				root = nullptr;
				_root = root;

			}
			else {
				if (root->parent->left == root)
					root->parent->left = nullptr;
				else
					root->parent->right = nullptr;
			}
			delete node;
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
*/


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
inline Node<T>* AVLTree<T>::insert(Node<T>* root , T* data)
{
	if (root == nullptr) {
		root = new Node<T>(*data);
		if (_root == nullptr) {
			_root = root;
		}
		return root;
	}

	if (*data < *(root->data)) {
		root->left = insert(root->left, data);
	}
	else if (*data > *(root->data)) {
		root->right = insert(root->right, data);
	}
	else {
		return root;
	}

	root = balanceTree(root);
	return root;
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
inline Node<T>* AVLTree<T>::remove(Node<T>* root, T* data)
{
	if (root == nullptr) {
		return root;
	}

	if (*data < *(root->data)) {
		root->left = remove(root->left, data);
	}

	else if (*data > *(root->data)) {
		root->right = remove(root->right, data);
	}

	else {
		if ((root->left == nullptr) || (root->right == nullptr)) {
			Node<T>* temp = root->left ? root->left : root->right;
			if (temp == nullptr) {
				temp = root;
				root = nullptr;
			}
			else {
				*(root) = *(temp);
			}
			delete temp;
		}
		else {
			Node<T>* temp = findMinNodeInSubTree(root->right);
			*(root->data) = *(temp->data);
			root->right = remove(root->right, temp->data);
		}
	}

	if (root == nullptr) {
		return root;
	}

	root = balanceTree(root);
	return root;
}
/*
template<class T>
inline bool AVLTree<T>::remove(const T& data)
{
	Node<T>* node = find(_root, data);
	if (!_root || !node)
		return false;
	else
		auxRemove(_root, node);
	return true;
}*/

#endif