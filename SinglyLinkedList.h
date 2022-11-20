#include <cassert>
#include <cstdlib>

/* This is the template class node. The node can store data whose type is
   Item. This node has a pointer that points to next node. */

template <class Item> class node {
  public:
    // Constructor
    node(const Item &init_data = Item(), node<Item> *init_link = NULL);

    /* member functions */

    // setter
    void set_data(const Item &new_data) { data_filed = new_data; }
    void set_link(node<Item> *new_link) { link_field = new_link; }

    // getter
    Item get_data() const { return data_filed; }
    node<Item> *get_link() { return link_field; }
    const node<Item> *get_link() const { return link_field; }

  private:
    /* member variables */
    Item data_filed;
    node<Item> *link_field; // point to next node
};

// Constructor implementation
template <class Item>
node<Item>::node(const Item &init_data, node<Item> *init_link) {
    data_filed = init_data;
    link_field = init_link;
}

/* This is SinglyLinkedList template function toolkit. The head_ptr is pointer
   of list's head nodee. If list is empty, head_ptr is NULL. */

template <class Item> size_t list_length(const node<Item> *head_ptr);

template <class Item>
node<Item> *list_search(node<Item> *head_ptr, const Item &target);
template <class Item>
const node<Item> *list_search(const node<Item> *head_ptr, const Item &target);

template <class Item>
node<Item> *list_locate(node<Item> *head_ptr, size_t position);
template <class Item>
const node<Item> *list_locate(const node<Item> *head_ptr, size_t position);

template <class Item>
void list_head_insert(node<Item> *&head_ptr, const Item &new_data);

template <class Item>
void list_insert(node<Item> *previous_ptr, const Item &new_data);

template <class Item> void list_head_remove(node<Item> *&head_ptr);

template <class Item> void list_remove(node<Item> *previous_ptr);

template <class Item> void list_clear(node<Item> *&head_ptr);

template <class Item>
void list_copy(const node<Item> *source_ptr, node<Item> *&head_ptr,
               node<Item> *&tail_ptr);

template <class Item> Item *list_to_array(const node<Item> *head_ptr);

/* The singly linked list function template toolkit implementation */

template <class Item> size_t list_length(const node<Item> *head_ptr) {
    size_t answer = 0;
    const node<Item> *cursor;
    for (cursor = head_ptr; cursor != NULL; cursor = cursor->get_link())
        ++answer;
    return answer;
}

template <class Item>
node<Item> *list_search(node<Item> *head_ptr, const Item &target) {
    node<Item> *cursor;
    for (cursor = head_ptr; cursor != NULL; cursor = cursor->get_link())
        if (target == cursor->get_data())
            return cursor;
    return NULL;
}

template <class Item>
const node<Item> *list_search(const node<Item> *head_ptr, const Item &target) {
    const node<Item> *cursor;
    for (cursor = head_ptr; cursor != NULL; cursor = cursor->get_link())
        if (target == cursor->get_data())
            return cursor;
    return NULL;
}

template <class Item>
node<Item> *list_locate(node<Item> *head_ptr, size_t position) {
    assert(0 < position); // Precondition.

    node<Item> *cursor = head_ptr;
    size_t i;
    for (i = 1; (cursor != NULL && i < position); ++i)
        cursor = cursor->get_link();
    return cursor;
}

template <class Item>
const node<Item> *list_locate(const node<Item> *head_ptr, size_t position) {
    assert(0 < position); // Precondition.

    const node<Item> *cursor = head_ptr;
    size_t i;
    for (i = 1; (cursor != NULL && i < position); ++i)
        cursor = cursor->get_link();
    return cursor;
}

template <class Item>
void list_head_insert(node<Item> *&head_ptr, const Item &new_data) {
    head_ptr = new node<Item>(new_data, head_ptr);
}

template <class Item>
void list_insert(node<Item> *previous_ptr, const Item &new_data) {
    assert(previous_ptr != NULL); // Precondition

    previous_ptr->set_link(new node<Item>(new_data, previous_ptr->get_link()));
}

template <class Item> void list_head_remove(node<Item> *&head_ptr) {
    if (head_ptr == NULL) // List is empty.
        return;
    node<Item> *remove_ptr;
    remove_ptr = head_ptr;
    head_ptr = head_ptr->get_link();
    delete remove_ptr;
}

template <class Item> void list_remove(node<Item> *previous_ptr) {
    assert(previous_ptr != NULL); // Precondition.

    node<Item> *remove_ptr;
    remove_ptr = previous_ptr->get_link();
    previous_ptr->set_link(remove_ptr->get_link());
    delete remove_ptr;
}

template <class Item> void list_clear(node<Item> *&head_ptr) {
    while (head_ptr != NULL)
        list_head_remove(head_ptr);
}

template <class Item>
void list_copy(const node<Item> *source_ptr, node<Item> *&head_ptr,
               node<Item> *&tail_ptr) {
    head_ptr = NULL;
    tail_ptr = NULL;
    if (source_ptr == NULL) // Source list is empty.
        return;

    // deep copy the head node.
    list_head_insert(head_ptr, source_ptr->get_data());
    tail_ptr = head_ptr;
    source_ptr = source_ptr->get_link();
    while (source_ptr != NULL) { // deep copy all nodes behind head node.
        list_insert(tail_ptr, source_ptr->get_data());
        tail_ptr = tail_ptr->get_link();
        source_ptr = source_ptr->get_link();
    }
}

template <class Item> Item *list_to_array(const node<Item> *head_ptr) {
    node<Item> *cusor;
    size_t size = list_length(head_ptr);
    Item *arr = new Item[size];
    int i = 0;

    for (cusor = head_ptr; cusor != NULL; cusor = cusor->get_link()) {
        arr[i++] = cusor->get_data();
    }

    return arr;
}
