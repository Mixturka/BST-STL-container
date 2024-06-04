# BST STL Container

## Overview

This project implements STL-compatible container for a Binary Search Tree, providing tree traversal method using tag dispatch idiom through iterators.

## Features

- **Associative Container**
- **Reverse Iterator**
- **Allocator Awareness**
- **Bidirectional Iterator**
- **Traversal via Iterators**

## Testing

The project includes a test suite using the Google Test framework to ensure tree is working correctly.

## Usage

To use the containers, include the appropriate header files and instantiate the containers with the desired template parameters. Use the iterators provided by each container to traverse the tree in the specified order.

## Example

```cpp
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
```
