#ifndef MAX_HEAP_HPP
#define MAX_HEAP_HPP

#include "PriorityQueueItem.hpp"

// Kolejka priorytetowa max na kopcu binarnym.
// Tablica rośnie dwukrotnie gdy zabraknie miejsca.
class MaxHeap {
private:
    PriorityQueueItem* array_;
    int size_;
    int capacity_;
    unsigned long long next_id_;

    void heapify_up(int index);
    void heapify_down(int index);
    void resize(int new_capacity);

public:
    MaxHeap();
    ~MaxHeap();

    // kopiowanie i przenoszenie zakazane
    MaxHeap(const MaxHeap&) = delete;
    MaxHeap& operator=(const MaxHeap&) = delete;

    void insert(int data, int priority);
    PriorityQueueItem extract_max();
    PriorityQueueItem peek() const;

    // po zmianie priorytetu woła heapify_up lub heapify_down w zależności od kierunku
    void modify_key(int data, int new_priority);

    int return_size() const;
    PriorityQueueItem get_element_at(int index) const;
};

#endif // MAX_HEAP_HPP
