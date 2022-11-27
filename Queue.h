#include "SinglyLinkedList.h"

template <class Item> class queue {
  public:
    // Default Constructor
    queue();

    // Copy Constructor
    queue(const queue<Item> &source);

    // Destructor
    ~queue() { list_clear(front_ptr); }

    void push(const Item &entry);

    void pop();

    void operator=(const queue<Item> &source);

    bool empty() const { return (count == 0); }

    Item front() const;

    size_t size() const { return count; }

    Item *to_array() const;

  private:
    node<Item> *front_ptr; // point to the node that has the first item.
    node<Item> *rear_ptr;  // point to the node that has the last item.
    size_t count;          // the number of items.
};

template <class Item> queue<Item>::queue() {
    // empty queue
    count = 0;
    front_ptr = NULL;
    rear_ptr = NULL;
}

template <class Item> queue<Item>::queue(const queue<Item> &source) {
    count = source.count;
    list_copy(source.front_ptr, front_ptr, rear_ptr); // deep copy
}

template <class Item> void queue<Item>::push(const Item &entry) {
    if (empty()) { // The list is empty. So call list_head_insert().
        list_head_insert(front_ptr, entry);
        rear_ptr = front_ptr;
    } else { // The list is not empty. So call list_insert().
        list_insert(rear_ptr, entry);
        rear_ptr = rear_ptr->get_link();
    }
    count++;
}

template <class Item> void queue<Item>::pop() {
    assert(!empty()); // Precondition.
    list_head_remove(front_ptr);
    count--;
    if (empty())
        rear_ptr = NULL;
}

template <class Item> void queue<Item>::operator=(const queue<Item> &source) {
    if (this == &source) // self-assignment.
        return;
    list_clear(front_ptr); // Free the memory that original list used.
    list_copy(source.front_ptr, front_ptr, rear_ptr); // deep copy.
    count = source.count;
}

template <class Item> Item queue<Item>::front() const {
    assert(!empty()); // Precondition.
    return front_ptr->get_data();
}

template <class Item> Item *queue<Item>::to_array() const {
    return list_to_array(front_ptr);
}
