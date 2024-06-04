# BST STL Container

## Overview

This project implements STL-compatible container for a Binary Search Tree, providing tree traversal method using tag dispatch idiom through iterators.

## Features


- **Template-based Containers**: Parameterized by the type of stored objects, comparison operator, and allocator.
- **Associative Containers**: Elements are referenced by their key and sorted based on the comparison operator.

- **Reverse Iterators**: Support for iterating through the container in reverse order.
- **Allocator Awareness**: Containers support custom allocators for memory management.

- **Bidirectional Iterators**: Iterators can move in both directions, forward and backward.
- **Traversal via Iterators**: The `++` operator moves the iterator to the next element according to the traversal rule.

## Testing

The project includes a comprehensive test suite using the Google Test framework to ensure that all requirements are met. The tests are an integral part of the assignment, and their coverage will affect the final grade.

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
