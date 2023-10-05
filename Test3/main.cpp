#include <iostream>
#include <vector>
#include <string>
#include <map>

template <class T>
class TreeNode {
public:
    TreeNode() : left(NULL), right(NULL), parent(NULL) {}
    TreeNode(const T& init) : value(init), left(NULL), right(NULL), parent(NULL) {}
    T value;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
};

template <class T>
const T& findLargestInTree(TreeNode<T>* nodePtr){
    T curMax = nodePtr -> value;
    if (nodePtr -> right != NULL){
        T rightMax = findLargestInTree(nodePtr -> right);
        curMax = std::max(rightMax, curMax);
    }
    return curMax;
}

template <class T>
TreeNode<T>* FindSmallestInRange(const T& a, const T& b, TreeNode<T>* root){
    if(!root){
        return NULL;
    }
    T best_value = FindLargestInTree(root);
    TreeNode<T>* ret = FindSmallestInRange(a, b, root, best_value);
    if(best_value >= b){
        return NULL;
    }
    return ret;
}

template <class T>
TreeNode<T>* FindSmallestInRange(const T& a, const T& b, TreeNode<T>* root, const T& best_val){

}
int main() {


    return 0;
}
