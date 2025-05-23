/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"
#include <string>
using namespace std;

ExprTreeNode::ExprTreeNode(){
    this->type = "";
    this->val = new UnlimitedRational();
    this->evaluated_value = new UnlimitedRational();
    this->id = "";
    this->left = NULL;
    this->right = NULL;
};

ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v){
    type = t;
    UnlimitedInt* q = new UnlimitedInt(1);
    val = new UnlimitedRational(v,q);
    evaluated_value = new UnlimitedRational();
    id = "";
    left = NULL;
    right = NULL;
};

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v){
    type = t;
    val = v;
    evaluated_value = new UnlimitedRational();
    id = "";
    left = NULL;
    right = NULL;
};

ExprTreeNode::~ExprTreeNode(){
    if (val != nullptr) {
        delete val;
        val = nullptr;
    }

    if (evaluated_value != nullptr) {
        delete evaluated_value;
        evaluated_value = nullptr;
    }

    // Recursively delete objects within the left and right subtrees
    if (left != nullptr) {
        delete left;
        left = nullptr;
    }

    if (right != nullptr) {
        delete right;
        right = nullptr;
    }
};