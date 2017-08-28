#include "sortingnetworkindividual.h"

SortingNetworkIndividual::SortingNetworkIndividual(int massiveSize, int networkSize)
{
    _networkSize = networkSize;
    _massiveSize = massiveSize;
    chromosomeGenerator();
}

void SortingNetworkIndividual::printFirstChromosomes(void)
{
    for (int i = 0; i < _networkSize / 2; i++)
    {
        std::cout << _chromosomes[i].first << "-" << _chromosomes[i].second << " ";
    }
    std::cout << "  ";
}

void SortingNetworkIndividual::printSecondChromosomes(void)
{
    for (int i = _networkSize / 2; i < _networkSize ; i++)
    {
        std::cout << _chromosomes[i].first << "-" << _chromosomes[i].second << " ";
    }
    std::cout << "\r\n";
}

void SortingNetworkIndividual::chromosomeGenerator(void)
{
    int first  = 0;
    int second = 0;
    for (int i = 0; i < _networkSize; i++)
    {
        if ((rand() % 100) < 70)
        {
            _chromosomes.push_back(std::make_pair(0, 0));
        }
        else
        {
            first = rand() % _massiveSize;
            second = rand() % _massiveSize;
            while(second == first)
            {
                second = rand() % _massiveSize;
            }
            _chromosomes.push_back(std::make_pair(first, second));
        }
    }
}

void SortingNetworkIndividual::setInternalFitness(int value)
{
    _internalFitness = value;
}

void SortingNetworkIndividual::setExternalFitness(int value)
{
    _externalFitness = value;
}

int SortingNetworkIndividual::getInternalFitness(void) const
{
    return _internalFitness;
}

int SortingNetworkIndividual::getExternalFitness(void) const
{
    return _externalFitness;
}

int SortingNetworkIndividual::getNetworkSize(void) const
{
    return _networkSize;
}

int SortingNetworkIndividual::getMassiveSize(void) const
{
    return _massiveSize;
}

std::vector<std::pair<int, int>> SortingNetworkIndividual::getChromosomes(void) const
{
    return _chromosomes;
}

void SortingNetworkIndividual::setChromosomes(std::vector<std::pair<int, int>> value)
{
    _chromosomes = value;
}

std::pair<int, int> SortingNetworkIndividual::getSingleChromosome(int position) const
{
    return _chromosomes[position];
}

void SortingNetworkIndividual::setSingleChromosome(std::pair<int, int> value, int position)
{
    _chromosomes[position] = value;
}

void SortingNetworkIndividual::doMutation(void)
{
    int first  = rand() % _massiveSize;
    int second = rand() % _massiveSize;
    while (second == first)
    {
        second = rand() % _massiveSize;
    }
    setSingleChromosome(std::make_pair(first, second), rand() % _networkSize);
}

bool isNetworkBetter(SortingNetworkIndividual net1, SortingNetworkIndividual net2)
{
    return (net1.getInternalFitness() > net2.getInternalFitness());
}
