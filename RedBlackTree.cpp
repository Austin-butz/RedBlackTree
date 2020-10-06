#include <cassert>  //for assert
#include <iomanip>  //for setw
#include <iostream> //for cout
#include <vector> //for tree_array()
#include "RedBlackTree.h"

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

RedBlackTree::~RedBlackTree() {
  vector<int> temp;
  tree_vector(root, temp);
  for (int i = 0; i < temp.size(); i++) deletenode(temp[i]);
}

void RedBlackTree::tree_vector(Node* node, vector<int> &output) {
    if (node != nullnode && node->data != 0)
    {
        tree_vector(node->left, output);
        output.push_back(node->data);
        tree_vector(node->right, output);
    }
    return;
}

RedBlackTree::RedBlackTree(const RedBlackTree &old) {
  nullnode = new Node;
  nullnode->color = 0;
  nullnode->left = nullptr;
  nullnode->right = nullptr;
  root = nullnode;
  numItems = 0;
  vector<int> temp;
  tree_vector(old.root, temp);
  for (int i = temp.size()-1; i >= 0; i--) {
    this->Insert(temp[i]);
  }
}

Node* RedBlackTree::findsibling(Node* input) {
  if (input->parent == nullptr) {
    return nullptr;
  }
  if (input->parent->left != nullnode && input->parent->left != input) {
    return input->parent->left;
  }
  else return input->parent->right;
}

Node* RedBlackTree::replacement(Node* input) {
  if (input->left != nullnode and input->right != nullnode) {
    Node* temp = input->right;
    while (temp->left != nullnode) temp = temp->left;
    return temp;
  }
  else if (input->left == nullnode && input->right == nullnode) {
    return nullptr;
  }
  else {
    if (input->left == nullnode) return input->right;
    else return input->left;
  }
}

void RedBlackTree::fixdoubleblack(Node* input) {
  if (input = root) return;
  Node* sibling = findsibling(input);
  Node* parent = input->parent;
  if (sibling == nullptr) fixdoubleblack(parent);
  else {
    if (sibling->color == 1) {
      parent->color = 1;
      sibling->color = 0;
      if (sibling->parent->right == sibling) leftrotate(parent);
      else rightrotate(parent);
      fixdoubleblack(input);
    }
    else {
      if ((sibling->left->color == 1 || sibling->right->color == 1) || (sibling->left->color == 1 && sibling->right->color == 1)) {
          if (sibling->left != nullnode && sibling->left->color == 1) {
            if (sibling->parent->left == sibling) {
            sibling->left->color = sibling->color;
            sibling->color = parent->color;
            rightrotate(parent);
          }
          else {
            sibling->left->color = parent->color;
            rightrotate(sibling);
            leftrotate(parent);
          }
        }
        else {
          if (sibling->parent->left == sibling) {
            sibling->right->color = parent->color;
            leftrotate(sibling);
            rightrotate(parent);
          }
          else {
            sibling->right->color = sibling->color;
            sibling->color = parent->color;
            leftrotate(parent);
          }
        }
        parent->color = 0;
      }
      else {
        sibling->color = 1;
        if (parent->color == 0) fixdoubleblack(parent);
        else parent->color = 0;
      }
    }
  }
}

void RedBlackTree::deletenode(int input) {//When doing my speed test I got a duration of 0 for every deletion, meaning this program is incredibly fast
  Node* current = root;
  Node* parent;
  while (current->data != input) {
    parent = current;
    if (input > current->data) current = current->right;
    else current = current->left;
  }
  Node* replacement = this->replacement(current);
  bool doubleblack = ((replacement == nullptr || replacement->color == 0) && current->color == 0);
  if (replacement == nullptr) {
    if (current == root) root = nullptr;
    else {
      if (doubleblack) {
        fixdoubleblack(current);
        }
      else if (findsibling(current) != nullnode && findsibling(current) != nullptr) {
        findsibling(current)->color = 1;
      }
      if (findsibling(current) == parent->left) {
        parent->right = nullnode;
      }
      else {
        parent->left = nullnode;
      }
    }
    delete current;
    return;
  }
  if (current->left == nullnode || current->right == nullnode) {
    if (current->data == root->data) {
      current->data = replacement->data;
      current->left = nullnode;
      current->right = nullnode;
      delete replacement;
    }
    else {
      if (current->parent->left = current) parent->left = replacement;
      else parent->right = replacement;
      delete current;
      replacement->parent = parent;
      if (doubleblack) {
        fixdoubleblack(replacement);
      }
      else replacement->color = 0;
    }
    return;
  }
  if (replacement->left == nullnode && replacement->right == nullnode) {
    int temp = current->data;
    current->data = replacement->data;
    replacement->data = temp;
    Node* tempo = replacement->parent;
    if (replacement->parent->right == replacement) {
      replacement->parent->right = nullnode;
      delete replacement;
    }
    if (replacement->parent->left == replacement) {
      replacement->parent->left = nullnode;
      delete replacement;
    }
    if (doubleblack) fixdoubleblack(tempo);
  }
  else {
    int temp = current->data;
    current->data = replacement->data;
    replacement->data = temp;
    deletenode(temp);
  }
}

string RedBlackTree::ToPostfixStringp(Node* node, string &output)
{
    if (node != nullnode)
    {
      ToPostfixStringp(node->left, output);
      ToPostfixStringp(node->right, output);
      output = output + " ";
      if (node->color == 0) output = output + "B";
      else output = output + "R";
      output = output + to_string(node->data);
      output = output + " ";
    }
    return output;
}

string RedBlackTree::ToInfixStringp(Node* node, string &output)
{
    if (node != nullnode)
    {
      ToInfixStringp(node->left, output);
      output = output + " ";
      if (node->color == 0) output = output + "B";
      else output = output + "R";
      output = output + to_string(node->data);
      output = output + " ";
      ToInfixStringp(node->right, output);
    }
    return output;
}

string RedBlackTree::ToPrefixStringp(Node* node, string &output)
{
    if (node != nullnode)
    {
      output = output + " ";
      if (node->color == 0) output = output + "B";
      else output = output + "R";
      output = output + to_string(node->data);
      output = output + " ";
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
        } 
        else {
          if (input == input->parent->left) {
            input = input->parent;
            rightrotate(input);
          }
          input->parent->color = 0;
          input->parent->parent->color = 1;
          leftrotate(input->parent->parent);
        }
      } 
      else {
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
    if (tempnode->right != nullnode) tempnode->right->parent = input;
    tempnode->parent = input->parent;
    if (input->parent == nullptr) root = tempnode;
    else if (input == input->parent->right) input->parent->right = tempnode;
    else input->parent->left = tempnode;
    tempnode->right = input;
    input->parent = tempnode;
  }

  void RedBlackTree::leftrotate(Node* input) {
    Node* tempnode = input->right;
    input->right = tempnode->left;
    if (tempnode->left != nullnode) tempnode->left->parent = input;
    tempnode->parent = input->parent;
    if (input->parent == nullptr) root = tempnode;
    else if (input == input->parent->left) input->parent->left = tempnode;
    else input->parent->right = tempnode;
    tempnode->left = input;
    input->parent = tempnode;
  }

  void RedBlackTree::Insert(int key) {//When doing my speed test I got a duration of 0 for every insertion, meaning this program is incredibly fast
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
      } 
      else {
        node3 = node3->right;
      }
    }
    node->parent = node2;
    if (node2 == nullptr) {
      root = node;
    } 
    else if (node->data < node2->data) {
      node2->left = node;
    } 
    else {
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

bool RedBlackTree::Contains(int entry) {
  string check = ToPostfixString();
  string find = to_string(entry);
  if (check.find(find) > check.size()) return false;
  else return true;
}



