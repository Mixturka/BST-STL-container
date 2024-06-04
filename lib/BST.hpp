#pragma once
#include <sys/_types/_size_t.h>
#include <sys/wait.h>

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <locale>
#include <memory>
#include <utility>

#include "Tree.hpp"

enum class IteratorType { INORDER, POSTORDER, PREORDER };

template <typename T, typename Allocator = std::allocator<Node<T>>>
class BST {
  friend Node<T>;
  std::allocator<Node<T>> allocator_;
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef int difference_type;
  typedef uint size_type;
  typedef Allocator allocator_type;
  typedef typename std::allocator_traits<Allocator>::pointer pointer;
  typedef
      typename std::allocator_traits<Allocator>::const_pointer const_pointer;
  typedef Node<value_type>* node_type;


public:
  template <IteratorType type>
  class const_iterator {
   public:
    const_iterator(Node<value_type>* ptr);
    const_iterator(const const_iterator& other);
    const_iterator() = default;

    ~const_iterator() = default;

    const_iterator& operator++();
    const_iterator operator++(int);

    const_iterator& operator--();
    const_iterator operator--(int);

    const_iterator& operator=(const const_iterator& other);

    const value_type& operator*();

    bool operator!=(const const_iterator& other) const;
    bool operator==(const const_iterator& other) const;

   private:
    const Node<T>* ptr_;
  };

  template <typename It>
  class const_reverse_iterator {
   private:
    It current = It();

   public:
    const_reverse_iterator(Node<value_type>* ptr);
    const_reverse_iterator(const const_reverse_iterator& other);
    const_reverse_iterator() = default;

    ~const_reverse_iterator() = default;

    const_reverse_iterator& operator++();
    const_reverse_iterator operator++(int);

    const_reverse_iterator& operator--();
    const_reverse_iterator operator--(int);

    const_reverse_iterator& operator=(const const_reverse_iterator& other);

    const value_type& operator*();

    bool operator!=(const const_reverse_iterator& other) const;
    bool operator==(const const_reverse_iterator& other) const;
  };

 public:
  BST() { tree_ = Tree<T, Allocator>(); }
  BST(const BST& other);
  BST(const std::initializer_list<value_type>& ilist);

  BST& operator=(const BST& other);
  BST& operator=(const std::initializer_list<value_type>& ilist);

  ~BST();

  template <IteratorType type>
  const_iterator<type> begin();

  template <IteratorType type>
  const_iterator<type> end();

  template <IteratorType type>
  const_iterator<type> cbegin();

  template <IteratorType type>
  const_iterator<type> cend();

  template <IteratorType type>
  const_reverse_iterator<const_iterator<type>> rbegin();

  template <IteratorType type>
  const_reverse_iterator<const_iterator<type>> rend();

  template <IteratorType type>
  const_reverse_iterator<const_iterator<type>> crbegin();

  template <IteratorType type>
  const_reverse_iterator<const_iterator<type>> crend();

  bool operator==(BST& second);

  bool operator!=(const BST& second);

  void swap(BST& other);

  std::allocator<Node<value_type>> get_allocator() { return this->tree_.get_allocator(); }

  size_type size();
  size_type max_size();

  bool empty();

  void Insert(int value);

  void Remove(int value);

  template <IteratorType type>
  std::pair<const_iterator<type>, bool> insert(const value_type& value);

  template <class InputIt>
  void insert(InputIt first, InputIt last);

  void insert(std::initializer_list<value_type> ilist);

  template <IteratorType type, typename... Args>
  std::pair<const_iterator<type>, bool> emplace(Args&&... args);

  template <IteratorType type>
  const_iterator<type> erase(const_iterator<type> pos);

  template <IteratorType type>
  const_iterator<type> erase(const_iterator<type> first,
                             const_iterator<type> last);

  size_type erase(const value_type& key);

  size_type count(const value_type& key);

  template <typename K>
  size_type count(const K& x) const;

  template <IteratorType type>
  const_iterator<type> find(const value_type& key);

  template <IteratorType type, typename K>
  const_iterator<type> find(const K& key);

  bool contains(const value_type& key);

  template <typename K>
  bool contains(const K& x) const;

  template <IteratorType type>
  const_iterator<type> lower_bound(const value_type& key);

  template <IteratorType type, typename K>
  const_iterator<type> lower_bound(const K& key);

  template <IteratorType type>
  const_iterator<type> upper_bound(const value_type& key);

  template <IteratorType type, typename K>
  const_iterator<type> upper_bound(const K& key);

  Node<value_type>* extract(const value_type& key);

  void merge(BST& source);

  void clear();

 private:
  Tree<value_type, Allocator> tree_;

  Node<value_type>* Insert(Node<value_type>* node, int value);

  Node<value_type>* Min(Node<value_type>* node);

  Node<value_type>* Remove(Node<value_type>* node, int value);

  Node<value_type>* Copy(Node<value_type>* node);

  void Deallocate(Node<value_type>* node);

  void UpdateParentPointers(Node<value_type>* node, Node<value_type>* parent);
};

template <typename T, typename Allocator>
BST<T, Allocator>::BST(const std::initializer_list<value_type>& ilist) {
  this->tree_.Deallocate();
  this->insert(ilist);
}

template <typename T, typename Allocator>
BST<T, Allocator>& BST<T, Allocator>::operator=(
    const std::initializer_list<value_type>& ilist) {
  this->tree_.Deallocate();
  this->insert(ilist);

  return *this;
}

template <typename T, typename Allocator>
template <IteratorType type>
typename BST<T, Allocator>::template const_iterator<type>
BST<T, Allocator>::begin() {
  return cbegin<type>();
}

template <typename T, typename Allocator>
template <IteratorType type>
typename BST<T, Allocator>::template const_iterator<type>
BST<T, Allocator>::end() {
  return cend<type>();
}

template <typename T, typename Allocator>
BST<T, Allocator>::BST(const BST<T, Allocator>& other) {
  this->root_ = Copy(other.root_);
}

template <typename T, typename Allocator>
Node<T>* BST<T, Allocator>::Copy(Node<T>* node) {
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
BST<T, Allocator>& BST<T, Allocator>::operator=(
    const BST<T, Allocator>& other) {
  this->root_ = Copy(other.root_);
}

template <typename T, typename Allocator>
BST<T, Allocator>::~BST() {
  tree_.Deallocate();
}

template <typename T, typename Allocator>
void BST<T, Allocator>::swap(BST<T, Allocator>& other) {
  auto temp = this->tree_.GetRoot();
  this->tree_.SetRoot(other.tree_.GetRoot());
  other.tree_.SetRoot(temp);

  size_t temp_size = this->tree_.GetSize();
  this->tree_.SetSize(other.tree_.GetSize());
  other.tree_.SetSize(temp_size);
}

template <typename T, typename Allocator>
typename BST<T, Allocator>::size_type BST<T, Allocator>::size() {
  return this->tree_.GetSize();
}

template <typename T, typename Allocator>
typename BST<T, Allocator>::size_type BST<T, Allocator>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

template <typename T, typename Allocator>
bool BST<T, Allocator>::empty() {
  return begin<IteratorType::INORDER>() == end<IteratorType::INORDER>();
}

template <typename T, typename Allocator>
template <IteratorType type>
BST<T, Allocator>::const_iterator<type>::const_iterator(Node<T>* ptr)
    : ptr_(ptr) {}

template <typename T, typename Allocator>
template <IteratorType type>
BST<T, Allocator>::const_iterator<type>::const_iterator(
    const const_iterator<type>& other) {
  this->ptr_ = other.ptr_;
}

template <typename T, typename Allocator>
template <IteratorType type>
typename BST<T, Allocator>::template const_iterator<type>&
BST<T, Allocator>::const_iterator<type>::operator=(
    const const_iterator<type>& other) {
  this->ptr_ = other.ptr_;

  return *this;
}

template <typename T, typename Allocator>
template <IteratorType type>
typename BST<T, Allocator>::template const_iterator<type>&
BST<T, Allocator>::const_iterator<type>::operator++() {
  if (type == IteratorType::PREORDER) {
    if (ptr_->left != nullptr) {
      ptr_ = ptr_->left;
    } else if (ptr_->right != nullptr) {
      ptr_ = ptr_->right;
    } else {
      while (ptr_->parent != nullptr &&
             (ptr_ == ptr_->parent->right || ptr_->parent->right == nullptr)) {
        ptr_ = ptr_->parent;
      }

      if (ptr_->parent == nullptr) {
        ptr_ = nullptr;
      } else {
        ptr_ = ptr_->parent->right;
      }
    }
  } else if (type == IteratorType::INORDER) {
    if (ptr_->right != nullptr) {
      ptr_ = ptr_->right;
      while (ptr_->left != nullptr) {
        ptr_ = ptr_->left;
      }
    } else {
      while (ptr_->parent != nullptr && ptr_ == ptr_->parent->right) {
        ptr_ = ptr_->parent;
      }
      ptr_ = ptr_->parent;
    }
  } else if (type == IteratorType::POSTORDER) {
    if (ptr_ == nullptr) return *this;

    if (ptr_->parent == nullptr) {
      ptr_ = nullptr;
      return *this;
    }

    if (ptr_ == ptr_->parent->left && ptr_->parent->right != nullptr) {
      ptr_ = ptr_->parent->right;

      while (ptr_->left != nullptr || ptr_->right != nullptr) {
        if (ptr_->left != nullptr) {
          ptr_ = ptr_->left;
        } else {
          ptr_ = ptr_->right;
        }
      }
    } else {
      ptr_ = ptr_->parent;
    }
  }

  return *this;
}

template <typename T, typename Allocator>
template <IteratorType type>
typename BST<T, Allocator>::template const_iterator<type>
BST<T, Allocator>::const_iterator<type>::operator++(int) {
  const_iterator<type> temp = *this;
  ++(*this);

  return temp;
}

template <typename T, typename Allocator>
template <IteratorType type>
const typename BST<T, Allocator>::value_type&
BST<T, Allocator>::const_iterator<type>::operator*() {
  if (this->ptr_ != nullptr) {
  return this->ptr_->value;
  } else {
    throw std::invalid_argument("Dereferencing null pointer.");
  }
}

template <typename T, typename Allocator>
template <IteratorType type>
bool BST<T, Allocator>::const_iterator<type>::operator!=(
    const typename BST<T, Allocator>::const_iterator<type>& other) const {
  return this->ptr_ != other.ptr_;
}

template <typename T, typename Allocator>
template <IteratorType type>
bool BST<T, Allocator>::const_iterator<type>::operator==(
    const typename BST<T, Allocator>::const_iterator<type>& other) const {
  return this->ptr_ == other.ptr_;
}

template <typename T, typename Allocator>
template <IteratorType type>
typename BST<T, Allocator>::template const_iterator<type>&
BST<T, Allocator>::const_iterator<type>::operator--() {
  if (type == IteratorType::INORDER) {
    if (ptr_->left != nullptr) {
      ptr_ = ptr_->left;
      while (ptr_->right != nullptr) {
        ptr_ = ptr_->right;
      }
    } else {
      while (ptr_->parent != nullptr && ptr_ == ptr_->parent->left) {
        ptr_ = ptr_->parent;
      }
      ptr_ = ptr_->parent;
    }
  } else if (type == IteratorType::PREORDER) {
    if (ptr_ == nullptr) return *this;

    if (ptr_->parent == nullptr) {
      ptr_ = nullptr;
      return *this;
    }

    if (ptr_ == ptr_->parent->right && ptr_->parent->left != nullptr) {
      ptr_ = ptr_->parent->left;

      while (ptr_->right != nullptr || ptr_->left != nullptr) {
        if (ptr_->right != nullptr) {
          ptr_ = ptr_->right;
        } else {
          ptr_ = ptr_->left;
        }
      }
    } else {
      ptr_ = ptr_->parent;
    }

  } else if (type == IteratorType::POSTORDER) {
    if (ptr_->right != nullptr) {
      ptr_ = ptr_->right;
    } else if (ptr_->left != nullptr) {
      ptr_ = ptr_->left;
    } else {
      while (ptr_->parent != nullptr &&
             (ptr_ == ptr_->parent->left || ptr_->parent->left == nullptr)) {
        ptr_ = ptr_->parent;
      }

      if (ptr_->parent == nullptr) {
        ptr_ = nullptr;
      } else {
        ptr_ = ptr_->parent->left;
      }
    }
  }

  return *this;
}

template <typename T, typename Allocator>
template <IteratorType type>
typename BST<T, Allocator>::template const_iterator<type>
BST<T, Allocator>::const_iterator<type>::operator--(int) {
  const_iterator<type> temp = const_iterator<type>(this->ptr_);
  --(*this);

  return temp;
}

template <typename T, typename Allocator>
template <IteratorType type>
typename BST<T, Allocator>::template const_iterator<type>
BST<T, Allocator>::cbegin() {
  if (type == IteratorType::INORDER) {
    if (this->tree_.GetRoot() == nullptr) return const_iterator<type>(nullptr);
    Node<T>* cur = this->tree_.GetRoot();

    while (cur->left != nullptr) {
      cur = cur->left;
    }

    return const_iterator<type>(cur);
  } else if (type == IteratorType::PREORDER) {
    return const_iterator<type>(this->tree_.GetRoot());
  } else if (type == IteratorType::POSTORDER) {
    if (this->tree_.GetRoot() == nullptr) return const_iterator<type>(nullptr);

    Node<T>* cur = this->tree_.GetRoot();
    while (cur->left != nullptr || cur->right != nullptr) {
      if (cur->left != nullptr) {
        cur = cur->left;
      } else {
        cur = cur->right;
      }
    }

    return const_iterator<type>(cur);
  }
}
template <typename T, typename Allocator>
template <IteratorType type>
typename BST<T, Allocator>::template const_iterator<type>
BST<T, Allocator>::cend() {
  return const_iterator<type>(nullptr);
}

template <typename T, typename Allocator>
template <typename It>
BST<T, Allocator>::template const_reverse_iterator<It>::const_reverse_iterator(
    Node<value_type>* ptr) {
  this->current = It(ptr);
}

template <typename T, typename Allocator>
template <typename It>
BST<T, Allocator>::template const_reverse_iterator<It>::const_reverse_iterator(
    const const_reverse_iterator& other) {
  this->current = other.current;
}

template <typename T, typename Allocator>
template <typename It>
typename BST<T, Allocator>::template const_reverse_iterator<It>&
BST<T, Allocator>::const_reverse_iterator<It>::operator++() {
  --current;

  return *this;
}

template <typename T, typename Allocator>
template <typename It>
typename BST<T, Allocator>::template const_reverse_iterator<It>
BST<T, Allocator>::const_reverse_iterator<It>::operator++(int) {
  const_reverse_iterator<It> temp = *this;
  ++(*this);

  return temp;
}

template <typename T, typename Allocator>
template <typename It>
typename BST<T, Allocator>::template const_reverse_iterator<It>&
BST<T, Allocator>::const_reverse_iterator<It>::operator--() {
  ++current;

  return *this;
}

template <typename T, typename Allocator>
template <typename It>
typename BST<T, Allocator>::template const_reverse_iterator<It>
BST<T, Allocator>::const_reverse_iterator<It>::operator--(int) {
  const_reverse_iterator<It> temp = *this;
  --(*this);

  return temp;
}

template <typename T, typename Allocator>
template <typename It>
const typename BST<T, Allocator>::value_type&
BST<T, Allocator>::const_reverse_iterator<It>::operator*() {
  return *(current);
}

template <typename T, typename Allocator>
template <typename It>
typename BST<T, Allocator>::template const_reverse_iterator<It>&
BST<T, Allocator>::const_reverse_iterator<It>::operator=(
    const BST<T, Allocator>::const_reverse_iterator<It>& other) {
  this->current = other.current;

  return *this;
}

template <typename T, typename Allocator>
template <typename It>
bool BST<T, Allocator>::const_reverse_iterator<It>::operator==(
    const typename BST<T, Allocator>::const_reverse_iterator<It>& other) const {
  return this->current == other.current;
}

template <typename T, typename Allocator>
template <typename It>
bool BST<T, Allocator>::const_reverse_iterator<It>::operator!=(
    const typename BST<T, Allocator>::const_reverse_iterator<It>& other) const {
  return this->current != other.current;
}

template <typename T, typename Allocator>
template <IteratorType type, typename... Args>
std::pair<typename BST<T, Allocator>::template const_iterator<type>, bool>
BST<T, Allocator>::emplace(Args&&... args) {
  T arr[] = {std::forward<Args>(args)...};
  size_t arr_size = sizeof(arr) / sizeof(arr[0]);

  for (int i = 0; i < arr_size; ++i) {
    Node<T>* find_node = this->tree_.Find(arr[i]);

    if (find_node != nullptr) {
      return std::make_pair(const_iterator<type>(find_node), false);
    }

    this->tree_.Insert(arr[i]);
    Node<T>* inserted = this->tree_.Find(arr[i]);
    if (i == arr_size - 1) {
      return std::make_pair(const_iterator<type>(inserted), true);
    }
  }
}

template <typename T, typename Allocator>
void BST<T, Allocator>::UpdateParentPointers(Node<value_type>* node,
                                             Node<value_type>* parent) {
  if (node != nullptr) {
    node->parent = parent;
    UpdateParentPointers(node->left, node);
    UpdateParentPointers(node->right, node);
  }
}

template <typename T, typename Allocator>
template <IteratorType type>
typename BST<T, Allocator>::template const_iterator<type>
BST<T, Allocator>::erase(const_iterator<type> pos) {
  if (pos == this->cend<type>()) return cend<type>();

  const_iterator<type> following = pos;
  value_type temp = *pos;
  if (type != IteratorType::INORDER) {
    ++following;
    this->tree_.Remove(temp);
  } else {
    this->tree_.Remove(temp);
    following = const_iterator<type>(this->tree_.Next(temp));
  }

  return following;
}

template <typename T, typename Allocator>
template <IteratorType type>
typename BST<T, Allocator>::template const_iterator<type>
BST<T, Allocator>::erase(const_iterator<type> first,
                         const_iterator<type> last) {
  const_iterator<type> following;
  value_type temp;
  int length = 0;

  for (auto it = first; it != last; ++it) {
    ++length;
  }

  value_type* temp_arr = new value_type[length];
  int i = 0;
  for (auto it = first; it != last; ++it) {
    temp_arr[i] = *it;
    ++i;
  }

  for (int i = 0; i < length; ++i) {
    this->tree_.Remove(temp_arr[i]);
    if (i == length - 1) {
      following = const_iterator<type>(this->tree_.Find(temp_arr[i]));
    }
  }

  if (type != IteratorType::INORDER) {
    ++following;
  } else {
    following = const_iterator<type>(this->tree_.Next(temp));
  }
  delete[] temp_arr;

  return following;
}

template <typename T, typename Allocator>
typename BST<T, Allocator>::size_type BST<T, Allocator>::erase(
    const value_type& key) {
  if (!this->tree_.Find(key)) return 0;

  this->tree_.Remove(key);

  return 1;
}

template <typename T, typename Allocator>
typename BST<T, Allocator>::size_type BST<T, Allocator>::count(
    const value_type& key) {
  if (this->tree_.Find(key)) return 1;

  return 0;
}

template <typename T, typename Allocator>
template <typename K>
typename BST<T, Allocator>::size_type BST<T, Allocator>::count(
    const K& key) const {
  if (this->tree_.Find(key)) return 1;

  return 0;
}

template <typename T, typename Allocator>
template <IteratorType type>
typename BST<T, Allocator>::template const_iterator<type>
BST<T, Allocator>::find(const value_type& key) {
  Node<value_type>* node = this->tree_.Find(key);

  return const_iterator<type>(node);
}

template <typename T, typename Allocator>
template <IteratorType type, typename K>
typename BST<T, Allocator>::template const_iterator<type>
BST<T, Allocator>::find(const K& key) {
  Node<value_type>* node = this->tree_.Find(key);

  return const_iterator<type>(node);
}

template <typename T, typename Allocator>
bool BST<T, Allocator>::contains(const value_type& key) {
  return (this->tree_.Find(key) == nullptr) ? false : true;
}

template <typename T, typename Allocator>
template <typename K>
bool BST<T, Allocator>::contains(const K& key) const {
  return (this->tree_.Find(key) == nullptr) ? false : true;
}

template <typename T, typename Allocator>
template <IteratorType type>
typename BST<T, Allocator>::template const_iterator<type>
BST<T, Allocator>::lower_bound(const value_type& key) {
  Node<value_type>* temp = this->tree_.Find(key);

  if (temp != nullptr) return const_iterator<type>(temp);

  return const_iterator<type>(this->tree_.Next(key));
}

template <typename T, typename Allocator>
template <IteratorType type, typename K>
typename BST<T, Allocator>::template const_iterator<type>
BST<T, Allocator>::lower_bound(const K& key) {
  Node<value_type>* temp = this->tree_.Find(key);

  if (temp != nullptr) return const_iterator<type>(temp);

  return const_iterator<type>(this->tree_.Next(key));
}

template <typename T, typename Allocator>
template <IteratorType type>
typename BST<T, Allocator>::template const_iterator<type>
BST<T, Allocator>::upper_bound(const value_type& key) {
  return const_iterator<type>(this->tree_.Next(key));
}

template <typename T, typename Allocator>
template <IteratorType type, typename K>
typename BST<T, Allocator>::template const_iterator<type>
BST<T, Allocator>::upper_bound(const K& key) {
  return const_iterator<type>(this->tree_.Next(key));
}

template <typename T, typename Allocator>
void BST<T, Allocator>::clear() {
  tree_.Deallocate();
}

template <typename T, typename Allocator>
template <IteratorType type>
std::pair<typename BST<T, Allocator>::template const_iterator<type>, bool>
BST<T, Allocator>::insert(const value_type& value) {
  Node<value_type>* temp = this->tree_.Find(value);
  if (temp != nullptr) return std::make_pair(const_iterator<type>(temp), false);

  this->tree_.Insert(value);

  return std::make_pair(const_iterator<type>(this->tree_.Find(value)), true);
}

template <typename T, typename Allocator>
template <class InputIt>
void BST<T, Allocator>::insert(InputIt first, InputIt last) {
  for (auto it = first; it != last; ++it) {
    this->tree_.Insert(*it);
  }
}

template <typename T, typename Allocator>
void BST<T, Allocator>::insert(std::initializer_list<value_type> ilist) {
  for (auto it = ilist.begin(); it != ilist.end(); ++it) {
    this->tree_.Insert(*it);
  }
}

template <typename T, typename Allocator>
Node<T>* BST<T, Allocator>::extract(const value_type& key) {
  Node<T>* temp = allocator_.allocate(1);
  temp->value = tree_.Find(key)->value;
  this->tree_.Remove(key);

  return temp;
}

template <typename T, typename Allocator>
void BST<T, Allocator>::merge(BST<T, Allocator>& source) {
  while (!source.empty()) {
    this->insert<IteratorType::INORDER>(
        source.extract(source.tree_.GetRoot()->value)->value);
  }
}

template <typename T, typename Allocator>
template <IteratorType type>
typename BST<T, Allocator>::template const_reverse_iterator<
    typename BST<T, Allocator>::template const_iterator<type>>
BST<T, Allocator>::rbegin() {
  if (type == IteratorType::INORDER) {
    if (this->tree_.GetRoot() == nullptr)
      return const_reverse_iterator<const_iterator<type>>(nullptr);
    Node<T>* cur = this->tree_.GetRoot();

    while (cur->right != nullptr) {
      cur = cur->right;
    }

    return const_reverse_iterator<const_iterator<type>>(cur);
  } else if (type == IteratorType::PREORDER) {
    Node<T>* cur = this->tree_.GetRoot();
    while (cur->left != nullptr || cur->right != nullptr) {
      cur = cur->right;
    }

    return const_reverse_iterator<const_iterator<type>>(cur);
  } else if (type == IteratorType::POSTORDER) {
    return const_reverse_iterator<const_iterator<type>>(this->tree_.GetRoot());
  }
}

template <typename T, typename Allocator>
template <IteratorType type>
typename BST<T, Allocator>::template const_reverse_iterator<
    typename BST<T, Allocator>::template const_iterator<type>>
BST<T, Allocator>::crbegin() {
  return rbegin<type>();
}

template <typename T, typename Allocator>
template <IteratorType type>
typename BST<T, Allocator>::template const_reverse_iterator<
    typename BST<T, Allocator>::template const_iterator<type>>
BST<T, Allocator>::crend() {
  return rend<type>();
}

template <typename T, typename Allocator>
template <IteratorType type>
typename BST<T, Allocator>::template const_reverse_iterator<
    typename BST<T, Allocator>::template const_iterator<type>>
BST<T, Allocator>::rend() {
  if (type == IteratorType::INORDER) {
    if (this->tree_.GetRoot() == nullptr)
      return const_reverse_iterator<const_iterator<type>>(nullptr);
    Node<T>* cur = this->tree_.GetRoot();

    while (cur->right != nullptr) {
      cur = cur->right;
    }

    return const_reverse_iterator<const_iterator<type>>(cur);
  } else if (type == IteratorType::PREORDER) {
    return const_reverse_iterator<const_iterator<type>>(
        this->tree_.GetRoot()->parent);
  } else if (type == IteratorType::POSTORDER) {
    return const_reverse_iterator<const_iterator<type>>(nullptr);
  }
}

template <typename T, typename Allocator>
bool BST<T, Allocator>::operator==(BST& second) {
if (this->size() != second.size()) return false;
  bool res = true;
  value_type* arr1 = new value_type[this->size()];
  value_type* arr2 = new value_type[this->size()];
  int i = 0;

  for (auto it = this->begin<IteratorType::PREORDER>(); it != this->end<IteratorType::PREORDER>(); ++it) {
    arr1[i] = *it;
    ++i;
  }
  i = 0;
  for (auto it = second.begin<IteratorType::PREORDER>(); it != second.end<IteratorType::PREORDER>(); ++it) {
    arr2[i] = *it;
    ++i;
  }
  for (int i = 0; i < this->size(); ++i) {
    if (arr1[i] != arr2[i]) res = false;
  }

  return res;
}

template <typename T, typename Allocator>
bool BST<T, Allocator>::operator!=(const BST& second) {
  return !(*this == second);
}
