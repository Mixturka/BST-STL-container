#include "../lib/BST.hpp"

int main() {
  BST<int> bst;
  auto tree = bst.emplace<IteratorType::INORDER>(5, 4, 1, 7, 2, 8, 6);
  BST<int> bst2;
  bst2.emplace<IteratorType::INORDER>(1, 2, 3);
  bst.merge(bst2);
  for (auto it = bst.begin<IteratorType::INORDER>();
       it != bst.end<IteratorType::INORDER>(); ++it) {
    std::cout << *it << ' ';
  }
  
  return 0;
}
