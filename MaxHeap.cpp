#include "MaxHeap.hpp"
#include <stdexcept>

MaxHeap::MaxHeap()
    : size_(0), capacity_(16), next_id_(0)
{
    array_ = new PriorityQueueItem[capacity_];
}

MaxHeap::~MaxHeap() {
    delete[] array_;
}

void MaxHeap::resize(int new_capacity) {
    PriorityQueueItem* new_array = new PriorityQueueItem[new_capacity];
    for (int i = 0; i < size_; ++i) {
        new_array[i] = array_[i];
    }
    delete[] array_;
    array_ = new_array;
    capacity_ = new_capacity;
}

void MaxHeap::heapify_up(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (array_[index].has_higher_priority_than(array_[parent])) {
            PriorityQueueItem temp = array_[index];
            array_[index] = array_[parent];
            array_[parent] = temp;
            index = parent;
        } else {
            break;
        }
    }
}

void MaxHeap::heapify_down(int index) {
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < size_ && array_[left].has_higher_priority_than(array_[largest])) {
            largest = left;
        }
        if (right < size_ && array_[right].has_higher_priority_than(array_[largest])) {
            largest = right;
        }

        if (largest != index) {
            PriorityQueueItem temp = array_[index];
            array_[index] = array_[largest];
            array_[largest] = temp;
            index = largest;
        } else {
            break;
        }
    }
}

void MaxHeap::insert(int data, int priority) {
    if (size_ == capacity_) {
        resize(capacity_ * 2);
    }
    array_[size_] = PriorityQueueItem(data, priority, next_id_++);
    heapify_up(size_);
    ++size_;
}

PriorityQueueItem MaxHeap::extract_max() {
    if (size_ == 0) {
        throw std::underflow_error("kopiec jest pusty");
    }
    PriorityQueueItem max_item = array_[0];
    array_[0] = array_[size_ - 1];
    --size_;
    if (size_ > 0) {
        heapify_down(0);
    }
    return max_item;
}

PriorityQueueItem MaxHeap::peek() const {
    if (size_ == 0) {
    }
    return array_[0];
}

void MaxHeap::modify_key(int data, int new_priority) {
    int index = -1;
    for (int i = 0; i < size_; ++i) {
        if (array_[i].data == data) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        throw std::runtime_error("nie ma elementu o takiej wartosci");
    }

    int old_priority = array_[index].priority;
    array_[index].priority = new_priority;

    if (new_priority > old_priority) {
        heapify_up(index);
    } else if (new_priority < old_priority) {
        heapify_down(index);
    }
}

int MaxHeap::return_size() const {
    return size_;
}

PriorityQueueItem MaxHeap::get_element_at(int index) const {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("indeks poza zakresem");
    }
    return array_[index];
}
