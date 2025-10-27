#include <iostream>
#include <sstream>
#include "BinaryTree.h"

using namespace std;

int AVL_check(TreeNode<int>* root){
    if (!root) return 0;

   int hl = AVL_check(root->left);
   int hr = AVL_check(root->right);

   if (hl == -1 || hr == -1 || abs(hl - hr) > 1)
       return -1; // не сбалансировано

   return max(hl, hr) + 1;
}

int main() {
    FBTree<int> tree;
    
    string enter;
    getline(cin, enter);
    stringstream ss(enter);
    
    string num;
    while (ss >> num){
        int numInt = stoi(num);
        TINSERT(tree, numInt);
    }
    PRINT(tree.root);
    if (AVL_check(tree.root) != -1){
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
