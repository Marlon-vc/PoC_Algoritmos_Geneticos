#ifndef INDIVIDUAL
#define INDIVIDUAL

class Individual {
    public:
        Individual();
        Individual(int *genes);
        int *getGenes();
        void setGenes(int *genes);
        //int getScore();
        //void setScore(int score);
        void setSelected(bool select);
        bool isSelected();
        int score = 0;
    private:
        bool selected = false;
        int genes[5] = {0};
        void copyGenes(int *genes);
};

#endif