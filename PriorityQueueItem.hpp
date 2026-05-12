#ifndef PRIORITY_QUEUE_ITEM_HPP
#define PRIORITY_QUEUE_ITEM_HPP

struct PriorityQueueItem {
    int data;
    int priority;
    unsigned long long insertion_id;  // FIFO przy równych priorytetach — mniejszy id wchodzi pierwszy

    PriorityQueueItem()
        : data(0), priority(0), insertion_id(0) {}

    PriorityQueueItem(int data, int priority, unsigned long long insertion_id)
        : data(data), priority(priority), insertion_id(insertion_id) {}

    bool has_higher_priority_than(const PriorityQueueItem& other) const {
        if (priority != other.priority)
            return priority > other.priority;
        return insertion_id < other.insertion_id;  // starszy element wygrywa remis
    }
};

#endif // PRIORITY_QUEUE_ITEM_HPP
