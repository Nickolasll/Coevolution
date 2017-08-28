#ifndef SORTINGNETWORKINDIVIDUAL_H
#define SORTINGNETWORKINDIVIDUAL_H
#include <vector>
#include <stdlib.h>
#include <iostream>

class SortingNetworkIndividual
{
public:
    SortingNetworkIndividual(int massiveSize, int networkSize);

    //! void
    void printFirstChromosomes(void);
    void printSecondChromosomes(void);
    void doMutation(void);

    //! set
    void setInternalFitness(int value);
    void setExternalFitness(int value);
    void setChromosomes(std::vector<std::pair<int, int>> value);
    void setSingleChromosome(std::pair<int, int> value, int position);

    //! set
    int getInternalFitness(void) const;
    int getExternalFitness(void) const;
    int getNetworkSize(void) const;
    int getMassiveSize(void) const;
    std::vector<std::pair<int, int>> getChromosomes(void) const;
    std::pair<int, int> getSingleChromosome(int position) const;

private:
    void chromosomeGenerator(void);

    int _internalFitness = 0x00;
    int _externalFitness = 0x00;
    int _networkSize     = 20;
    int _massiveSize     = 10;

    std::vector<std::pair<int, int>> _chromosomes;
};

bool isNetworkBetter(SortingNetworkIndividual net1, SortingNetworkIndividual net2);

#endif // SORTINGNETWORKINDIVIDUAL_H
