#include "sequentialcoevolution.h"

SequentialCoevolution::SequentialCoevolution()
{

}

void SequentialCoevolution::setMaxCycles(int value)
{
	_maxCycles = value;
}

int SequentialCoevolution::getMaxCycles(void) const
{
	return _maxCycles;
}

void SequentialCoevolution::setCurrentCycles(int value)
{
	_currentCycles = value;
}

int SequentialCoevolution::getCurrentCycles(void) const
{
    return _currentCycles;
}

bool SequentialCoevolution::testNetwork(SortingNetworkIndividual &network, MassiveIndividual &massive)
{
    std::vector<int> massiveTest  = massive.getChromosomes();
    for (int i = 0; i < network.getNetworkSize(); i++)
    {
        if (network.getSingleChromosome(i).first != network.getSingleChromosome(i).second)
        {
            std::iter_swap(&massiveTest[network.getSingleChromosome(i).first], &massiveTest[network.getSingleChromosome(i).second]);
        }
    }
    return std::is_sorted(massiveTest.begin(), massiveTest.end());
}

bool SequentialCoevolution::testInputNetwork(SortingNetworkIndividual &network, MassiveIndividual &massive)
{
    std::vector<int> massiveTest  = massive.getChromosomes();
    for (int i = 0; i < network.getNetworkSize(); i++)
    {
        if (network.getSingleChromosome(i).first != network.getSingleChromosome(i).second)
        {
            std::iter_swap(&massiveTest[network.getSingleChromosome(i).first], &massiveTest[network.getSingleChromosome(i).second]);
        }
    }
    std::cout << "\r\nResult: ";
    for (unsigned int i = 0; i < massiveTest.size(); i++)
    {
       std::cout << massiveTest[i] << " ";
    }
    return std::is_sorted(massiveTest.begin(), massiveTest.end());
}

void SequentialCoevolution::assertNetworkFitness(SortingNetworkPopulation &networkPopulation, MassivePopulation &massivePopulation, bool isExternal)
{
    for (int i = 0; i < networkPopulation.getSize(); i++)
    {
        if (isExternal)
        {
            networkPopulation.getIndividual(i).setExternalFitness(0);
        }
        else
        {
            networkPopulation.getIndividual(i).setInternalFitness(0);
        }
        for (int j = 0; j < massivePopulation.getSize(); j++)
        {
            if (testNetwork(networkPopulation.getIndividual(i), massivePopulation.getIndividual(j)))
            {
                if (isExternal)
                {
                    networkPopulation.getIndividual(i).setExternalFitness(networkPopulation.getIndividual(i).getExternalFitness() + 1);
                }
                else
                {
                    networkPopulation.getIndividual(i).setInternalFitness(networkPopulation.getIndividual(i).getInternalFitness() + 1);
                }
            }
        }
    }
}

void SequentialCoevolution::assertMassiveFitness(MassivePopulation &massivePopulation, SortingNetworkPopulation &networkPopulation)
{
    for (int i = 0; i < massivePopulation.getSize(); i++)
    {
        massivePopulation.getIndividual(i).setInternalFitness(0);
        for (int j = 0; j < networkPopulation.getSize(); j++)
        {
            if (!testNetwork(networkPopulation.getIndividual(j), massivePopulation.getIndividual(i)))
            {
                massivePopulation.getIndividual(i).setInternalFitness(massivePopulation.getIndividual(i).getInternalFitness() + 1);
            }
        }
    }
}
