#ifndef MENU_HPP
#define MENU_HPP

#include "MaxHeap.hpp"
#include "SinglyLinkedListPQ.hpp"
#include <string>

class Menu {
private:
    MaxHeap heap_;
    SinglyLinkedListPQ list_;

    void display_options() const;

    // format pliku: jedna para "data priorytet" na wiersz
    void load_from_file(const std::string& filename);

public:
    Menu();
    void run();
};

#endif // MENU_HPP
