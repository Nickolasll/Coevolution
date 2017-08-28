#ifndef MASSIVEINDIVIDUAL_H
#define MASSIVEINDIVIDUAL_H
#include <vector>
#include <stdlib.h>

class MassiveIndividual
{
public:
    MassiveIndividual(int size);

    //!void
    void doMutation(void);

    //!set
    void setInternalFitness(int value);
    void setChromosomes(std::vector<int> value);
    void setSingleChromosome(int value, int position);

    //!get
    int getVectorSize(void) const;
    int getInternalFitness(void) const;
    std::vector<int> getChromosomes(void) const;
    int getSingleChromosome(int position) const;

private:
    void chromosomeGenerator(void);

    int _internalFitness = 0x00;
    int _vectorSize      = 10;
    int _random          = 1000;

    std::vector<int> _chromosomes;
};

bool isMassiveBetter(MassiveIndividual ind1, MassiveIndividual ind2);

#endif // MASSIVEINDIVIDUAL_H
