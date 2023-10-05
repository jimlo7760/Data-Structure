/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#include <vector>
#include <iomanip>

#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE

///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////

//Do not implement the class here, this is a forward declaration. Implement at
//the bottom of the .h file
template<class T>
class BPlusTree;

template<class T>
class BPlusTreeNode {
public:
    BPlusTreeNode() : parent(NULL) {};

    bool is_leaf();

    bool contains(const T &key);

    //For grading only. This is bad practice to have, because
    //it exposes a private member variable.
    BPlusTreeNode *get_parent() { return parent; }

    //We need this to let BPlusTree access private members
    friend class BPlusTree<T>;

private:
    bool contains(const T &key, std::size_t low, std::size_t high);

    std::vector<T> keys;
    std::vector<BPlusTreeNode *> children;
    BPlusTreeNode *parent;
};

template<class T>
bool BPlusTreeNode<T>::is_leaf() {
    for (unsigned int i = 0; i < children.size(); i++) {
        if (children[i]) {
            return false;
        }
    }
    return true;
}

template<class T>
bool BPlusTreeNode<T>::contains(const T &key) {
    return contains(key, 0, keys.size() - 1);
}

//Private method takes advantage of the fact keys are sorted
template<class T>
bool BPlusTreeNode<T>::contains(const T &key, std::size_t low, std::size_t high) {
    if (low > high) {
        return false;
    }
    if (low == high) {
        return key == keys[low];
    }
    std::size_t mid = (low + high) / 2;
    if (key <= keys[mid]) {
        return contains(key, 0, mid);
    } else {
        return contains(key, mid + 1, high);
    }
}

///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////
template<class T>
class BPlusTree {
public:
    BPlusTree();    // default constructor

    BPlusTree(int degreeNum);       // degree-specify constructor

    // copy constructor
    BPlusTreeNode<T> *copyRec(BPlusTreeNode<T> *node);      // recursive function of copy constructor

    BPlusTree(BPlusTree<T> &tree2);     // copy constructor

    BPlusTree<T> operator=(BPlusTree<T> &tree2);        // "=" overload

    ~BPlusTree() { clear(); }

    void clear();       // delete all the nodes in the tree

    int getSize() { return this->treeSize; }

    int addKeyToNode(T &key, BPlusTreeNode<T> *node);       // insert a key into a node and remain its order
    void remFirKey(BPlusTreeNode<T> *node);     // remove the first key in the node


    BPlusTreeNode<T> *findRec(T &key, BPlusTreeNode<T> *node);      // recursive function of find
    BPlusTreeNode<T> *find(T key);      //function of find

    void insertRec(BPlusTreeNode<T> *node);     // recursive function of find
    void insert(T key);     // function of find

    void pntSidewaysRec(std::ofstream &outfile, int curLev, BPlusTreeNode<T> *node);        //recursive function of print_sideways
    void print_sideways(std::ofstream &outfile);        //   function of print_sideways

    void print_BFS(std::ofstream &outfile);

    void print_BFS_pretty_helper(std::vector<std::vector<std::vector<T> > > &keysVec, std::vector<BPlusTreeNode<T>*> nodes);
    void print_BFS_pretty(std::ofstream &outfile);
private:
    int treeSize;       // size of the tree
    BPlusTreeNode<T> *rootPtr;      // pointer to the root
};

/// Default constructor
/// \tparam T
template<class T>
BPlusTree<T>::BPlusTree() {
    this->treeSize = 0;
    this->rootPtr = NULL;
}

/// Degree-specified constructor
/// \tparam T
/// \param degreeNum
template<class T>
BPlusTree<T>::BPlusTree(int degreeNum) {
    this->treeSize = degreeNum;
    this->rootPtr = NULL;
}

/// Recursive function of copy constructor
/// \tparam T
/// \param node current-copying node
/// \return
template<class T>
BPlusTreeNode<T> *BPlusTree<T>::copyRec(BPlusTreeNode<T> *node) {
    if (node == NULL) {
        return NULL;
    }
    std::vector<T> curValVec = node->keys;
    std::vector<BPlusTreeNode<T> *> curChildVec = node->children;
    BPlusTreeNode<T> *newNode = new BPlusTreeNode<T>;
    newNode->parent = node->get_parent();
    // assigning values
    for (unsigned int i = 0; i < curValVec.size(); i++) {
        (newNode->keys).push_back(curValVec[i]);
    }
    // assigning children
    for (unsigned int i = 0; i < curChildVec.size(); i++) {
        (newNode->children)[i] = copyRec(curChildVec[i]);
    }
    return newNode;
}

/// function of copy constructor
/// \tparam T
/// \param tree2 the tree be copied
template<class T>
BPlusTree<T>::BPlusTree(BPlusTree<T> &tree2) {
    int size = tree2.getSize();
    this->treeSize = size;
    this->rootPtr = tree2.copyRec(tree2.rootPtr);
}

/// "=" overload
/// \tparam T
/// \param tree2 the tree be copied
/// \return the copied tree
template<class T>
BPlusTree<T> BPlusTree<T>::operator=(BPlusTree<T> &tree2) {
    if (this->rootPtr != tree2.rootPtr) {
        this->clear();
        int size = tree2.getSize();
        this->treeSize = size;
        if (tree2.rootPtr == NULL) {
            return (*this);
        }
        this->rootPtr = new BPlusTreeNode<T>;
        this->rootPtr = tree2.copyRec(tree2.rootPtr);
    }
    return (*this);
}

/// delete all the nodes of a current pointer
/// \tparam T
template<class T>
void BPlusTree<T>::clear() {
    BPlusTreeNode<T> *rootNode = this->rootPtr;
    if (rootNode == NULL) {
        return;
    }
    // vector of pointers to the current-level nodes
    std::vector<BPlusTreeNode<T> *> curLevel;
    // vector of pointers to the next-level ndoes
    std::vector<BPlusTreeNode<T> *> nextLevel;
    curLevel.push_back(rootNode);
    while (curLevel.size() != 0) {
        for (unsigned int i = 0; i < curLevel.size(); i++) {
            BPlusTreeNode<T> *curNode = curLevel[i];
            std::vector<BPlusTreeNode<T> *> curChild = curNode->children;
            for (unsigned int j = 0; j < curChild.size(); j++) {
                nextLevel.push_back(curChild[j]);
            }
            delete curNode;
        }
        curLevel = nextLevel;
        nextLevel.clear();
    }
}

/// Recursive function of the find function
/// \tparam T
/// \param key key to find
/// \param node current-searching node
/// \return the leaf node contain/would contain the key
template<class T>
BPlusTreeNode<T> *BPlusTree<T>::findRec(T &key, BPlusTreeNode<T> *node) {
    // check children
    std::vector<BPlusTreeNode<T> *> childVec = node->children;
    if (childVec.size() == 0) {
        // leaf node
        return node;
    }
    std::vector<T> keyVec = node->keys;
    // less than the first key, find among the first child node
    if (key < keyVec[0]) {
        return findRec(key, childVec[0]);
    }
    // find among the "middle" part
    for (unsigned int i = 1; i < keyVec.size(); i++) {
        if (key >= keyVec[i - 1] && key < keyVec[i]) {
            return findRec(key, childVec[i]);
        }
    }
    // greater than the last key, find among the last child node
    return findRec(key, childVec.back());
}

/// Fund function
/// \tparam T
/// \param key key to find
/// \return
template<class T>
BPlusTreeNode<T> *BPlusTree<T>::find(T key) {
    if (this->rootPtr == NULL) {
        return NULL;
    }
    return findRec(key, this->rootPtr);
}

/// Function to add a key into the node remaining the order
/// \tparam T
/// \param key key to add
/// \param node node to be added
/// \return index of key inserted in the node
template<class T>
int BPlusTree<T>::addKeyToNode(T &key, BPlusTreeNode<T> *node) {
    if (key < (node->keys)[0]) {
        // less than the first element
        (node->keys).push_back(key);
        for (int i = (node->keys).size() - 2; i >= 0; i--) {
            (node->keys)[i + 1] = (node->keys)[i];
        }
        (node->keys)[0] = key;
        return 0;
    }

    if (key > ((node->keys).back())) {
        // greater than the last element
        (node->keys).push_back(key);
        return (node->keys).size();
    }

    // insert in among the middle
    typename std::vector<T>::iterator itr = (node->keys).begin();
    itr++;
    int pos = 1;
    while (itr != (node->keys).end()) {
        typename std::vector<T>::iterator lastPtr = itr;
        lastPtr--;
        if (key > (*lastPtr) && key <= (*itr)) {
            (node->keys).insert(itr, key);
            break;
        }
        itr++;
        pos++;
    }
    return pos;
}

/// Remove the first key in of the node
/// \tparam T
/// \param node target node to proceed
template<class T>
void BPlusTree<T>::remFirKey(BPlusTreeNode<T> *node){
    // shifting
    for (unsigned int i = 1; i < (node -> keys).size(); i++){
        (node -> keys)[i - 1] = (node -> keys)[i];
    }
    // reduce in size
    (node -> keys).pop_back();
}

/// recursive function of insert
/// \tparam T
/// \param node node to insert
template<class T>
void BPlusTree<T>::insertRec(BPlusTreeNode<T> *node) {

    // check if the current node is full
    if ((node->keys).size() == this->treeSize) {
        BPlusTreeNode<T> *leftNode = new BPlusTreeNode<T>;
        BPlusTreeNode<T> *rightNode = new BPlusTreeNode<T>;
        // assigning value to the left node
        for (unsigned int i = 0; i < (node->keys).size() / 2; i++) {
            (leftNode->keys).push_back((node->keys)[i]);
        }
        // assigning value to the right node
        for (unsigned int i = (node->keys).size() / 2; i < (node->keys).size(); i++) {
            (rightNode->keys).push_back((node->keys)[i]);
        }

        // assigning children to the left node
        for (unsigned int i = 0; i < (node -> children).size() / 2; i++){
            (leftNode -> children).push_back((node->children)[i]);
            (leftNode -> children)[i]->parent = leftNode;
        }

        // assigning children to the right node
        for (unsigned int i = (node -> children).size() / 2; i < (node -> children).size(); i++){
            (rightNode -> children).push_back((node -> children)[i]);
            (rightNode -> children)[i - (node -> children).size() / 2]->parent = rightNode;
        }

        // if the current node is the root
        if ((node->parent) == NULL) {
            BPlusTreeNode<T> *newRoot = new BPlusTreeNode<T>;
            (newRoot->keys).push_back((rightNode->keys)[0]);
            if (!node -> is_leaf()){
                // remove the first element in the node after splitting if it is non-leaf node
                this ->remFirKey(rightNode);
            }
            delete node;
            // changing pointers
            this->rootPtr = newRoot;
            leftNode->parent = newRoot;
            rightNode->parent = newRoot;
            (newRoot->children).push_back(leftNode);
            (newRoot->children).push_back(rightNode);
            return;
        }

        // insert to the non-leaf and non-root node
        int pos = this->addKeyToNode((rightNode->keys)[0], node->parent);
        leftNode->parent = (node->parent);
        rightNode->parent = (node->parent);
        if (!node -> is_leaf()){
            // remove the first element in the node after splitting if it is non-leaf node
            this ->remFirKey(rightNode);
        }

        // if the element inserted is the last element
        if (pos == ((node->parent)->keys).size()) {
            delete node;
            ((leftNode->parent)->children).back() = leftNode;
            ((leftNode->parent)->children).push_back(rightNode);
            return insertRec(leftNode->parent);
        }
        // iterate through children to find the position of the node being splitting
        typename std::vector<BPlusTreeNode<T> *>::iterator itr = ((node->parent)->children).begin();
        int curPos = 0;
        while (curPos < pos) {
            itr++;
            curPos++;
        }
        itr = ((node->parent)->children).erase(itr);
        ((node->parent)->children).insert(itr, rightNode);
        ((node->parent)->children).insert(itr, leftNode);
        delete node;
        return insertRec(leftNode->parent);
    }
}

/// Insert function
/// \tparam T
/// \param key key to insert
template<class T>
void BPlusTree<T>::insert(T key) {
    BPlusTreeNode<T> *root = this->rootPtr;
    if (root == NULL) {
        // when the tree is NULL
        BPlusTreeNode<T> *newRoot = new BPlusTreeNode<T>;
        (newRoot->keys).push_back(key);
        this->rootPtr = newRoot;
        return;
    }

    // leaf node to add
    BPlusTreeNode<T> *addingNode = this->find(key);

    // insert the key into the leaf node
    this->addKeyToNode(key, addingNode);

    // changing its ascend parents
    this->insertRec(addingNode);
}

/// Recursive function to print sideways
/// \tparam T
/// \param outfile output file
/// \param curLev current level of the tree
/// \param node current node to print
template<class T>
void BPlusTree<T>::pntSidewaysRec(std::ofstream &outfile, int curLev, BPlusTreeNode<T> *node) {
    if (node == NULL) {
        return;
    }
    curLev++;
    std::vector<BPlusTreeNode<T> *> childVec = node->children;
    std::vector<T> keyVec = node->keys;
    // left-half leaf node
    if (childVec.size() == 0) {
        std::string spaces(curLev, '\t');
        outfile << spaces << keyVec[0];
        for (unsigned int i = 1; i < keyVec.size(); i++) {
            outfile << "," << keyVec[i];
        }
        outfile << std::endl;
        return;
    }
    for (unsigned int i = 0; i < childVec.size() / 2; i++) {
        pntSidewaysRec(outfile, curLev, childVec[i]);
    }
    // parent node
    std::string spaces(curLev, '\t');
    outfile << spaces << keyVec[0];
    for (unsigned int i = 1; i < keyVec.size(); i++) {
        outfile << "," << keyVec[i];
    }
    outfile << std::endl;
    // right-half leaf node
    for (unsigned int i = childVec.size() / 2; i < childVec.size(); i++) {
        pntSidewaysRec(outfile, curLev, childVec[i]);
    }
}

/// function to print the sideways
/// \tparam T
/// \param outfile output file
template<class T>
void BPlusTree<T>::print_sideways(std::ofstream &outfile) {
    BPlusTreeNode<T> *rootNode = this->rootPtr;
    if (rootNode == NULL){
        outfile << "Tree is empty." << std::endl;
    }
    pntSidewaysRec(outfile, -1, rootNode);
}

/// function to print by breath-first search
/// \tparam T
/// \param outfile
template<class T>
void BPlusTree<T>::print_BFS(std::ofstream &outfile) {
    BPlusTreeNode<T> *rootNode = this->rootPtr;
    if (rootNode == NULL) {
        outfile << "Tree is empty." << std::endl;
        return;
    }
    // vector store the pointer to the current-level nodes
    std::vector<BPlusTreeNode<T> *> curLevel;
    // vector store the pointer to the next-level nodes
    std::vector<BPlusTreeNode<T> *> nextLevel;
    curLevel.push_back(rootNode);
    while (curLevel.size() != 0) {
        for (unsigned int i = 0; i < curLevel.size(); i++) {
            if (i != 0){
                outfile << "\t";
            }
            BPlusTreeNode<T> *curNode = curLevel[i];
            std::vector<T> curKey = curNode->keys;
            std::vector<BPlusTreeNode<T> *> curChild = curNode->children;
            outfile << curKey[0];
            for (unsigned int j = 1; j < curKey.size(); j++) {
                outfile << "," << curKey[j];
            }
            // assigning next level
            for (unsigned int j = 0; j < curChild.size(); j++) {
                nextLevel.push_back(curChild[j]);
            }
        }
        curLevel = nextLevel;
        nextLevel.clear();
        outfile << std::endl;
    }
}

/// helper function to print BFS pretty
/// \tparam T
/// \param keysVec the 3-D vector
/// \param nodes a vector of pointers to the nodes in the current level
template<class T>
void BPlusTree<T>::print_BFS_pretty_helper(std::vector<std::vector<std::vector<T> > > &keysVec, std::vector<BPlusTreeNode<T>*> nodes){
    std::vector<BPlusTreeNode<T>*> curLev = nodes;
    std::vector<BPlusTreeNode<T>*> nextLev;
    while (curLev.size() != 0){
        std::vector<std::vector<T> > curLevKeys;
        // traverse each node in the curren level
        for (unsigned int i = 0; i < curLev.size(); i++){
            std::vector<T> curNodeKeys;
            // traverse each key in the current node
            for (unsigned int j = 0; j < (curLev[i]->keys).size(); j++){
                T curKey = (curLev[i]->keys)[j];
                curNodeKeys.push_back(curKey);
            }
            // assigning children
            for (unsigned int j = 0; j < (curLev[i]->children).size(); j++){
                BPlusTreeNode<T>* curChild = (curLev[i]->children)[j];
                nextLev.push_back(curChild);
            }
            curLevKeys.push_back(curNodeKeys);
        }
        curLev = nextLev;
        nextLev.clear();
        keysVec.push_back(curLevKeys);
    }
}

/// function for extra credit (print BFS pretty)
/// \tparam T
/// \param outfile
template<class T>
void BPlusTree<T>::print_BFS_pretty(std::ofstream &outfile) {
    std::vector<std::vector<std::vector<T> > > keyVec;
    // keyVec: vector storing keys
    // first layer: different levels
    // second layer: nodes in the current level
    // third layer: keys in the current node
    BPlusTreeNode<T>* rootNode = this -> rootPtr;
    if (rootNode == NULL){
        outfile << "This tree is empty." << std::endl;
        return;
    }
    std::vector<T> rootVec = rootNode->keys;

    // pushing the first level (root node only)
    std::vector<std::vector<T> > firstLev;
    firstLev.push_back(rootVec);
    keyVec.push_back(firstLev);
    print_BFS_pretty_helper(keyVec, rootNode->children);

    // find the maximum number of spaces is needed
    int rowWid = 0;
    for (unsigned int i = 0; i < keyVec.back().size(); i++){
        for (unsigned int j = 0; j < keyVec.back()[i].size(); j++){
            rowWid += 2;
        }
    }
    for (unsigned int i = 0; i < keyVec.size(); i++){
        // width of each node
        int nodeWid = rowWid / (keyVec[i].size() + 1);
        for (unsigned int j = 0; j < keyVec[i].size(); j++){
            std::string curNode;
            for (unsigned int k = 0; k < keyVec[i][j].size(); k++){
                curNode += std::to_string(keyVec[i][j][k]);
                curNode += " ";
            }
            // set each node with same width, filled with spaces for redundant spaces
            outfile << std::setw(nodeWid * 2) << curNode;
        }
        outfile << std::endl;
    }
}



#endif
