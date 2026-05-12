#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <string>

// Mierzy czas operacji obu struktur dla rosnących N.
// Wyniki lądują w CSV: N,structure,operation,avg_time_ns.
// seed = 0 oznacza losowy (inny przy każdym uruchomieniu).
class Benchmark {
private:
    int n_min_;
    int n_max_;
    int n_step_;
    int num_queries_;   // liczba zapytań K dla modify_key
    int num_repeats_;   // ile razy powtórzyć pomiar, żeby uśrednić
    unsigned int seed_; // 0 = losowy, każda inna wartość = powtarzalny
    std::string output_file_;

    void benchmark_max_heap(std::ofstream& out);
    void benchmark_singly_linked_list(std::ofstream& out);

public:
    Benchmark(int n_min = 5000,
              int n_max = 100000,
              int n_step = 5000,
              int num_queries = 100,
              int num_repeats = 50,
              const std::string& output_file = "benchmark_results.csv",
              unsigned int seed = 0);

    void run_all();
};

#endif // BENCHMARK_HPP
