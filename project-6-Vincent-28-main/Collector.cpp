#include "Collector.hpp" 

template <class T>
void DFS::internal::collectHelper(const DFS::Order& traversal_order, std::vector<T>& collected, std::shared_ptr<Node<T>> root)     
{
    if (root == nullptr) { // Task 2: if the subtree is empty, stop
        return;            // Task 2: return to caller without modifying vector
    }

    if (traversal_order == DFS::PRE_ORDER) {  //check if we are doing PRE_ORDER
        collected.push_back(root->data_); //"process" parent by adding its data to vector
    }

    DFS::internal::collectHelper<T>(traversal_order, collected, root->left_);    

    if (traversal_order == DFS::IN_ORDER) { //check if we are doing IN_ORDER
        collected.push_back(root->data_); //add parent after left subtree, before right subtree
    }

    DFS::internal::collectHelper<T>(traversal_order, collected, root->right_);   

    if (traversal_order == DFS::POST_ORDER) { //check if we are doing POST_ORDER
        collected.push_back(root->data_); //add parent after both left and right subtrees
    }
}

template <class T>
std::vector<T> DFS::collect(const BST<T>& tree, const DFS::Order& traversal_order) 
{
    std::vector<T> collected; //create empty vector to store traversal result

    DFS::internal::collectHelper<T>(traversal_order, collected, tree.getRoot()); 

    return collected; //return traversal result to caller
}

template <class T>
std::vector<T> BFS::collect(const BST<T>& tree) //function definition for BFS::collect
{
    std::vector<T> collected; //vector to store BFS traversal result

    std::shared_ptr<Node<T>> root = tree.getRoot(); //starting node for BFS

    if (root == nullptr) { //no nodes to traverse
        return collected; //return empty result
    }

    std::queue<std::shared_ptr<Node<T>>> to_visit; //queue for nodes to process

    to_visit.push(root); //first node to be processed is the root

    while (!to_visit.empty()) { //loop while there are nodes waiting in queue
        std::shared_ptr<Node<T>> current = to_visit.front(); //node we are currently processing
        to_visit.pop(); //remove it from the queue

        collected.push_back(current->data_); //store this node's value in level-order

        if (current->left_ != nullptr) { //check if current has a left child
            to_visit.push(current->left_); //left child will be processed later
        }

        if (current->right_ != nullptr) { //check if current has a right child
            to_visit.push(current->right_); //right child will be processed later
        }
    }

    return collected; //return BFS traversal result
}