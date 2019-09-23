#include "individual.h"

Individual::Individual() {
    
}

Individual::Individual(int *genes) {
    copyGenes(genes);
}

int *Individual::getGenes() {
    return genes;
}

void Individual::setGenes(int *genes) {
    copyGenes(genes);
}

void ::Individual::copyGenes(int *genes) {
    for (int i=0; i < 5; i++) {
        this->genes[i] = genes[i];
    }
}

// int Individual::getScore() {
//     return score;
// }

// void Individual::setScore(int s) {
//     score = s;
// }

bool Individual::isSelected() {
    return selected;
}

void Individual::setSelected(bool select) {
    selected = select;
}