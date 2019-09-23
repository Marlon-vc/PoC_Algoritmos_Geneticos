#include "genetic.cpp"
#include "individual.cpp"
#include <chrono>
#include <thread>

int main() {
    Genetic algorithm(10);
    algorithm.generate_population();

    int generations = 1;

    int prev_score = 0;
    int score = 0;
    int count = 10;
    while (algorithm.get_fittest().score < 5 && count > 0) {
        prev_score = score;
        score = algorithm.calculate_fitness();
        if (prev_score == score) {
            std::cout << "EQUALS\n";
            std::cout << "Score: " << score << "\n";
            std::cout << "Prev: " << prev_score << "\n";
            count--;
        }
        algorithm.selection();
        algorithm.crossover();
        generations++;
    }
    algorithm.calculate_fitness();
    std::cout << "Solution set found at generation: " << generations << "\n";
    std::cout << "Fittest individual score: " << algorithm.get_fittest().score << "\n";
    
    return 0;
}