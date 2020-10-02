#include <cassert>  //for assert
#include <iomanip>  //for setw
#include <iostream> //for cout
#include "rbt.h"

using namespace std;

RedBlackTree::RedBlackTree() {
    nullnode = new Node;
    nullnode->color = 0;
    nullnode->left = nullptr;
    nullnode->right = nullptr;
    root = nullnode;
    numItems = 0;
}

Node* RedBlackTree::create_node(Node* parent, const int& entry)
{
    Node* result_ptr;

    result_ptr = new Node;
    result_ptr->data  = entry;
    result_ptr->left  = nullptr;
    result_ptr->right = nullptr;
    result_ptr->color = 1;
    result_ptr->parent = parent;
    return result_ptr;
}

string RedBlackTree::ToPostfixStringp(Node* node, string &output)
{
    if (node != nullnode)
    {
        ToPostfixStringp(node->left, output);
        ToPostfixStringp(node->right, output);
        output = output + to_string(node->data);
        output = output + ", ";
    }
    return output;
}

string RedBlackTree::ToInfixStringp(Node* node, string &output)
{
    if (node != nullnode)
    {
        ToInfixStringp(node->left, output);
        output = output + to_string(node->data);
        output = output + ", ";
        ToInfixStringp(node->right, output);
    }
    return output;
}

string RedBlackTree::ToPrefixStringp(Node* node, string &output)
{
    if (node != nullnode)
    {
        output = output + to_string(node->data);
        output = output + ", ";
        ToPrefixStringp(node->left, output);
        ToPrefixStringp(node->right, output);
    }
    return output;
}

void RedBlackTree::printtreehelper(Node* node, size_t depth)
{
    if (node != nullnode)
    {
        printtreehelper (node->right, depth+1);
        cout << setw(4*depth) << "";
        cout << node->data << endl;
        printtreehelper (node->left, depth+1);
    }
}

void RedBlackTree::printTree()
{
    printtreehelper(root, 0);
}

void RedBlackTree::sorttree(Node* input) {
    Node* tempnode;
    while (input->parent->color == 1) {
      if (input->parent == input->parent->parent->right) {
        tempnode = input->parent->parent->left;
        if (tempnode->color == 1) {
          tempnode->color = 0;
          input->parent->color = 0;
          input->parent->parent->color = 1;
          input = input->parent->parent;
        } else {
          if (input == input->parent->left) {
            input = input->parent;
            rightrotate(input);
          }
          input->parent->color = 0;
          input->parent->parent->color = 1;
          leftrotate(input->parent->parent);
        }
      } else {
        tempnode = input->parent->parent->right;

      if (tempnode->color == 1) {
        tempnode->color = 0;
        input->parent->color = 0;
        input->parent->parent->color = 1;
        input = input->parent->parent;
      } else {
        if (input == input->parent->right) {
          input = input->parent;
          leftrotate(input);
        }
        input->parent->color = 0;
        input->parent->parent->color = 1;
        rightrotate(input->parent->parent);
      }
    }
    if (input == root) {
      break;
    }
  }
  root->color = 0;
}

  void RedBlackTree::rightrotate(Node* input) {
    Node* tempnode = input->left;
    input->left = tempnode->right;
    if (tempnode->right != nullnode) {
      tempnode->right->parent = input;
    }
    tempnode->parent = input->parent;
    if (input->parent == nullptr) {
      root = tempnode;
    } else if (input == input->parent->right) {
      input->parent->right = tempnode;
    } else {
      input->parent->left = tempnode;
    }
    tempnode->right = input;
    input->parent = tempnode;
  }

  void RedBlackTree::leftrotate(Node* input) {
    Node* tempnode = input->right;
    input->right = tempnode->left;
    if (tempnode->left != nullnode) {
      tempnode->left->parent = input;
    }
    tempnode->parent = input->parent;
    if (input->parent == nullptr) {
      root = tempnode;
    } else if (input == input->parent->left) {
      input->parent->left = tempnode;
    } else {
      input->parent->right = tempnode;
    }
    tempnode->left = input;
    input->parent = tempnode;
  }

  void RedBlackTree::Insert(int key) {
    numItems += 1;
    Node* node = new Node;
    node->color = 1;
    node->parent = nullptr;
    node->left = nullnode;
    node->right = nullnode;
    node->data = key;
    Node* node2 = nullptr;
    Node* node3 = root;

    while (node3 != nullnode) {
      node2 = node3;
      if (node->data < node3->data) {
        node3 = node3->left;
      } else {
        node3 = node3->right;
      }
    }

    node->parent = node2;
    if (node2 == nullptr) {
      root = node;
    } else if (node->data < node2->data) {
      node2->left = node;
    } else {
      node2->right = node;
    }

    if (node->parent == nullptr) {
      node->color = 0;
      return;
    }
    
    sorttree(node);
  }

int RedBlackTree::GetMax() {
  Node* node = root;
  while (node->right != nullptr) {
    node = node->right;
  }
  return node->data;
}

int RedBlackTree::GetMin() {
  Node* node = root;
  while (node->left != nullptr) {
    node = node->left;
  }
  return node->data;  
}

int main() {
  RedBlackTree rbt = RedBlackTree();
  rbt.Insert(30);
  rbt.Insert(15);
  rbt.Insert(45);
  rbt.Insert(10);
  rbt.Insert(25);
  rbt.Insert(7);
  rbt.Insert(5);
  rbt.printTree();
  cout << endl << endl;
  cout << "size: " << rbt.Size() << endl;
  cout << "Postfix: " << rbt.ToPostfixString() << endl;
  cout << "Prefix: " << rbt.ToPrefixString() << endl;
  cout << "Infix: " << rbt.ToInfixString() << endl;
}

