#ifndef GENERIC_AVL_TREE_H_
#define GENERIC_AVL_TREE_H_

#include <iostream>

template<class T>
class Node {
public:
	Node(const T& data);

	Node(const Node<T>& node); //copy constructor

	Node<T>& operator=(const Node<T>& node);

	~Node();

	T* data;
	Node<T>* parent;
	Node<T>* left;
	Node<T>* right;
	int height;
};


template<class T>
class AVLTree {
private:
	Node<T>* root;

	int max(int num1, int num2);
	Node<T>& rightRotate(Node<T>& node);
	Node<T>& leftRotate(Node<T>& node);
	void auxInorder(Node<T>& root, int num, T* arr, int index);
	//void mergeArray(T** arr1, int size1, T** arr2, int size2, T** newArr);
	//void buildTreeFromArrays(T** arr1, int size1, T** arr2, int size2)

public:
	AVLTree<T>(); //con
	AVLTree<T>(AVLTree<T>& avlTree); //copy_con
	~AVLTree();

	void insert(const T& data);

	void remove(const T& data);

	int getHieght(const Node<T>& node);

	int getBalance(const Node<T>& node);

	T* inorder(Node<T>& root, int num, T *arr);

};


#endif //GENERIC_AVL_TREE_H_
