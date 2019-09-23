#include "genetic.h"

Genetic::Genetic(int initial_population): 
eng(rd()), geneGenerator(0, 1), splitGenerator(0, 5),
mutationGenerator(0, 20) {
    population_size = initial_population;
}

void Genetic::generate_population() {
    for (int i=0; i<population_size; i++) {

        int genes[5] = {0};

        std::string cromosome;
        for (int j=0; j<5; j++) {
            int g = geneGenerator(eng);
            genes[j] = g;
            cromosome.append(std::to_string(g));
        }

        Individual a = Individual(genes);
        population.push_back(a);

        //std::cout << "Genes " << i << ": " << cromosome << "\n"; 
        
    }
}

int Genetic::calculate_fitness() {
    std::cout << "Calculating fitness\n";
    int total = 0;
    Individual fittest;
    for (int i=0; i<population_size; i++) {
        Individual &current = population[i];

        int *genes = current.getGenes();

        std::string cromosome;
        for (int i=0; i<5; i++) {
            cromosome.append(std::to_string(genes[i]));
        }

        calculate_fitness(current);
        total += current.score;
        std::cout << "Gene " << i << ": " << cromosome << ", score: " << current.score << "\n";

        // if (this->fittest.getScore() < current.getScore()) {
        //     this->fittest = current;
        // }
        if (this->fittest.score < current.score) {
            this->fittest = current;
        }
    }
    return total;
}

void Genetic::calculate_fitness(Individual &i) {
    int *genes = i.getGenes();
    int score = 0;
    for (int j=0; j<5; j++) {
        score += genes[j];    
    }
    // i.setScore(score);
    i.score = score;
}

void Genetic::selection() {
    std::cout << "Selecting\n";
    prom = 0;
    for (int i=0; i<population_size; i++) {
        Individual &current = population[i];
        //std::cout << "Score " << i << ": " << current.score << "\n";
        prom += current.score;
    }
    prom /= population_size;
    individuals_selected = 0;

    std::cout << "Average: " << prom << "\n";

    for (int i=0; i<population_size; i++) {
        Individual &current = population[i];
        if (current.score <= prom) {
            current.setSelected(true);
            individuals_selected++;
            std::cout << "Individual selected\n";
        }
    }
}

void Genetic::crossover() {
    std::cout << "Doing crossover\n";
    while (individuals_selected > 1) {
        Individual &i1 = getSelected();
        Individual &i2 = getSelected();
        individuals_selected -= 2;

        int splitPoint = splitGenerator(eng);
        std::cout << "Split point: " << splitPoint << "\n";
        int genes1[5] = {0};
        int genes2[5] = {0};

        for (int i=0; i<splitPoint; i++) {
            genes1[i] = i2.getGenes()[i];
            genes2[i] = i1.getGenes()[i];            
        }
        for (int i=splitPoint; i<5; i++) {
            genes1[i] = i1.getGenes()[i];
            genes2[i] = i2.getGenes()[i];
        }

        Individual o1 = Individual(genes1);
        Individual o2 = Individual(genes2);

        mutate(o1);
        mutate(o2);
        calculate_fitness(o1);
        calculate_fitness(o2);
        swapIndividuals(o1);
        swapIndividuals(o2);
    }
    getSelected();
}

void Genetic::mutate(Individual &in) {
    int *genes = in.getGenes();

    int mutationChance = mutationGenerator(eng);
    if (mutationChance <= 3) {
        std::cout << "Mutating\n";
        for (int i=0; i<5; i++) {
            int flip = mutationGenerator(eng);
            if (flip <= 3) {
                genes[i] = geneGenerator(eng);
            }
        }
    }
}

Individual Genetic::get_fittest() {
    return fittest;
}

Individual &Genetic::getSelected() {
    for (int i=0; i< population_size; i++) {
        Individual &current = population[i];
        if (current.isSelected()) {
            current.setSelected(false);
            return current;
        }
    }
}

void Genetic::swapIndividuals(Individual &newIndividual) {
    for (int i=0; i<population_size; i++) {
        Individual &current = population[i];
        if (!current.isSelected() && (current.score < newIndividual.score) ) {
            population.erase(population.begin() + i);
            population.push_back(newIndividual);
        }
    }
}
