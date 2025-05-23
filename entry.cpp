/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"

SymEntry::SymEntry(){
    this->key = "";
    this->val = new UnlimitedRational();
    this->left = NULL;
    this->right = NULL;
};

SymEntry::SymEntry(string k, UnlimitedRational* v){
    this->key = k;
    this->val = v;
    this->left = NULL;
    this->right = NULL;
};

SymEntry::~SymEntry(){
    delete val;
    if(left!=NULL) delete left;
    if(right!=NULL) delete right;
};