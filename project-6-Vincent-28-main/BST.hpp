#pragma once
#include <iostream>
#include <memory>

template <class T>
struct Node {
    T data_;
    std::shared_ptr<Node<T>> left_;
    std::shared_ptr<Node<T>> right_;

    /**
     * @brief Parameterized node constructor
     * @param data The value to store in the node, where T could be integer, string, or a templated object.
     * @param left A shared pointer to the left child node (default is nullptr).
     * @param right A shared pointer to the right child node (default is nullptr).
     */
    Node(T data, std::shared_ptr<Node<T>> left = nullptr, std::shared_ptr<Node<T>> right = nullptr);
};

template <class T>
class BST {
private:
    size_t size_;
    std::shared_ptr<Node<T>> root_;

    /**
     * @brief Recursive helper function to insert a value into the tree.
     * @param to_insert The value to insert, where T could be integer, string, or a templated object.
     * @param root The root of the current subtree.
     * @return std::shared_ptr<Node<T>> The updated root of the subtree.
     */
    std::shared_ptr<Node<T>> insertHelper(const T& data, std::shared_ptr<Node<T>> root);

    /**
     * @brief Recursive helper function to remove a value from the tree.
     * @param data The value to remove, where T could be integer, string, or a templated object.
     * @param root The root of the current subtree.
     * @param A boolean specifying whether a node was removed or not.
     * @return std::shared_ptr<Node<T>> The updated root of the subtree.
     */
    std::shared_ptr<Node<T>> eraseHelper(const T& data, std::shared_ptr<Node<T>> root, bool& did_remove);

public:
    /**
     * @brief Constructs an empty Binary Search Tree.
     */
    BST();

    /**
     * @brief Retrieves the root node of the BST.
     * @return std::shared_ptr<Node<T>> Pointer to the root node.
     */
    std::shared_ptr<Node<T>> getRoot() const;

    /**
     * @brief Returns the number of nodes in the BST.
     * @return size_t The total count of nodes.
     */
    size_t size() const;

    /**
     * @brief Inserts a new element into the BST.
     * @param data The value to insert, where T could be integer, string, or a templated object.
     */
    void insert(const T& data);

    /**
     * @brief Removes an element from the BST.
     * @param data The value to remove, where T could be integer, string, or a templated object.
     * @return true If the element was successfully removed.
     * @return false If the element was not found in the tree.
     */
    bool erase(const T& data);

/**
 * @brief Checks if a specific value exists in the BST.
 * @param data A const reference of type T, specifying the value to search for.
 * @return true If the data is found in the tree, false otherwise.
 */
    bool contains(const T& data) const;

    /**
     * @brief Destroys the BST and releases all memory.
     */
    ~BST();
};

#include "BST.cpp"