#include "LinkedList.hpp"

/**
 * @brief Constructs a Node with a given value.
 */
template <class T>
Node<T>::Node(const T& val, Node* next)
    : value_(val)
    , next_(next)
{
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& rhs)
    : size_ { 0 }
{
    // Perform the deep copy from the other list
    for (Node<T>* current = rhs.head_; current != nullptr; current = current->next_) {
        push_back(current->value_);
    }
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
{
    // 1. Check for self-assignment
    if (this == &other) {
        return *this;
    }

    // 2. Clear the current list's contents to prevent memory leaks
    clear();

    // 3. Perform the deep copy from the other list
    for (Node<T>* current = other.head_; current != nullptr; current = current->next_) {
        push_back(current->value_);
    }

    // 4. Return a reference to the current object to allow for chained assignments
    return *this;
}

/**
 * @brief Stringifies the underlying LinkedList
 * @return A string of the form "{'<node_content_1>', ...}" representing the LinkedList's contents
 */
template <class T>
std::string LinkedList<T>::toString() const
{
    std::stringstream ss;
    ss << "size: " << size() << " - ";
    ss << "{ ";

    Node<T>* p = head_;
    for (size_t i = 0; i < size(); i++) {
        ss << p->value_;

        if (i + 1 != size()) {
            ss << ", ";
        }
        p = p->next_;
    }

    ss << " }";
    return ss.str();
}

// YOUR CODE BELOW. DO NOT MODIFY ABOVE.

//Returns the numnber of elements in the list
template <class T>
size_t LinkedList<T>::size() const{ 
    return size_; //returns the number of elements (size_t)
}

//Checks if the list is empty (ie. contains no elements).
template <class T>
bool LinkedList<T>::empty() const{
    if (size_ == 0) { //Checks if the list is empty (ie. contains no elements).
        return true; //returns true if empty
    }
    else {
        return false; //returns false otherwise
    }
}

template <class T>
Node<T>* LinkedList<T>::head() const{ //Access the node pointing to the head of the linked list
    if (head_ == nullptr) {
        return nullptr; //return nullptr if the list is empty (there is not head ndoe)
    }
    else {
        return head_; //return the head node
    }
}

template <class T>
T LinkedList<T>::front() const{ //Access the first element.
    if (empty()) {
        throw std::runtime_error("empty list"); //std::runtime_error if the list is empty.
    }
    else {
        return head_->value_; //The first element's value (of type T, NOT the node).
    }
}

template <class T>
T LinkedList<T>::back() const{ //Access the last element.
    if (empty()) {
        throw std::runtime_error("empty list"); //std::runtime_error if the list is empty.
    }
    Node<T>* current = head_;
    while (current->next_ != nullptr) { //keep setting current to next_ until it is pointing to a nullptr meaning current would be the last element
        current = current->next_;
    } 
    return current->value_; //The last element's value (of type T, , NOT the node).
}

template <class T>
T LinkedList<T>::at(size_t index) const{ //Access an element at a specific index.
    if (index >= size_) { //the index would be out of range if it is greater than the size
        throw std::out_of_range("index out of range"); //throws std::out_of_range if the index is invalid (eg. too large).
    }
    Node<T>* current = head_;
    for (size_t i = 0; i < index; i++) { //loop through the next_ pointers index amount of times
        current = current->next_;
    }
    return current->value_; //return the element's vvalue at the given index (of type T)
}

template <class T>
void LinkedList<T>::push_back(const T& value) { //adds an element to the end of the list
    Node<T>* newNode = new Node<T>(value, nullptr); //new node for the end of the list
    if (empty()) { 
        head_ = newNode; //if the list is empty, the head_ will become the newNode
    }
    else {
        Node<T>* current = head_;
        while (current->next_ != nullptr) {
            current = current->next_;
        } //this while loop sets current to the last node in the list (done in the back function)
        current->next_ = newNode; //we link the last (current) to the newNode
    }
    size_++; //maintain size
}

template<class T>
void LinkedList<T>::insert(size_t index, const T& value) {
    if (index > size_) { //check if index is greater then the size (out of range)
        throw std::out_of_range("index is greater than the size");
    }

    if (index == 0) { //check if the index is at 0 (the head) 
        Node<T>* newNode = new Node<T>(value, head_); //create a newNode and set head as that newNode
        head_ = newNode;
        if (size_ == 0) {
            tail_ = newNode;
        }
        size_++; //maintain size
        return;
    }

    if (index == size_) { //check if the index is equal to the head (we would need to add to the end)
        push_back(value); //reuse the push_back function we made to add to the end of the list
        return;
    }

    Node<T>* lastNode = head_; //we want to insert in the middle of the list
    for (size_t i = 0; i +1 < index; i++) { //we get the index and set that to lastNode. 
        lastNode = lastNode->next_;
    }
    //right now lastNode is the index we want to insert at
    Node<T>* newNode = new Node<T>(value, lastNode->next_); 
    lastNode->next_ = newNode; //create new node and its set to the lastNode's index
    size_++; //maintain size
}

template <class T>
void LinkedList<T>::erase(size_t index) { //Erases an element at a specific index.
    if (index >= size_) {
        throw std::out_of_range("index out of range"); //throws std::out_of_range if index is greater than or equal to the size
    }

    if (index == 0) { //check if the index is 0 (the head)
        Node<T>* firstHead = head_; //create a pointer to head_ so we dont lose it when we move head_
        head_ = head_->next_; //move head_ to the next pointer (instead of pointing to A, head_ now points to B since we are removing at index 0)
        if (size_ == 1) {
            tail_ = nullptr;
        }
        firstHead->next_ = nullptr; //we get the original head_ we had and that will now point to a nullptr (basically cutting its link to the rest of the list)
        delete firstHead; //free the memory of that original first head (erasing it)
        size_--; //maintain the size (we subtract 1)
        return;
    }

    //now we will remove from the middle of the list
    Node<T>* lastNode = head_;
    for (size_t i = 0; i +1 < index; i++) { //we doing i+1 since we already dealt with the case in which index = 0 above^
        lastNode = lastNode->next_; //lastNode is now pointing to the index we want to erase
    }
    Node<T>* previous = lastNode->next_; //we set previous to lastNode which is pointing to the index we want to remove
    lastNode->next_ = previous->next_; //move the lastNode to be pointing to the next element and bypass previous (the element we want to delete) so we set lastNode to point to the node previous is pointing at
    if (previous == tail_) {
        tail_ = lastNode;
    }
    previous->next_ = nullptr; //we now make previous point to a nullptr
    delete previous; //we delete previous to free the memory
    size_--; //maintain size
}

template <class T>
void LinkedList<T>::clear() {
    Node<T>* current = head_; //set a pointer current to what head_ is pointing to 
    while (current != nullptr) {
        Node<T>* nextNode = current->next_; //nextNode will remember the nextNode before we delete the current one we are at
        current->next_ = nullptr; //get the current node and set it to nullptr to unlink it from the list
        delete current; //delete the current node
        current = nextNode; //set current now to the nextNode which was pointing to the one after the one we deleted
    }
    head_ = nullptr; //make head_ point to a nullptr
    size_ = 0; //the size is reset and set to 0 since we just cleared the list
}

template <class T>
LinkedList<T>::~LinkedList() { //Destructor: cleans up all nodes to prevent memory leaks.
    clear();
}




