#pragma once 

#include <vector>   
#include <queue>   
#include <memory>   
#include "BST.hpp"  

namespace DFS { //define a namespace DFS

    enum Order { //enum type to specify traversal order
        IN_ORDER, //left, parent, right
        PRE_ORDER, //parent, left, right
        POST_ORDER //left, right, parent
    };

    namespace internal { //nested namespace for helper functions

        template <class T>
        void collectHelper(const Order& traversal_order, std::vector<T>& collected,std::shared_ptr<Node<T>> root);    
    }

/**
 * @brief Performs a Breadth-First Search (BFS) to
 * collect all elements in the tree level-by-level, left-to-right.
 * @tparam T The type of valued stored within the BST's nodes,
 * and to be stored in the resultant vector.
 *
 * @param tree A const reference to the BST (of type T) to traverse.
 *
 * @return std::vector<T> A vector containing the
 * collected elements, in level-order
 */
    template <class T>
    std::vector<T> collect(const BST<T>& tree, const Order& traversal_order);

}

namespace BFS { 
    template <class T> //template so BFS::collect works with BST<T>
    std::vector<T> collect(const BST<T>& tree); //BFS traversal declaration

} 

#include "Collector.cpp" 