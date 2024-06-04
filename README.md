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

## Constraints


- **No Standard Containers**: The use of standard containers is prohibited.

## Implementation Notes


- **Tag Dispatch Idiom**: Consider using this idiom to avoid implementing three separate containers and to efficiently manage the different traversal types.

## Usage

To use the containers, include the appropriate header files and instantiate the containers with the desired template parameters. Use the iterators provided by each container to traverse the tree in the specified order.

## Example

```cpp
#include "BinarySearchTree.h"

int main() {
    // Example usage of the Binary Search Tree containers
    // Assuming InOrderBinarySearchTree, PreOrderBinarySearchTree, and PostOrderBinarySearchTree are implemented
    InOrderBinarySearchTree<int> inOrderTree;
    PreOrderBinarySearchTree<int> preOrderTree;
    PostOrderBinarySearchTree<int> postOrderTree;

    // Insert elements into the trees
    // ...

    // Traverse the trees using iterators
    for (auto it = inOrderTree.begin(); it != inOrderTree.end(); ++it) {
        // Process element pointed by it
    }
    // Similarly for preOrderTree and postOrderTree

    return 0;
}
