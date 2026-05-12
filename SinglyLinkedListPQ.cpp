#include "SinglyLinkedListPQ.hpp"
#include <stdexcept>

SinglyLinkedListPQ::SinglyLinkedListPQ()
    : head_(nullptr), size_(0), next_id_(0) {}

SinglyLinkedListPQ::~SinglyLinkedListPQ() {
    Node* current = head_;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void SinglyLinkedListPQ::insert(int data, int priority) {
    PriorityQueueItem item(data, priority, next_id_++);
    Node* new_node = new Node(item, head_);
    head_ = new_node;
    ++size_;
}

PriorityQueueItem SinglyLinkedListPQ::extract_max() {
    if (head_ == nullptr) {
        throw std::underflow_error("lista jest pusta");
    }

    Node* max_prev = nullptr;
    Node* max_node = head_;
    Node* prev = nullptr;
    Node* current = head_;

    while (current != nullptr) {
        if (current->item.has_higher_priority_than(max_node->item)) {
            max_prev = prev;
            max_node = current;
        }
        prev = current;
        current = current->next;
    }

    PriorityQueueItem result = max_node->item;

    if (max_prev == nullptr) {
        head_ = max_node->next;
    } else {
        max_prev->next = max_node->next;
    }

    delete max_node;
    --size_;
    return result;
}

PriorityQueueItem SinglyLinkedListPQ::peek() const {
    if (head_ == nullptr) {
        throw std::underflow_error("lista jest pusta");
    }

    Node* max_node = head_;
    Node* current = head_->next;

    while (current != nullptr) {
        if (current->item.has_higher_priority_than(max_node->item)) {
            max_node = current;
        }
        current = current->next;
    }

    return max_node->item;
}

void SinglyLinkedListPQ::modify_key(int data, int new_priority) {
    Node* current = head_;
    while (current != nullptr) {
        if (current->item.data == data) {
            current->item.priority = new_priority;
            return;
        }
        current = current->next;
    }
    throw std::runtime_error("nie ma elementu o takiej wartosci");
}

int SinglyLinkedListPQ::return_size() const {
    return size_;
}

PriorityQueueItem SinglyLinkedListPQ::get_element_at(int index) const {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("indeks poza zakresem");
    }
    Node* current = head_;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->item;
}
