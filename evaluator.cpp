/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"

using namespace std;

Evaluator::Evaluator(){
    symtable = new SymbolTable();
};

Evaluator::~Evaluator(){
    for (ExprTreeNode* expr_tree : expr_trees) {
        delete expr_tree;
    }

    delete symtable;
};

bool is_variable(string s){
    return ((s[0] >= 'a') && (s[0] <= 'z')) || ((s[0] >= 'A') && (s[0] <= 'Z'));
}

string identify(string s){
    if (s == "+") return "ADD";
    if (s == "-") return "SUB";
    if (s == "*") return "MUL";
    if (s == "/") return "DIV";
    else return "MOD";
}

ExprTreeNode* make_node(string s, SymbolTable* symtable){
    ExprTreeNode* node = new ExprTreeNode();
    if (is_variable(s)){
        UnlimitedRational* x = symtable->search(s);
        node->type = "VAR";
        node->evaluated_value = x;
        node->id = s;
    }
    else{
        node->type = "VAL";
        UnlimitedInt* n = new UnlimitedInt(s);
        UnlimitedInt* d = new UnlimitedInt("1");
        node->val = new UnlimitedRational(n, d);
        node->evaluated_value = node->val;
    }
    return node;
}

UnlimitedRational* valuate(string op, UnlimitedRational* o1, UnlimitedRational* o2){
    if (op == "ADD") return UnlimitedRational::add(o1, o2);
    if (op == "SUB") return UnlimitedRational::sub(o1, o2);
    if (op == "MUL") return UnlimitedRational::mul(o1, o2);
    if (op == "DIV") return UnlimitedRational::div(o1, o2);
    else{
        string p1 = o1->get_p_str();
        string p2 = o2->get_p_str();
        UnlimitedInt* x1 = new UnlimitedInt(p1);
        UnlimitedInt* x2 = new UnlimitedInt(p2);
        UnlimitedInt* res = UnlimitedInt::mod(x1, x2);
        UnlimitedInt* d = new UnlimitedInt(1);
        UnlimitedRational* ans = new UnlimitedRational(res, d);
        return ans;
    }
}

ExprTreeNode* make_operator_node(string s, ExprTreeNode* leftNode, ExprTreeNode* rightNode){
    ExprTreeNode* Node = new ExprTreeNode();
    Node->type = identify(s);
    Node->evaluated_value = valuate(Node->type, leftNode->evaluated_value, rightNode->evaluated_value);
    Node->left = leftNode;
    Node->right = rightNode;
    return Node;
}

bool is_operator(string s){
    return (s == "+" || s == "-" || s == "*" || s == "/" || s == "%");
}

void Evaluator::parse(vector<string> code){
    vector<string> stack;
    vector<ExprTreeNode*> tree_stack;
    int len = code.size();
    for (int i=2; i<len; i++){
        if (code[i] == "("){
            continue;
        }
        else if (code[i] == ")"){
            string op = stack[stack.size()-1];
            ExprTreeNode* rightNode = tree_stack[tree_stack.size() - 1];
            tree_stack.pop_back();
            ExprTreeNode* leftNode = tree_stack[tree_stack.size()-1];
            tree_stack.pop_back();
            ExprTreeNode* Node = make_operator_node(op, leftNode, rightNode);
            tree_stack.push_back(Node);
            stack.pop_back();
            continue;
        }
        else if (is_operator(code[i])){
            stack.push_back(code[i]);
            continue;
        }
        else{
            ExprTreeNode* temp = make_node(code[i], symtable);
            tree_stack.push_back(temp);
        }
    }
    ExprTreeNode* rightNode = tree_stack[0];
    ExprTreeNode* node = new ExprTreeNode();
    node->type = "VAR";
    node->id = code[0];
    ExprTreeNode* eq_node = new ExprTreeNode();
    eq_node->type = "EQ";
    eq_node->right = rightNode;
    eq_node->left = node;
    expr_trees.push_back(eq_node);
    return;
};

void Evaluator::eval(){
    ExprTreeNode* temp = expr_trees[expr_trees.size()-1];
    symtable->insert(temp->left->id, temp->right->evaluated_value);
    temp->evaluated_value = temp->right->evaluated_value;
    temp->left->evaluated_value = temp->evaluated_value;
}