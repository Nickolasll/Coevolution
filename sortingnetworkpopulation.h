#ifndef SORTINGNETWORKPOPULATION_H
#define SORTINGNETWORKPOPULATION_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>

#include "sortingnetworkindividual.h"

class SortingNetworkPopulation
{
public:
    SortingNetworkPopulation();

    //! void
    void generatePopulation(int massiveSize, int networkSize);
    void doSort(void);
    void doBreed(void);
    void printPopulation(void);
    void mutatePopulation(void);
    void printMutation(void);

    //! set
    void setSize(int value);
    void setOutput(bool value);

    //! get
    int getSize(void) const;
    SortingNetworkIndividual &getIndividual(int number);

private:
    template<typename T>
    void printElement(T t, const int& width);

    int  _size     = 3;
    bool _isOutput = true;
    std::vector<SortingNetworkIndividual> _population;
    std::string _mutationBuffer = "";
};

#endif // SORTINGNETWORKPOPULATION_H
