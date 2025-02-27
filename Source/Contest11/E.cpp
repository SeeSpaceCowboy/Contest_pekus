#include <iostream>
#include <fstream>
#include <cstdint>

class BST {
 private:
  struct Node {
    int value;
    size_t repeats;
    Node* left;
    Node* right;
  };
  enum Relation { LEFT_CHILD, RIGHT_CHILD, UNKNOWN };
  struct NodesPair {
    Node* parent;
    Node* node;
    Relation relation;
  };

 public:
  bool Add(int value) {
    NodesPair nodes = FindParentNode(value);
    if (nodes.node) {
      nodes.node->repeats += 1;
      return true;
    }
    ++size_;
    if (!root_) {
      root_ = new Node{value, 1, nullptr, nullptr};
      return false;
    }
    if (nodes.relation == RIGHT_CHILD) {
      nodes.parent->right = new Node{value, 1, nullptr, nullptr};
      return false;
    }
    nodes.parent->left = new Node{value, 1, nullptr, nullptr};
    return false;
  }
  void PrintRepeats() {
    if (root_ != nullptr) {
      PrintRepeatsFromSmth(root_->left);
      if (root_->repeats > 1) {
        std::cout << root_->value << ' ';
      }
      PrintRepeatsFromSmth(root_->right);
    }
  }
  void PrintRepeatsFromSmth(Node* smth_node) {
    if (smth_node != nullptr) {
      PrintRepeatsFromSmth(smth_node->left);
      if (smth_node->repeats > 1) {
        std::cout << smth_node->value << ' ';
      }
      PrintRepeatsFromSmth(smth_node->right);
    }
  }
  void Clear() {
    ClearNode(root_);
    root_ = nullptr;
  }

 private:
  NodesPair FindParentNode(int value) const {
    if (!root_ || root_->value == value) {
      return {nullptr, root_, UNKNOWN};
    }
    if (!root_->left && !root_->right) {
      return {root_, nullptr, root_->value > value ? LEFT_CHILD : RIGHT_CHILD};
    }
    Node* runner = root_;
    Node* next = nullptr;
    Relation relation = UNKNOWN;
    while (true) {
      if (runner->value > value) {
        next = runner->left;
        relation = LEFT_CHILD;
      } else {
        next = runner->right;
        relation = RIGHT_CHILD;
      }
      if (!next || next->value == value) {
        return {runner, next, relation};
      }
      runner = next;
    }
  }
  static void ClearNode(Node* node) {
    if (!node) {
      return;
    }
    ClearNode(node->left);
    ClearNode(node->right);
    delete node;
  };

  Node* root_ = nullptr;
  int size_ = 0;
};

int main() {
  int n = 0;
  int value = 0;
  int repeats = 0;
  BST binary_tree;
  std::cin >> n;
  while (n) {
    std::cin >> value;
    if (binary_tree.Add(value)) {
      ++repeats;
    }
    --n;
  }
  std::cin >> n;
  while (n) {
    std::cin >> value;
    if (binary_tree.Add(value)) {
      ++repeats;
    }
    --n;
  }
  std::cout << repeats << '\n';
  binary_tree.PrintRepeats();
  binary_tree.Clear();
  return 0;
}
