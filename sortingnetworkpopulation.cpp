#include "sortingnetworkpopulation.h"

SortingNetworkPopulation::SortingNetworkPopulation()
{

}

template<typename T>
void SortingNetworkPopulation::printElement(T t, const int& width)
{
    std::cout << std::left << std::setw(width) << std::setfill(' ') << t;
}

void SortingNetworkPopulation::printPopulation(void)
{
    std::cout << "\r\n";
    printElement("Num ", 5);
    printElement("Chromosomes:", 82);
    printElement("Int Fitness: ", 13);
    printElement("Ext Fitness: ", 13);
    std::cout << "\r\n";
    for (unsigned int i = 0; i < _population.size(); i++)
    {
        printElement(i, 5);
        _population[i].printFirstChromosomes();
        printElement(_population[i].getInternalFitness(), 13);
        std::cout << _population[i].getExternalFitness() << "\r\n     ";
        _population[i].printSecondChromosomes();
    }
    std::cout << "\r\n";
}

void SortingNetworkPopulation::doBreed(void)
{
    if (_isOutput) std::cout << "\r\n";
    int count = _population.size();
    int max = (int) count / 3;
    int breed = 2 * ((rand() % max) + 1);
    int breakPoint = 1;
    int childCount = _population.size() - 1;
    for (int i = 0; i < breed; i += 2)
    {
        //breakPoint = (rand() % (_population[0].getNetworkSize() - 3)) + 2;
        breakPoint = (rand() % (_population[0].getNetworkSize() - 2)) + 1;
        for (int j = 0; j < _population[0].getNetworkSize(); j++)
        {
            if (j < breakPoint)
            {
                _population[childCount].setSingleChromosome(_population[i + 1].getSingleChromosome(j), j);
            }
            else
            {
                _population[childCount].setSingleChromosome(_population[i].getSingleChromosome(j), j);
            }
        }
        if (_isOutput)
        {
            std::cout << "Break point: " << breakPoint << "\r\nParents:\r\n";
            printElement(i, 5);
            std::cout << ": ";
            _population[i].printFirstChromosomes();
            std::cout << "\r\n       ";
            _population[i].printSecondChromosomes();
            std::cout << "\r\n";
            printElement(i + 1, 5);
            std::cout << ": ";
            _population[i + 1].printFirstChromosomes();
            std::cout << "\r\n       ";
            _population[i + 1].printSecondChromosomes();
            std::cout << "\r\nchild: ";
            _population[childCount].printFirstChromosomes();
            std::cout << "\r\n       ";
            _population[childCount].printSecondChromosomes();
            std::cout << "\r\n";
        }
        childCount--;
    }
    if (_isOutput) std::cout << "\r\n";
}

void SortingNetworkPopulation::generatePopulation(int massiveSize, int networkSize)
{
    for (int i = 0; i < _size; i++) _population.push_back(SortingNetworkIndividual(massiveSize, networkSize));
}

void SortingNetworkPopulation::doSort(void)
{
    std::sort(_population.begin(), _population.end(), isNetworkBetter);
}

void SortingNetworkPopulation::setSize(int value)
{
    _size = value;
}

int SortingNetworkPopulation::getSize(void) const
{
    return _size;
}

SortingNetworkIndividual &SortingNetworkPopulation::getIndividual(int number)
{
    return _population[number];
}

void SortingNetworkPopulation::setOutput(bool value)
{
    _isOutput = value;
}

void SortingNetworkPopulation::mutatePopulation(void)
{
    _mutationBuffer = "Sorting networks has been mutated: ";
    for (int i = 0; i < _size; i++)
    {
        if ((rand() % 100) > 50)
        {
            _population[i].doMutation();
            _mutationBuffer += std::to_string(i) + " ";
        }
    }
}

void SortingNetworkPopulation::printMutation(void)
{
    std::cout << _mutationBuffer << "\r\n";
}
