#pragma once
#include <iostream>
#include <locale>

template <typename T>
class Node {
 public:
  T value;

  Node() = default;
  Node(T value_)
      : value(value_), parent(nullptr), left(nullptr), right(nullptr) {}

  Node(const Node& other)
      : value(other.value),
        parent(other.parent),
        left(other.left),
        right(other.right) {}

  Node* parent = nullptr;
  Node* left = nullptr;
  Node* right = nullptr;
};

template <typename T, typename Allocator = std::allocator<Node<T>>>
class Tree {
  typedef T value_type;
  typedef size_t size_type;

 public:
  void Insert(int value);

  void Remove(int value);

  Node<value_type>* Find(const value_type& value);

  Node<value_type>* Copy(Node<value_type>* node);

  void Deallocate();

  Node<value_type>* Next(value_type value);

  size_type GetSize() { return size_; }

  Node<value_type>* GetRoot() { return this->root_; }

  void SetRoot(Node<T>* node) { root_ = node; }

  void SetSize(int size) { size_ = size; }

  std::allocator<Node<value_type>> get_allocator() { return this->allocator_;}

 private:
  Node<value_type>* Insert(Node<value_type>* node, int value);
  Node<T>* Remove(Node<T>* node, int value);
  Node<value_type>* Min(Node<value_type>* node);
  Node<value_type>* Find(Node<value_type>* node, value_type value);
  void Deallocate(Node<value_type>* node);

  Node<value_type>* Next(Node<value_type>* node, value_type value) {
    Node<value_type>* result = nullptr;

    while (node != nullptr) {
      if (value < node->value) {
        if (result == nullptr || node->value < result->value) {
          result = node;
        }
        node = node->left;
      } else {
        node = node->right;
      }
    }

    return result;
  }

  Allocator allocator_;

  Node<value_type>* root_;
  size_type size_ = 0;
};

template <typename T, typename Allocator>
Node<T>* Tree<T, Allocator>::Insert(Node<T>* node, int value) {
  if (node == nullptr) {
    Node<T>* new_node = allocator_.allocate(1);
    std::allocator_traits<Allocator>::construct(allocator_, new_node, value);
    ++size_;

    return new_node;
  }

  if (value < node->value) {
    node->left = Insert(node->left, value);

    node->left->parent = node;

  } else if (value > node->value) {
    node->right = Insert(node->right, value);

    node->right->parent = node;
  }

  return node;
}

template <typename T, typename Allocator>
void Tree<T, Allocator>::Insert(int value) {
  this->root_ = Insert(this->root_, value);
}

template <typename T, typename Allocator>
Node<T>* Tree<T, Allocator>::Min(Node<T>* node) {
  while (node->left != nullptr) {
    node = node->left;
  }

  return node;
}

template <typename T, typename Allocator>
void Tree<T, Allocator>::Remove(int value) {
  this->root_ = Remove(this->root_, value);
}

template <typename T, typename Allocator>
Node<T>* Tree<T, Allocator>::Remove(Node<T>* node, int value) {
  if (node == nullptr) return node;

  if (value < node->value) {
    node->left = Remove(node->left, value);

    if (node->left) {
      node->left->parent = node;
    }
  } else if (value > node->value) {
    node->right = Remove(node->right, value);

    if (node->right) {
      node->right->parent = node;
    }
  } else {
    if (node->left == nullptr) {
      Node<T>* temp = node->right;
      delete node;
      --size_;

      return temp;
    } else if (node->right == nullptr) {
      Node<T>* temp = node->left;
      delete node;
      --size_;

      return temp;
    }

    Node<T>* temp = Min(node->right);
    node->value = temp->value;

    node->right = Remove(node->right, temp->value);
  }

  return node;
}

template <typename T, typename Allocator>
Node<T>* Tree<T, Allocator>::Find(Node<T>* node, T value) {
  if (node == nullptr || node->value == value) {
    return node;
  }

  if (node->value < value) {
    return Find(node->right, value);
  } else {
    return Find(node->left, value);
  }
}

template <typename T, typename Allocator>
Node<T>* Tree<T, Allocator>::Copy(Node<T>* node) {
  if (node == nullptr) return node;

  Node<T>* new_node = allocator_.allocate(1);
  std::allocator_traits<Allocator>::construct(allocator_, new_node,
                                              node->value);
  new_node->right = Copy(node->right);

  if (new_node->right != nullptr) {
    new_node->right->parent = new_node;
  }

  new_node->left = Copy(node->left);
  if (new_node->left != nullptr) {
    new_node->left->parent = new_node;
  }

  return new_node;
}

template <typename T, typename Allocator>
void Tree<T, Allocator>::Deallocate(Node<T>* node) {
  if (node == nullptr) return;

  Deallocate(node->left);
  Deallocate(node->right);
  --size_;
  std::allocator_traits<Allocator>::destroy(allocator_, node);
  allocator_.deallocate(node, 1);
}

template <typename T, typename Allocator>
Node<T>* Tree<T,Allocator>::Find(const T& value) {
    return Find(this->root_, value);
}

template <typename T, typename Allocator>
void Tree<T, Allocator>::Deallocate() {
    Deallocate(this->root_);
    this->root_ = nullptr;
}
template <typename T, typename Allocator>
Node<T>* Tree<T, Allocator>::Next(T value) { return Next(this->root_, value); }
