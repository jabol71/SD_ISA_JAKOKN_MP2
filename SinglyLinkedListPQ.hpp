#ifndef SINGLY_LINKED_LIST_PQ_HPP
#define SINGLY_LINKED_LIST_PQ_HPP

#include "PriorityQueueItem.hpp"

// Kolejka priorytetowa max na nieposortowanej liście jednokierunkowej.
// insert O(1) (na głowę), extract_max i peek O(N) (pełne przejście).
class SinglyLinkedListPQ {
private:
    struct Node {
        PriorityQueueItem item;
        Node* next;

        Node(const PriorityQueueItem& item, Node* next)
            : item(item), next(next) {}
    };

    Node* head_;
    int size_;
    unsigned long long next_id_;

public:
    SinglyLinkedListPQ();
    ~SinglyLinkedListPQ();

    // kopiowanie i przenoszenie zakazane
    SinglyLinkedListPQ(const SinglyLinkedListPQ&) = delete;
    SinglyLinkedListPQ& operator=(const SinglyLinkedListPQ&) = delete;

    void insert(int data, int priority);
    PriorityQueueItem extract_max();
    PriorityQueueItem peek() const;

    // lista nieposortowana — zmiana priorytetu nie wymaga żadnej naprawy struktury
    void modify_key(int data, int new_priority);

    int return_size() const;
    PriorityQueueItem get_element_at(int index) const;
};

#endif // SINGLY_LINKED_LIST_PQ_HPP
