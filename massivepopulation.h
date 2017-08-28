#ifndef MASSIVEPOPULATION_H
#define MASSIVEPOPULATION_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>

#include "massiveindividual.h"

class MassivePopulation
{
public:
    MassivePopulation();

    //!void
    void generatePopulation(int vectorSize);
    void doSort(void);
    void printIndividual(int number);
    void printPopulation(void);
    void doBreed(void);
    void mutatePopulation(void);
    void printMutation(void);

    //!set
    void setSize(int value);
    void setZeroes(void);
    void setOutput(bool value);

    //!get
    int getSize(void) const;
    MassiveIndividual &getIndividual(int number);

private:
    template<typename T>
    void printElement(T t, const int& width);

    int  _size     = 3;
    bool _isOutput = true;
    std::vector<MassiveIndividual> _population;
    std::string _mutationBuffer = "";
};

#endif // MASSIVEPOPULATION_H
