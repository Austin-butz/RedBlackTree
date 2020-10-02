#include <iostream>
using namespace std;
#ifndef RBT_H
#define RBT_H

struct Node {
  int data;
  Node *parent;
  Node *left;
  Node *right;
  int color;
};

class RedBlackTree {
    public: 
        RedBlackTree();

        Node* create_node(Node* parent, const int& entry);

        string ToInfixString() {string output; return ToInfixStringp(root, output); };
        
        string ToPrefixString() {string output; return ToPrefixStringp(root, output); };
        
        string ToPostfixString() {string output; return ToPostfixStringp(root, output); };

        void preorder(Node* node);

        void inorder(Node* node);

        void postorder(Node* node);

        bool Contains(int entry);

        bool containshelper(Node* node, int entry);

        size_t Size() {return numItems;}

        void printtreehelper(Node* node, size_t depth);

        void printTree();

        void rightrotate(Node* input);

        void leftrotate(Node* input);

        void sorttree(Node* input);

        int GetMin();

        int GetMax();

        void Insert(int Target);
    
    private:
        unsigned long long int numItems;
        Node* root;
        Node* nullnode;

        string ToPostfixStringp(Node* node, string &output);

        string ToPrefixStringp(Node* node, string &output);

        string ToInfixStringp(Node* node, string &output);
};

#endif