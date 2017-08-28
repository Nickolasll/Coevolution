#include "massiveindividual.h"

MassiveIndividual::MassiveIndividual(int size)
{
    _vectorSize = size;
    chromosomeGenerator();
}

void MassiveIndividual::chromosomeGenerator(void)
{
    for (int i = 0; i < _vectorSize; i++)
    {
        _chromosomes.push_back(rand() % _random - (int)(_random / 2));
    }
}

int MassiveIndividual::getSingleChromosome(int position) const
{
    return _chromosomes[position];
}

std::vector<int> MassiveIndividual::getChromosomes(void)const
{
    return _chromosomes;
}

int MassiveIndividual::getInternalFitness(void) const
{
    return _internalFitness;
}

void MassiveIndividual::setSingleChromosome(int value, int position)
{
    _chromosomes[position] = value;
}

void MassiveIndividual::setChromosomes(std::vector<int> value)
{
    _chromosomes = value;
}

void MassiveIndividual::setInternalFitness(int value)
{
    _internalFitness = value;
}

void MassiveIndividual::doMutation(void)
{
    setSingleChromosome(rand() % _random - (int)(_random / 2), rand() % _vectorSize);
}

int MassiveIndividual::getVectorSize(void) const
{
    return _vectorSize;
}

bool isMassiveBetter(MassiveIndividual ind1, MassiveIndividual ind2)
{
    return (ind1.getInternalFitness() > ind2.getInternalFitness());
}
