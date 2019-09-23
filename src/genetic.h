#ifndef GENETIC
#define GENETIC

#include "individual.h"
#include <vector>
#include <random>
#include <iostream>

class Genetic {
    public:
        Genetic(int initial_population);
        void generate_population();
        int calculate_fitness();
        void selection();
        void crossover();
        Individual get_fittest();
    private:
        int population_size;
        Individual fittest;
        int prom = 0;
        int individuals_selected = 0;
        std::vector<Individual> population;

        std::random_device rd;
        std::mt19937 eng;
        std::uniform_int_distribution<> geneGenerator;
        std::uniform_int_distribution<> splitGenerator;
        std::uniform_int_distribution<> mutationGenerator;
        Individual &getSelected();
        void mutate(Individual &i);
        void calculate_fitness(Individual &i);
        void swapIndividuals(Individual &newIndividual);
};

#endif