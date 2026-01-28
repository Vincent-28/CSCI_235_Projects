#include "BST.hpp"

/**
 * @brief Parameterized node constructor
 * @param data The value to store in the node, where T could be integer, string, or a templated object.
 * @param left A shared pointer to the left child node (default is nullptr).
 * @param right A shared pointer to the right child node (default is nullptr).
 */
template <class T>
Node<T>::Node(T data, std::shared_ptr<Node<T>> left, std::shared_ptr<Node<T>> right)
    : data_ { data }
    , left_ { left }
    , right_ { right }
{
}

/**
 * @brief Constructs an empty Binary Search Tree.
 */
template <class T>
BST<T>::BST()
    : size_ { 0 }
    , root_ { nullptr }
{
}

/**
 * @brief Recursive helper function to insert a value into the tree.
 * @param to_insert The value to insert, where T could be integer, string, or a templated object.
 * @param root The root of the current subtree.
 * @return std::shared_ptr<Node<T>> The updated root of the subtree.
 */
template <class T>
std::shared_ptr<Node<T>> BST<T>::insertHelper(const T& to_insert, std::shared_ptr<Node<T>> root)
{
    // If the tree/subtree is empty, create a new node
    if (!root) {
        size_++;
        return std::make_shared<Node<T>>(to_insert);
    }

    // Otherwise, recur down the tree
    if (to_insert < root->data_) {
        root->left_ = insertHelper(to_insert, root->left_);
    } else if (to_insert > root->data_) {
        root->right_ = insertHelper(to_insert, root->right_);
    }

    // If data is equal, we do nothing (no duplicates).
    return root;
}

/**
 * @brief Recursive helper function to remove a value from the tree.
 * @param data The value to remove, where T could be integer, string, or a templated object.
 * @param root The root of the current subtree.
 * @param A boolean specifying whether a node was removed or not.
 * @return std::shared_ptr<Node<T>> The updated root of the subtree.
 */
template <class T>
std::shared_ptr<Node<T>> BST<T>::eraseHelper(const T& data, std::shared_ptr<Node<T>> root, bool& did_remove)
{
    if (root == nullptr)
        return root;

    if (data < root->data_) {
        root->left_ = eraseHelper(data, root->left_, did_remove);
    } else if (data > root->data_) {
        root->right_ = eraseHelper(data, root->right_, did_remove);
    } else {
        // Node found: Set the flag to true
        did_remove = true;

        // Case 1: Node with only one child or no child
        if (root->left_ == nullptr) {
            return root->right_;
        } else if (root->right_ == nullptr) {
            return root->left_;
        }

        // Case 2: Node with two children
        std::shared_ptr<Node<T>> temp = root->right_;
        while (temp->left_ != nullptr) {
            temp = temp->left_;
        }

        root->data_ = temp->data_;

        // Pass a dummy status since know the successor exists and don't need the status back
        bool dummy_status = false;
        root->right_ = eraseHelper(temp->data_, root->right_, dummy_status);
    }
    return root;
}

/**
 * @brief Retrieves the root node of the BST.
 * @return std::shared_ptr<Node<T>> Pointer to the root node.
 */
template <class T>
std::shared_ptr<Node<T>> BST<T>::getRoot() const
{
    return root_;
}

/**
 * @brief Returns the number of nodes in the BST.
 * @return size_t The total count of nodes.
 */
template <class T>
size_t BST<T>::size() const
{
    return size_;
}

/**
 * @brief Inserts a new element into the BST.
 * @param data The value to insert, where T could be integer, string, or a templated object.
 */
template <class T>
void BST<T>::insert(const T& data)
{
    root_ = insertHelper(data, root_);
}

/**
 * @brief Removes an element from the BST.
 * @param data The value to remove, where T could be integer, string, or a templated object.
 * @return true If the element was successfully removed.
 * @return false If the element was not found in the tree.
 */
template <class T>
bool BST<T>::erase(const T& data)
{
    bool removed = false;
    root_ = eraseHelper(data, root_, removed);

    if (removed) {
        size_--;
    }

    return removed;
}

/**
 * @brief Destroys the BST and releases all memory.
 */
template <class T>
BST<T>::~BST()
{
    // shared_ptr handles memory automatically.
    // Explicitly resetting root will trigger the chain reaction of destruction.
    root_.reset();
}

template <class T>
bool BST<T>::contains(const T& data) const
{
    std::shared_ptr<Node<T>> current = root_; //current points to the node we are inspecting
    while (current != nullptr) { //if current is nullptr, we've fallen off the tree and did not find data
        if (data == current->data_) { //compare searched value with current node's data
            return true; //return true because the value exists in the BST
        }
        else if (data < current->data_) { //check if we must go left
            current = current->left_; //move current to left child
        }
        else { //here data > current->data_
            current = current->right_; //move current to right child
        }
    }

    return false; // when the value is not in the tree
}