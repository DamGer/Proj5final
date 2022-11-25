#include <iostream>
#include <list>
#include <vector>
using namespace std;

/*A binary tree node has data, pointer to left leave
and a pointer to right leave*/
template<typename T>
struct TreeNode
{
    T data;
    TreeNode* left;
    TreeNode* right;
};
/* A helper function that creates a new node 
with the given data and NULL left and right pointers */
template<typename T>
TreeNode<T>* newTreeNode(T data)
{
    TreeNode<T>* Node = new TreeNode<T>();
    Node->data = data;
    Node->left = nullptr;
    Node->right = nullptr;
    return(Node);
}
/* The struction contains tree depth and max paths in tree */
template<typename T>
struct MaxPaths {
    int depth = 0;
    int size = 0;
    MaxPaths();
    ~MaxPaths();
    MaxPaths<T> Unite(MaxPaths<T> right_subtree);
    void push_back(T data);
    void clear();
    vector<list <T>> element;
};

/* The function calculates the tree depth and max paths 
then return struction MaxPaths */
template<typename T>
MaxPaths<T> maxPaths(TreeNode<T>* node)
{
    if (node == nullptr) {
        MaxPaths<T> zero;
        return zero;
    }
    else
    {
        /* A recursive function call for the left and right subtrees */
        MaxPaths<T> lSubtree = maxPaths(node->left);
        MaxPaths<T> rSubtree = maxPaths(node->right);
        /* use the larger subtree to add new data
        to list(s) and return up to function */
        if (lSubtree.depth > rSubtree.depth) {
            lSubtree.push_back(node->data);
            rSubtree.clear();
            return lSubtree;
        }
        else if (lSubtree.depth < rSubtree.depth) {
                rSubtree.push_back(node->data);
                lSubtree.clear();
                return rSubtree;
            }
        /* if struct is leave create new struct and add its data */
        else if ((lSubtree.depth==rSubtree.depth) &&(node->right == nullptr) && (node->left == nullptr)) {
            MaxPaths<T> leave;
            leave.push_back(node->data);
            return leave;
            }
        /* if left subtree equal right subtree */
        else {
            lSubtree.Unite(rSubtree);
            lSubtree.push_back(node->data);
            return lSubtree;
        }
    }
}


template<typename T>
MaxPaths<T>::MaxPaths()
{
    list<T> a;
    this->element.push_back(a);
    size++;
}

template<typename T>
MaxPaths<T> MaxPaths<T>::Unite(MaxPaths<T> right)
{
    int k = right.size;
    while (k) {
        this->element.push_back(right.element[--k]);
        this->size++;
    }
    right.clear();
    return *this;
}

template<typename T>
void MaxPaths<T>::push_back(T data)
{
    int k = this->size;
        while (k) {
            this->element[--k].push_back(data);
        }
        /* Tree depth icrease by 1 when 
        the node's data is added to the list */
        this->depth++;
}

template<typename T>
MaxPaths<T>::~MaxPaths()
{
    this->element.clear();
}

template<typename T>
void MaxPaths<T>::clear()
{
    this->element.clear();
}

/* test code */
int main()
{
    TreeNode<int>* root = newTreeNode(0);
    root->left = newTreeNode(1);
    root->right = newTreeNode(2);
    root->right->right = newTreeNode(4);
    root->left->right = newTreeNode(5);
    root->left->left = newTreeNode(3);
    root->left->left->left = newTreeNode(7);
    root->left->left->left->left = newTreeNode(11);
    root->left->left->left->right = newTreeNode(9);
 /*
             0
           /   \
          1     2
        /   \    \
       3     5    4
      /
     7
   /   \
  11    9
    
 */
    MaxPaths<int> tree = maxPaths(root);
    cout << "Depth of binary tree is " << tree.depth << endl;
    return 0;
}
