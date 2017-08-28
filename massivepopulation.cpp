#include "massivepopulation.h"

MassivePopulation::MassivePopulation()
{

}

void MassivePopulation::setSize(int value)
{
    _size = value;
}


int MassivePopulation::getSize(void) const
{
    return _size;
}

MassiveIndividual &MassivePopulation::getIndividual(int number)
{
    return _population[number];
}

template<typename T>
void MassivePopulation::printElement(T t, const int& width)
{
    std::cout << std::left << std::setw(width) << std::setfill(' ') << t;
}

void MassivePopulation::generatePopulation(int vectorSize)
{
    for (int i = 0; i < _size; i++)
    {
        _population.push_back(MassiveIndividual(vectorSize));
    }
}

void MassivePopulation::doSort(void)
{
    std::sort(_population.begin(), _population.end(), isMassiveBetter);
}

void MassivePopulation::printIndividual(int number)
{
    for (int i = 0; i < _population[0].getVectorSize(); i++)
    {
        printElement(_population[number].getSingleChromosome(i), 6);
    }
}

void MassivePopulation::printPopulation(void)
{
    std::cout << "\r\n";
    printElement("Num ", 5);
    printElement("Chromosomes:  ", (_population[0].getVectorSize() - 2) * 6 + 14);
    printElement("Internal Fitness: ", 18);
    std::cout << "\r\n";
    for (unsigned int i = 0; i < _population.size(); i++)
    {
        printElement(i, 5);
        printIndividual(i);
        std::cout << "  ";
        _population[i].getVectorSize();
        std::cout << _population[i].getInternalFitness() << "\r\n";
    }
    std::cout << "\r\n";
}

void MassivePopulation::doBreed(void)
{
    if (_isOutput) std::cout << "\r\n";
    int count = _population.size();
    int max = (int) count / 3;
    int breed = 2 * ((rand() % max) + 1);
    int breakPoint = 1;
    int childCount = _population.size() - 1;
    for (int i = 0; i < breed; i += 2)
    {
        breakPoint = (rand() % (_population[0].getVectorSize() - 2)) + 1;
        for (int j = 0; j < _population[0].getVectorSize(); j++)
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
            printIndividual(i);
            std::cout << "\r\n";
            printElement(i + 1, 5);
            std::cout << ": ";
            printIndividual(i + 1);
            std::cout << "\r\nchild: ";
            printIndividual(childCount);
            std::cout << "\r\n";
        }
        childCount--;
    }
    if (_isOutput) std::cout << "\r\n";
}

void MassivePopulation::setZeroes(void)
{
    std::vector<int> zeros(_population[0].getVectorSize(), 0);
    for (int i = 0; i < _size; i++)
    {
        _population[i].setChromosomes(zeros);
    }
}

void MassivePopulation::setOutput(bool value)
{
    _isOutput = value;
}

void MassivePopulation::mutatePopulation(void)
{
    _mutationBuffer = "Massives has been mutated: ";
    for (int i = 0; i < _size; i++)
    {
        if ((rand() % 100) > 50)
        {
            _population[i].doMutation();
            _mutationBuffer += std::to_string(i) + " ";
        }
    }
}

void MassivePopulation::printMutation(void)
{
    std::cout << _mutationBuffer << "\r\n";
}
