#ifndef AVLTREE_H
#define AVLTREE_H

#include "AVLNode.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

class AVLERR {
public :
	std::string error;
	AVLERR();
	AVLERR(std::string info) {
		error = info;
	}
};

inline int MIN(int a, int b) {
	return a < b ? a : b;
}

//-----------------------------------------AVL tree-----------------------------------------
template<class T1, class T2 = NULLT>
class AVLTree {

private :
	Node<T1, T2> *root;
	int size;
	int(*cmp)(const T1 &a, const T1 &b);

	int calcHeight(const Node<T1, T2> * const node) const;
	int calcSize(const Node<T1, T2> * const node) const;
	Node<T1, T2>* rotateLL(Node<T1, T2> *N1);
	Node<T1, T2>* rotateRR(Node<T1, T2> *N1);
	Node<T1, T2>* rotateLR(Node<T1, T2> *N1);
	Node<T1, T2>* rotateRL(Node<T1, T2> *N1);
	Node<T1, T2>* plug(Node<T1, T2> *node, const T1 &id);

public :
	// constructors and destructor
	AVLTree();
	AVLTree(int(*compare)(const T1 &a, const T1 &b));
	AVLTree(const Node<T1, T2> &head, int(*compare)(const T1 &a, const T1 &b) = NULL);
	AVLTree(const T1 &rootID, const T2 * const rootRcd = NULL, int(*compare)(const T1 &a, const T1 &b) = NULL);
	AVLTree(const T1 &rootID, const T2 &rootRcd, int(*compare)(const T1 &a, const T1 &b) = NULL);
	AVLTree(const AVLTree<T1, T2> &New);
	~AVLTree();

	bool setCmp(int(*compare)(const T1 &a, const T1 &b));
	bool addRoot(const T1 &id, const T2 * const rcd = NULL);
	bool addRoot(const T1 &id, const T2 &rcd);
	bool addRoot(const Node<T1, T2> &New);

	bool insert(const T1 &id);
	bool empty();

	int getSize() const { return size; }
	T2 *find(const T1 &id) const;
};

////////////////////////////////////////////////////////////////////////////////
//        NAME: AVLTree
// DESCRIPTION: Constructor of AVLTree class.
//   ARGUMENTS: none
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
AVLTree<T1, T2>::AVLTree() {
	root = NULL;
	size = 0;
	cmp = NULL;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: AVLTree
// DESCRIPTION: Constructor of AVLTree class.
//   ARGUMENTS: int(*compare)(const T1 &a, const T1 &b) = NULL - the compare function
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
AVLTree<T1, T2>::AVLTree(int(*compare)(const T1 &a, const T1 &b)) {
	root = NULL;
	size = 0;
	cmp = compare;
}
////////////////////////////////////////////////////////////////////////////////
//        NAME: AVLTree
// DESCRIPTION: Constructor of AVLTree class.
//   ARGUMENTS: const Node<T1, T2> &head - the root node of the AVL tree
//				int(*compare)(const T1 &a, const T1 &b) = NULL - the compare function
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
AVLTree<T1, T2>::AVLTree(const Node<T1, T2> &head, int(*compare)(const T1 &a, const T1 &b)) {
	root = new Node<T1, T2>(head);
	size = calcSize(root);
	cmp = compare;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: AVLTree
// DESCRIPTION: Constructor of AVLTree class.
//   ARGUMENTS: const T1 &rootID - the ID of the root node
//				const T2 * const rootRcd = NULL - the initial root record
//				int(*compare)(const T1 &a, const T1 &b) = NULL - the compare function
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
AVLTree<T1, T2>::AVLTree(const T1 &rootID, const T2 * const rootRcd, int(*compare)(const T1 &a, const T1 &b)) {
	root = new Node<T1, T2>(rootID, rootRcd);
	size = 1;
	cmp = compare;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: AVLTree
// DESCRIPTION: Constructor of AVLTree class.
//   ARGUMENTS: const T1 &rootID - the ID of the root node
//				const T2 &rootRcd - the initial root record
//				int(*compare)(const T1 &a, const T1 &b) = NULL - the compare function
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
AVLTree<T1, T2>::AVLTree(const T1 &rootID, const T2 &rootRcd, int(*compare)(const T1 &a, const T1 &b)) {
	root = new Node<T1, T2>(rootID, rootRcd);
	size = 1;
	cmp = compare;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: AVLTree
// DESCRIPTION: Copy constructor of AVLTree class.
//   ARGUMENTS: const AVLTree<T1, T2> &Old - the AVLTree that is to be copied
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
AVLTree<T1, T2>::AVLTree(const AVLTree<T1, T2> &Old) {
	size = Old.size;
	cmp = Old.cmp;
	root = new Node<T1, T2>;
	root->copy(Old.root);
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: AVLTree
// DESCRIPTION: Destructor of AVLTree class.
//   ARGUMENTS: none
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
AVLTree<T1, T2>::~AVLTree() {
	cout << "Destructor: ";
	if (root != NULL)
		cout << root->getID();
	cout << endl;
	delete root;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: calcHeight
// DESCRIPTION: To get the height of a node in AVL tree.
//   ARGUMENTS: const Node<T1, T2> * const node - the node of which the height we want
// USES GLOBAL: none
// MODIFIES GL: none
//     RETURNS: int
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
int AVLTree<T1, T2>::calcHeight(const Node<T1, T2> * const node) const {
	if (node == NULL)
		return -1;
	return node->getHeight();
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: calcSize
// DESCRIPTION: To calculate the size of the tree with the root "node".
//   ARGUMENTS: const Node<T1, T2> * const node - the root the of tree
// USES GLOBAL: none
// MODIFIES GL: none
//     RETURNS: int
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
int AVLTree<T1, T2>::calcSize(const Node<T1, T2> * const node) const {
	if (node == NULL)
		return 0;
	else
		return calcSize(node->getLft()) + calcSize(node->getRgt()) + 1;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: setCmp
// DESCRIPTION: To assign the compare function to the member function pointer.
//   ARGUMENTS: int(*compare)(const T1 &a, const T1 &b) - the compare function
// USES GLOBAL: none
// MODIFIES GL: cmp
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool AVLTree<T1, T2>::setCmp(int(*compare)(const T1 &a, const T1 &b)) {
	cmp = compare;
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: addRoot
// DESCRIPTION: To add a root for the AVL tree.
//   ARGUMENTS: const T1 &id - the id of the root node
//				const T2 * const rcd - the record of the root node with default value NULL
// USES GLOBAL: none
// MODIFIES GL: root, size
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool AVLTree<T1, T2>::addRoot(const T1 &id, const T2 * const rcd) {
	if (root != NULL) {
		throw AVLERR("root already exists");
	}
	root = new Node<T1, T2>(id, rcd);
	size = calcSize(root);
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: addRoot
// DESCRIPTION: To add a root for the AVL tree.
//   ARGUMENTS: const T1 &id - the id of the root node
//				const T2 &rcd - the record of the root node
// USES GLOBAL: none
// MODIFIES GL: root, size
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool AVLTree<T1, T2>::addRoot(const T1 &id, const T2 &rcd) {
	if (root != NULL) {
		throw AVLERR("root already exists");
	}
	root = new Node<T1, T2>(id, rcd);
	size = calcSize(root);
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: addRoot
// DESCRIPTION: To add a root for the AVL tree.
//   ARGUMENTS: const Node<T1, T2> &New - the copy of the root node
// USES GLOBAL: none
// MODIFIES GL: root, size
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool AVLTree<T1, T2>::addRoot(const Node<T1, T2> &New) {
	if (root != NULL) {
		throw AVLERR("root already exists");
	}
	root = new Node<T1, T2>(New);
	size = calcSize(root);
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: empty
// DESCRIPTION: To delete all the nodes in the AVL tree.
//   ARGUMENTS: none
// USES GLOBAL: none
// MODIFIES GL: root, size
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool AVLTree<T1, T2>::empty() {
	if (root == NULL)
		return true;
	delete root;
	root = NULL;
	size = 0;
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: find
// DESCRIPTION: To find a node of a certain ID in AVL tree.
//   ARGUMENTS: const T1 &id - the ID of the node that we want to find
// USES GLOBAL: none
// MODIFIES GL: none
//     RETURNS: T2*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
T2 *AVLTree<T1, T2>::find(const T1 &id) const {
	Node<T1, T2> *p = root;
	while ((p != NULL) && (cmp(p->getID(), id) != 0)) {
		if (cmp(id, p->getID()) > 0)
			p = p->getRgt();
		else
			p = p->getLft();
	}
	if (p == NULL)
		return NULL;
	return p->getRcd();
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: rotateLL
// DESCRIPTION: The single rotation LL of AVL tree.
//   ARGUMENTS: Node<T1, T2> *N1 - the trouble finder node
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>* AVLTree<T1, T2>::rotateLL(Node<T1, T2> *N1) {
	Node<T1, T2> *N2 = N1->getLft();
	N1->AddLft(N2->getRgt());
	N2->AddRgt(N1);

	// update the height
	N1->ModifyHeight(MAX(calcHeight(N1->getLft()), calcHeight(N1->getRgt())) + 1);
	N2->ModifyHeight(MAX(calcHeight(N2->getLft()), calcHeight(N2->getRgt())) + 1);
	return N2;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: rotateRR
// DESCRIPTION: The single rotation RR of AVL tree.
//   ARGUMENTS: Node<T1, T2> *N1 - the trouble finder node
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>* AVLTree<T1, T2>::rotateRR(Node<T1, T2> *N1) {
	Node<T1, T2> *N2 = N1->getRgt();
	N1->AddRgt(N2->getLft());
	N2->AddLft(N1);

	// update the height
	N1->ModifyHeight(MAX(calcHeight(N1->getLft()), calcHeight(N1->getRgt())) + 1);
	N2->ModifyHeight(MAX(calcHeight(N2->getLft()), calcHeight(N2->getRgt())) + 1);
	return N2;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: rotateLR
// DESCRIPTION: The single rotation LR of AVL tree.
//   ARGUMENTS: Node<T1, T2> *N1 - the trouble finder node
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>* AVLTree<T1, T2>::rotateLR(Node<T1, T2> *N1) {
	Node<T1, T2> *N2 = N1->getLft();
	Node<T1, T2> *N3 = N2->getRgt();
	N2->AddRgt(N3->getLft());
	N1->AddLft(N3->getRgt());
	N3->AddLft(N2);
	N3->AddRgt(N1);

	// update the height
	N1->ModifyHeight(MAX(calcHeight(N1->getLft()), calcHeight(N1->getRgt())) + 1);
	N2->ModifyHeight(MAX(calcHeight(N2->getLft()), calcHeight(N2->getRgt())) + 1);
	N3->ModifyHeight(MAX(calcHeight(N3->getLft()), calcHeight(N3->getRgt())) + 1);
	return N3;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: rotateRL
// DESCRIPTION: The single rotation RL of AVL tree.
//   ARGUMENTS: Node<T1, T2> *N1 - the trouble finder node
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>* AVLTree<T1, T2>::rotateRL(Node<T1, T2> *N1) {
	Node<T1, T2> *N2 = N1->getRgt();
	Node<T1, T2> *N3 = N2->getLft();
	N2->AddLft(N3->getRgt());
	N1->AddRgt(N3->getLft());
	N3->AddLft(N1);
	N3->AddRgt(N2);

	// update the height
	N1->ModifyHeight(MAX(calcHeight(N1->getLft()), calcHeight(N1->getRgt())) + 1);
	N2->ModifyHeight(MAX(calcHeight(N2->getLft()), calcHeight(N2->getRgt())) + 1);
	N3->ModifyHeight(MAX(calcHeight(N3->getLft()), calcHeight(N3->getRgt())) + 1);
	return N3;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: plug
// DESCRIPTION: plug a node into the AVL tree.
//   ARGUMENTS: Node<T1, T2> *N1 - the root of the subtree that contains the new node
//				const T1 &id - the id of the new node that is to be plugged in
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>* AVLTree<T1, T2>::plug(Node<T1, T2> *node, const T1 &id) {
	if (node == NULL) {
		node = new Node<T1, T2>(id);
		++size;
	}
	else if (cmp(id, node->getID()) > 0) {
		node->AddRgt(this->plug(node->getRgt(), id));
		if (calcHeight(node->getRgt()) - calcHeight(node->getLft()) >= 2) {
			if (cmp(id, node->getRgt()->getID()) > 0)
				node = this->rotateRR(node);
			else
				node = this->rotateRL(node);
		}
	}
	else if (cmp(id, node->getID()) < 0) {
		node->AddLft(this->plug(node->getLft(), id));
		if (calcHeight(node->getLft()) - calcHeight(node->getRgt()) >= 2) {
			if (cmp(id, node->getLft()->getID()) < 0)
				node = this->rotateLL(node);
			else
				node = this->rotateLR(node);
		}
	}
	node->ModifyHeight(MAX(calcHeight(node->getLft()), calcHeight(node->getRgt())) + 1);
	return node;
}

template<class T1, class T2>
bool AVLTree<T1, T2>::insert(const T1 &id) {
	root = plug(root, id);
	return true;
}

#endif