/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

void removeutil(SymEntry* root, string k){
    if(k<root->key){
        removeutil(root->left, k);
    }else if(k>root->key){
        removeutil(root->right, k);
    }
    if(root->left==NULL && root->right==NULL){
        delete root;
        return;
    }
    if(root->left==NULL || root->right==NULL){
        if(root->left){
            root->val = root->left->val;
            root->key = root->left->key;
            delete root->left;
            return;
        }else{
            root->val = root->right->val;
            root->key = root->right->key;
            delete root->right;
            return;
        }
    }
    SymEntry* succP = root;
    SymEntry* succ = root->right;
    while(succ->left!=NULL){
        succP = succ;
        succ = succ->left;
    }
    if(succP !=root){
        succP->left = succ->right;
    }else{
        succP->right = succ->right;
    }
    root->val = succ->val;
    root->key = succ->key;
    delete succ;
    return;
}

void insertHelper(SymEntry* node, string k, UnlimitedRational* v) {
    // Implement BST insertion logic
    if (k < node->key) {
        if (node->left == nullptr) {
            node->left = new SymEntry(k, v);
        } else {
            insertHelper(node->left, k, v);
        }
    } else if (k > node->key) {
        if (node->right == nullptr) {
            node->right = new SymEntry(k, v);
        } else {
            insertHelper(node->right, k, v);
        }
    }
}

UnlimitedRational* searchutil(SymEntry* root, string k){
    if(root==NULL) return NULL;
    if(root->key>k){
        return searchutil(root->left, k);
    }else if(root->key<k){
        return searchutil(root->right, k);
    }else{
        return root->val;
    }
}

SymbolTable::SymbolTable(){
    this->size = 0;
    this->root = new SymEntry();
};

SymbolTable::~SymbolTable(){
    if(root!=NULL){
        delete root;
    }
};

void SymbolTable::insert(string k, UnlimitedRational* v){
    if(root==NULL){
        root = new SymEntry(k, v);
    } else {
        // Implement insertion into the BST
        insertHelper(root, k, v);
    }
    size++;
};

void SymbolTable::remove(string k){
    if(root==NULL) return;
    removeutil(root, k);
    size--;
};



UnlimitedRational* SymbolTable::search(string k){
    if(root==NULL) return NULL;
    if(root->key>k){
        return searchutil(root->left, k);
    }else if(root->key<k){
        return searchutil(root->right, k);
    }else{
        return root->val;
    }
};

int SymbolTable::get_size(){
    return size;
};

SymEntry* SymbolTable::get_root(){
    return root;
};
