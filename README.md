AVLTree(C++)
===================
This is the implementation of AVL tree in C++ using template.
Template
--------------------
- **T1** &#160;The type of the Node's ID
- **T2** &#160;The type of the Node's record
Members
--------------------
- **Node<T1, T2> \*root** &#160; The root of the AVL tree;
- **int size** &#160; The number of nodes of the AVL tree;
- **int (\*cmp)(const T1 &a, const T2 &b)** &#160; The function used to compare two T1s;
User Interface
--------------------
- **AVLTree()** &#160; The default constructor of AVL tree;
- **AVLTree(int(\*compare)(const T1 &a, const T1 &b))** &#160;The constructor with compare function initialized;
- **AVLTree(const Node<T1, T2> &head, int(\*compare)(const T1 &a, const T1 &b) = NULL)** &#160;The constructor with the root node and the compare function;
- **AVLTree(const T1 &rootID, const T2 \* const rootRcd = NULL, int(\*compare)(const T1 &a, const T1 &b) = NULL)** &#160;The constructor with the root node's ID and record and the compare function;
- **AVLTree(const T1 &rootID, const T2 &rootRcd, int(\*compare)(const T1 &a, const T1 &b) = NULL)** &#160;The constructor with the root ID, record, and the tree's compare function;
- **AVLTree(const AVLTree<T1, T2> &New)** &#160;The copy constructor of AVL tree;
- **~AVLTree()** &#160;The destructor of the class;
- **bool setCmp(int(\*compare)(const T1 &a, const T1 &b))** &#160;To set the compare function for the AVL tree, return true on success;
- **bool addRoot(const T1 &id, const T2 \* const rcd = NULL)** &#160;To set a root for AVL tree if it has no root;
- **bool addRoot(const T1 &id, const T2 &rcd)** &#160;To set a root for AVL tree if it has no root;
- **bool addRoot(const Node<T1, T2> &New)** &#160;To set a root for AVL tree if it has no root;
- **bool Insert(const T1 &id)** &#160;To insert a new node into the AVL tree with ID "id". It's ok to insert an already-exist node (nothing would happen then);
- **bool Delete(const T1 &id)** &#160;To delete a node into the AVL tree with ID "id". It's ok to delete a non-exist node (nothing would happen then);
- **bool empty()** &#160;To delete all the nodes in an AVL tree;
- **int getSize()** &#160;To get the number of nodes in an AVL tree;
- **int getHeight()** &#160;To get the height of the AVL tree;
- **T2 \*find(const T1 &id)** &#160;To get the pointer to the record of wanted node with ID "id". Return NULL if the node is not found;
- **T1 rootID()** &#160;To find the root's ID;
- **bool print()** &#160; To print the AVL tree inorderly. This function can be used only if the print functions has  been defined for T1 class;
