#ifndef SEQUENTIALCOEVOLUTION_H
#define SEQUENTIALCOEVOLUTION_H

#include <vector>
#include <algorithm>
#include <iostream>

#include "sortingnetworkindividual.h"
#include "sortingnetworkpopulation.h"

#include "massiveindividual.h"
#include "massivepopulation.h"

class SequentialCoevolution
{
public:
    SequentialCoevolution();
	~SequentialCoevolution(){}

	//! void
    void assertNetworkFitness(SortingNetworkPopulation &networkPopulation, MassivePopulation &massivePopulation, bool isExternal);
    void assertMassiveFitness(MassivePopulation &massivePopulation, SortingNetworkPopulation &networkPopulation);
    bool testInputNetwork(SortingNetworkIndividual &network, MassiveIndividual &massive);

	//! set
    void setMaxCycles(int value);
	void setCurrentCycles(int value);
	
	//! get
    int getMaxCycles(void) const;	
    int getCurrentCycles(void) const;

private:
    bool testNetwork(SortingNetworkIndividual &network, MassiveIndividual &massive);

    int _maxCycles      = 1;
    int _currentCycles  = 0;
};

#endif // SEQUENTIALCOEVOLUTION_H
