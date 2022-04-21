#ifndef GENERIC_AVL_TREE_H_
#define GENERIC_AVL_TREE_H_

#include <iostream>

template<class T>
class Node {
public:
	Node(const T& data_t) :data(data_t), parent(NULL), left(NULL), right(NULL), height(0) {}

	Node(const Node<T>& node); //copy constructor

	Node<T>& operator=(const Node<T>& node);

	~Node() {
		delete data;
	}

	T* data;
	Node<T>* parent;
	Node<T>* left;
	Node<T>* right;
	int height;
};


template<class T>
class AVLTree {
private:
	Node<T>* _root;

	void deleteTree(Node<T>* root) {
		if (root == NULL)
			return;
		deleteTree(root->left);
		deleteTree(root->right);
		delete root;
	}
	int max(int num1, int num2)
	{
		return ((num1 > num2) ? num1 : num2);
	}

	Node<T>& rightRotate(Node<T>& root) {
		//Rotate node
		Node<T>* newRoot = root->left;
		root->left = newRoot->right;
		newRoot->right = root;

		//adjust tree
		if (root->parent == nullptr) {
			_root = newRoot;
			newRoot->parent = nullptr;
		}
		else {
			if (root->parent->left == root) {
				root->parent->left = newRoot;
			}
			else {
				root->parent->left = newRoot;
			}
			newRoot->parent = root->parent;
		}
		root->parent = newRoot;
	}
	Node<T>& leftRotate(Node<T>& root) {
		//Rotate node
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

	void balanceTree(Node<T>* root);
	void auxInorder(Node<T>* root, int num, T* arr[], int index);
	void auxInsert(Node<T>* root, Node<T>* newNode);
	void auxRemove(Node<T>* root, Node<T>* node);
	Node<T>* findMinNodeInSubTree(Node<T>* root);
	//void mergeArray(T** arr1, int size1, T** arr2, int size2, T** newArr);
	//void buildTreeFromArrays(T** arr1, int size1, T** arr2, int size2)

public:
	AVLTree<T>() : root(NULL) {} //con
	AVLTree<T>(AVLTree<T>& avlTree); //copy_con
	~AVLTree() {
		deleteTree(this->root);
	}

	void insert(T* data);

	bool remove(T* data);

	int getHeight(Node<T>* node);

	int getBalance(Node<T>* node);

	T* inorder(Node<T>* root, int num, T *arr[]);

	Node<T>* find(Node<T>* root, T* data);

	///////////////////
	void help_print(Node<T>* r) const;
	void printTree() const;
	//////////////////////

};


template<class T>
inline void AVLTree<T>::balanceTree(Node<T>* root)
{
	int BF = getBalance(root);
	if (BF > 1) {
		if (getBalance(root->left) > 0)
			leftRotate(root->left);
		rightRotate(root);
	}
	else if (BF < -1) {
		if (getBalance(root->right) > 0)
			rightRotate(root->right);
		leftRotate(root);
	}
}

template<class T>
inline void AVLTree<T>::auxInsert(Node<T>* root, Node<T>* newNode)
{
	if (*(newNode->data) <= *(root->data)) {
		if (_root->left) {
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

	//AVL balancing
	balanceTree(root);
}

template<class T>
inline void AVLTree<T>::auxRemove(Node<T>* root, Node<T>* node)
{
	if (root == node) {
		if (root->left == nullptr && root->right == nullptr) {
			if (root->parent == nullptr) {
				root = nullptr;
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
			root->data = tmp->data;
			auxRemove(root->right, tmp);
		}
	}
	else if (root->data > node->data)
		auxRemove(root->right, node);
	else
		auxRemove(root->left, node);

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
inline void AVLTree<T>::insert(T* data)
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
inline bool AVLTree<T>::remove(T* data)
{
	Node<T>* node = find(_root, data);
	if (!_root || !node)
		return false;
	else
		auxRemove(_root, node);
	return true;
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
inline T* AVLTree<T>::inorder(Node<T>* root, int num, T* arr[])
{
	return NULL;
}

template<class T>
inline Node<T>* AVLTree<T>::find(Node<T>* root,T* data)
{
	if (root) {
		if (*(root->data) == *data)
			return root;
		else if (*data < *(root->data))
			return find(root->left, data);
		else
			return find(root->right, data);
	}

	return nullptr;
}

/////////////////////////////////////////////
template<class T>
void AVLTree<T>::help_print(Node<T>* r) const
{
	if (r != nullptr)
	{
		help_print(r->left);
		cout << r->data << " ";
		help_print(r->right);
	}
}
template<class T>
void AVLTree<T>::printTree() const
{
	help_print(this->_root);
}
////////////////////////////////////////////////


#endif //GENERIC_AVL_TREE_H_