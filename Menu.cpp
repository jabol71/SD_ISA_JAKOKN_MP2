#include "Menu.hpp"
#include "Benchmark.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

Menu::Menu() {}

void Menu::display_options() const {
    std::cout << "\n==========================================================" << std::endl;
    std::cout << "  Kolejka priorytetowa — menu glowne" << std::endl;
    std::cout << "==========================================================" << std::endl;
    std::cout << "  2. Wstaw element (insert)" << std::endl;
    std::cout << "  3. Wyswietl maksimum (peek)" << std::endl;
    std::cout << "  4. Usun maksimum (extract_max)" << std::endl;
    std::cout << "  5. Zmien priorytet elementu (modify_key)" << std::endl;
    std::cout << "  6. Wyswietl rozmiar struktury (return_size)" << std::endl;
    std::cout << "  7. Uruchom benchmark" << std::endl;
    std::cout << "  0. Wyjscie" << std::endl;
    std::cout << "==========================================================" << std::endl;
    std::cout << "  Wybor: ";
}

void Menu::load_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "  Blad: nie mozna otworzyc pliku: " << filename << std::endl;
        return;
    }

    int data, priority;
    int count = 0;
    while (file >> data >> priority) {
        heap_.insert(data, priority);
        list_.insert(data, priority);
        ++count;
    }
    file.close();
    std::cout << "  Wczytano " << count << " elementow z pliku: " << filename << std::endl;
}

void Menu::run() {
    int choice;
    bool running = true;

    while (running) {
        display_options();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "  Nieprawidlowe dane wejsciowe." << std::endl;
            continue;
        }

        switch (choice) {
            case 1: {
                std::cout << "  Podaj sciezke do pliku: ";
                std::string filename;
                std::cin >> filename;
                load_from_file(filename);
                break;
            }
            case 2: {
                int data, priority;
                std::cout << "  Podaj wartosc danych: ";
                std::cin >> data;
                std::cout << "  Podaj priorytet: ";
                std::cin >> priority;
                heap_.insert(data, priority);
                list_.insert(data, priority);
                std::cout << "  Element (" << data << ", " << priority
                          << ") wstawiony do obu struktur." << std::endl;
                break;
            }
            case 3: {
                try {
                    PriorityQueueItem heap_max = heap_.peek();
                    PriorityQueueItem list_max = list_.peek();
                    std::cout << "  MaxHeap — peek: data=" << heap_max.data
                              << ", priority=" << heap_max.priority << std::endl;
                    std::cout << "  SinglyLinkedListPQ — peek: data=" << list_max.data
                              << ", priority=" << list_max.priority << std::endl;
                } catch (const std::underflow_error& e) {
                    std::cerr << "  " << e.what() << std::endl;
                }
                break;
            }
            case 4: {
                try {
                    PriorityQueueItem heap_max = heap_.extract_max();
                    PriorityQueueItem list_max = list_.extract_max();
                    std::cout << "  MaxHeap — extract_max: data=" << heap_max.data
                              << ", priority=" << heap_max.priority << std::endl;
                    std::cout << "  SinglyLinkedListPQ — extract_max: data=" << list_max.data
                              << ", priority=" << list_max.priority << std::endl;
                } catch (const std::underflow_error& e) {
                    std::cerr << "  " << e.what() << std::endl;
                }
                break;
            }
            case 5: {
                int data, new_priority;
                std::cout << "  Podaj wartosc danych elementu: ";
                std::cin >> data;
                std::cout << "  Podaj nowy priorytet: ";
                std::cin >> new_priority;
                try {
                    heap_.modify_key(data, new_priority);
                    std::cout << "  MaxHeap — priorytet zmieniony." << std::endl;
                } catch (const std::runtime_error& e) {
                    std::cerr << "  MaxHeap: " << e.what() << std::endl;
                }
                try {
                    list_.modify_key(data, new_priority);
                    std::cout << "  SinglyLinkedListPQ — priorytet zmieniony." << std::endl;
                } catch (const std::runtime_error& e) {
                    std::cerr << "  SinglyLinkedListPQ: " << e.what() << std::endl;
                }
                break;
            }
            case 6: {
                std::cout << "  MaxHeap — rozmiar: " << heap_.return_size() << std::endl;
                std::cout << "  SinglyLinkedListPQ — rozmiar: " << list_.return_size() << std::endl;
                break;
            }
            case 7: {
                std::cout << "\n  [Benchmark] Konfiguracja pomiarow:" << std::endl;
                std::cout << "  Minimalne N (domyslnie 5000): ";
                int n_min, n_max, n_step, k, repeats;
                std::cin >> n_min;
                std::cout << "  Maksymalne N (domyslnie 100000): ";
                std::cin >> n_max;
                std::cout << "  Krok N (domyslnie 5000): ";
                std::cin >> n_step;
                std::cout << "  Liczba zapytan K dla modify_key (domyslnie 100): ";
                std::cin >> k;
                std::cout << "  Liczba powtorzen pomiaru (domyslnie 5): ";
                std::cin >> repeats;
                std::cout << "  Nazwa pliku wyjsciowego CSV (domyslnie benchmark_results.csv): ";
                std::string csv_file;
                std::cin >> csv_file;
                std::cout << "  Seed generatora (0 = losowy, dowolna liczba = powtarzalny): ";
                unsigned int seed;
                std::cin >> seed;

                Benchmark bench(n_min, n_max, n_step, k, repeats, csv_file, seed);
                bench.run_all();
                break;
            }
            case 0: {
                running = false;
                std::cout << "  Zakonczenie programu." << std::endl;
                break;
            }
            default: {
                std::cout << "  Nieprawidlowy wybor. Prosze wybrac opcje z zakresu 0-7." << std::endl;
                break;
            }
        }
    }
}
