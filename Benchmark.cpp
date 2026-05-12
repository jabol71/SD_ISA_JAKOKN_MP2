#include "Benchmark.hpp"
#include "MaxHeap.hpp"
#include "SinglyLinkedListPQ.hpp"

#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

// std::shuffle to funkcja, nie kontener STL
#include <algorithm>

Benchmark::Benchmark(int n_min, int n_max, int n_step,
                     int num_queries, int num_repeats,
                     const std::string& output_file,
                     unsigned int seed)
    : n_min_(n_min), n_max_(n_max), n_step_(n_step),
      num_queries_(num_queries), num_repeats_(num_repeats),
      seed_(seed), output_file_(output_file) {}

// --- Pomiary: MaxHeap ---
void Benchmark::benchmark_max_heap(std::ofstream& out) {
    std::mt19937 rng(seed_ != 0 ? seed_ : std::random_device{}());
    const int priority_range = 5 * n_max_;

    for (int n = n_min_; n <= n_max_; n += n_step_) {
        std::uniform_int_distribution<int> dist_priority(0, priority_range);
        std::uniform_int_distribution<int> dist_data(0, n_max_);

        {
            long long total_ns = 0;
            for (int r = 0; r < num_repeats_; ++r) {
                MaxHeap heap;
                for (int i = 0; i < n; ++i) {
                    heap.insert(dist_data(rng), dist_priority(rng));
                }
                int new_data = dist_data(rng);
                int new_priority = dist_priority(rng);
                auto start = std::chrono::high_resolution_clock::now();
                heap.insert(new_data, new_priority);
                auto end = std::chrono::high_resolution_clock::now();
                total_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }
            out << n << ",MaxHeap,insert," << (total_ns / num_repeats_) << "\n";
        }

        {
            long long total_ns = 0;
            for (int r = 0; r < num_repeats_; ++r) {
                MaxHeap heap;
                for (int i = 0; i < n; ++i) {
                    heap.insert(dist_data(rng), dist_priority(rng));
                }
                auto start = std::chrono::high_resolution_clock::now();
                heap.extract_max();
                auto end = std::chrono::high_resolution_clock::now();
                total_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }
            out << n << ",MaxHeap,extract_max," << (total_ns / num_repeats_) << "\n";
        }

        {
            long long total_ns = 0;
            for (int r = 0; r < num_repeats_; ++r) {
                MaxHeap heap;
                for (int i = 0; i < n; ++i) {
                    heap.insert(dist_data(rng), dist_priority(rng));
                }
                auto start = std::chrono::high_resolution_clock::now();
                heap.peek();
                auto end = std::chrono::high_resolution_clock::now();
                total_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }
            out << n << ",MaxHeap,peek," << (total_ns / num_repeats_) << "\n";
        }

        {
            long long total_ns = 0;
            for (int r = 0; r < num_repeats_; ++r) {
                MaxHeap heap;
                for (int i = 0; i < n; ++i) {
                    heap.insert(dist_data(rng), dist_priority(rng));
                }
                auto start = std::chrono::high_resolution_clock::now();
                heap.return_size();
                auto end = std::chrono::high_resolution_clock::now();
                total_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }
            out << n << ",MaxHeap,return_size," << (total_ns / num_repeats_) << "\n";
        }

        {
            MaxHeap heap;
            int* inserted_data = new int[n];
            for (int i = 0; i < n; ++i) {
                int d = i;  // dane == indeks, żeby modify_key mogło jednoznacznie trafić w element
                int p = dist_priority(rng);
                heap.insert(d, p);
                inserted_data[i] = d;
            }

            std::shuffle(inserted_data, inserted_data + n, rng);

            int k = (num_queries_ < n) ? num_queries_ : n;
            std::uniform_int_distribution<int> dist_new_priority(0, priority_range);

            auto start = std::chrono::high_resolution_clock::now();
            for (int q = 0; q < k; ++q) {
                heap.modify_key(inserted_data[q], dist_new_priority(rng));
            }
            auto end = std::chrono::high_resolution_clock::now();
            long long total_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

            out << n << ",MaxHeap,modify_key," << (total_ns / k) << "\n";
            delete[] inserted_data;
        }

        std::cout << "  MaxHeap: N = " << n << " — pomiary zakonczone." << std::endl;
    }
}

// --- Pomiary: SinglyLinkedListPQ ---
void Benchmark::benchmark_singly_linked_list(std::ofstream& out) {
    std::mt19937 rng(seed_ != 0 ? seed_ : std::random_device{}());
    const int priority_range = 5 * n_max_;

    for (int n = n_min_; n <= n_max_; n += n_step_) {
        std::uniform_int_distribution<int> dist_priority(0, priority_range);
        std::uniform_int_distribution<int> dist_data(0, priority_range);

        {
            long long total_ns = 0;
            for (int r = 0; r < num_repeats_; ++r) {
                SinglyLinkedListPQ list;
                for (int i = 0; i < n; ++i) {
                    list.insert(dist_data(rng), dist_priority(rng));
                }
                int new_data = dist_data(rng);
                int new_priority = dist_priority(rng);
                auto start = std::chrono::high_resolution_clock::now();
                list.insert(new_data, new_priority);
                auto end = std::chrono::high_resolution_clock::now();
                total_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }
            out << n << ",SinglyLinkedListPQ,insert," << (total_ns / num_repeats_) << "\n";
        }

        {
            long long total_ns = 0;
            for (int r = 0; r < num_repeats_; ++r) {
                SinglyLinkedListPQ list;
                for (int i = 0; i < n; ++i) {
                    list.insert(dist_data(rng), dist_priority(rng));
                }
                auto start = std::chrono::high_resolution_clock::now();
                list.extract_max();
                auto end = std::chrono::high_resolution_clock::now();
                total_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }
            out << n << ",SinglyLinkedListPQ,extract_max," << (total_ns / num_repeats_) << "\n";
        }

        {
            long long total_ns = 0;
            for (int r = 0; r < num_repeats_; ++r) {
                SinglyLinkedListPQ list;
                for (int i = 0; i < n; ++i) {
                    list.insert(dist_data(rng), dist_priority(rng));
                }
                auto start = std::chrono::high_resolution_clock::now();
                list.peek();
                auto end = std::chrono::high_resolution_clock::now();
                total_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }
            out << n << ",SinglyLinkedListPQ,peek," << (total_ns / num_repeats_) << "\n";
        }

        {
            long long total_ns = 0;
            for (int r = 0; r < num_repeats_; ++r) {
                SinglyLinkedListPQ list;
                for (int i = 0; i < n; ++i) {
                    list.insert(dist_data(rng), dist_priority(rng));
                }
                auto start = std::chrono::high_resolution_clock::now();
                list.return_size();
                auto end = std::chrono::high_resolution_clock::now();
                total_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }
            out << n << ",SinglyLinkedListPQ,return_size," << (total_ns / num_repeats_) << "\n";
        }

        {
            SinglyLinkedListPQ list;
            int* inserted_data = new int[n];
            for (int i = 0; i < n; ++i) {
                int d = i;  // dane == indeks, żeby modify_key mogło jednoznacznie trafić w element
                int p = dist_priority(rng);
                list.insert(d, p);
                inserted_data[i] = d;
            }

            std::shuffle(inserted_data, inserted_data + n, rng);

            int k = (num_queries_ < n) ? num_queries_ : n;
            std::uniform_int_distribution<int> dist_new_priority(0, priority_range);

            auto start = std::chrono::high_resolution_clock::now();
            for (int q = 0; q < k; ++q) {
                list.modify_key(inserted_data[q], dist_new_priority(rng));
            }
            auto end = std::chrono::high_resolution_clock::now();
            long long total_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

            out << n << ",SinglyLinkedListPQ,modify_key," << (total_ns / k) << "\n";
            delete[] inserted_data;
        }

        std::cout << "  SinglyLinkedListPQ: N = " << n << " — pomiary zakonczone." << std::endl;
    }
}

void Benchmark::run_all() {
    std::ofstream out(output_file_);
    if (!out.is_open()) {
        std::cerr << "Blad: nie mozna otworzyc pliku wyjsciowego: " << output_file_ << std::endl;
        return;
    }

    out << "N,structure,operation,avg_time_ns\n";

    std::cout << "[Benchmark] Rozpoczecie pomiarow wydajnosciowych." << std::endl;
    std::cout << "  Zakres N: [" << n_min_ << ", " << n_max_ << "], krok: " << n_step_ << std::endl;
    std::cout << "  Liczba zapytan K (modify_key): " << num_queries_ << std::endl;
    std::cout << "  Liczba powtorzen pomiaru: " << num_repeats_ << std::endl;
    if (seed_ != 0)
        std::cout << "  Seed: " << seed_ << " (powtarzalny)" << std::endl;
    else
        std::cout << "  Seed: losowy" << std::endl;
    std::cout << std::endl;

    std::cout << "[Benchmark] Pomiary dla MaxHeap:" << std::endl;
    benchmark_max_heap(out);

    std::cout << std::endl;
    std::cout << "[Benchmark] Pomiary dla SinglyLinkedListPQ:" << std::endl;
    benchmark_singly_linked_list(out);

    out.close();
    std::cout << std::endl;
    std::cout << "[Benchmark] Pomiary zakonczone. Wyniki zapisano do: " << output_file_ << std::endl;
}
