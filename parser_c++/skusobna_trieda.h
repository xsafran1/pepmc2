#include <cstdlib>
#include <string>
#include <vector>
#include <stack>

class Skusobna {
public:
	std::vector<std::string> var;
	std::vector<double> constant;
	std::vector<std::string> ramp;
	std::vector<std::string> sigm;
	std::vector<std::string> step;

};
/*
enum value_t {
    number,
    var,
    ramp,
    step,
    sigm,
    none_v
}
enum op_t {
    plus,
    minus,
    times,
    bracket,
    none_o
}
struct Node {
    value_t valueType;
    std::string value;
    op_t operation;
    Node* parent;
    std::vector<Node*> children;
};

class Tree {
    Node* root;
    std::stack<Node*> store;

    public:
    Tree() {}
    Tree(Node* r) : root(r) {}

    void addNode(value_t vt, std::string v);
    void addNode(op_t op);
};

void Tree::addNode(value_t vt, std::string v) {
    Node* n = new Node();
    n->valueType = vt;
    n->value = v;
    n->operation = none_o;
    n->parent = NULL;
    n->children = std::vector<Node*>();

    store.push(n);
}

void Tree::addNode(op_t op) {
}
*/
