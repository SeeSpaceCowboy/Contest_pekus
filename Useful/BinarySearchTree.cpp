/* Как устроено бинарное дерево поиска:

        (x1)          
      /      \
   (x2)      (x3)      # Левый элемент всегда меньше родительского
  /   \     /    \     # Правый элемент всегда больше родительского
(x4) (x5)  (x6) (x7)

*/


class BST {
 private:
  struct Node {
    int value;
    Node* left;
    Node* right;
  };
  enum Relation { LEFT_CHILD, RIGHT_CHILD, UNKNOWN };
  struct NodesPair {
    Node* parent;
    Node* node;
    Relation relation;
  };

  Node* root_ = nullptr;
  int size_ = 0;

 public:
  bool Add(int value) {
    NodesPair nodes = FindParentNode(value);
    if (nodes.node) {
      return false;
    }
    ++size_;
    if (!root_) {
      root_ = new Node{value, nullptr, nullptr};
      return true;
    }
    if (nodes.relation == RIGHT_CHILD) {
      nodes.parent->right = new Node{value, nullptr, nullptr};
    } else {
      nodes.parent->left = new Node{value, nullptr, nullptr};
    }
    return true;
  }

  void PrintInOrder() {
    if (root_ != nullptr) {
      PrintInOrderFromSmth(root_->left);
      std::cout << root_->value << ' ';
      PrintInOrderFromSmth(root_->right);
    }
  }
  void PrintInOrderFromSmth(Node* smth_node) {
    if (smth_node != nullptr) {
      PrintInOrderFromSmth(smth_node->left);
      std::cout << smth_node->value << ' ';
      PrintInOrderFromSmth(smth_node->right);
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
};
