#include <iostream>
#include <bitset>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <regex>
#include <fstream>

#include "sequentialcoevolution.h"

#include "massiveindividual.h"
#include "massivepopulation.h"

#include "sortingnetworkindividual.h"
#include "sortingnetworkpopulation.h"

enum
{
    INTERNAL = false,
    EXTERNAL = true
};

void readInteger(int &integer, int minValue, std::string inputMessage)
{
    std::cout << inputMessage;
    while(!(std::cin >> integer) || (integer < minValue))
    {
        std::cout << "Input value should be an integer that must be more than " << minValue << " please try again: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "\r\n";
}

void coevolutionAlgorythm(void)
{
    bool isOutput = false;

    int networkPopulationSize = 0;
    int massivePopulationSize = 0;
    int externalCycles        = 0;
    int cyclesCount           = 0;
    int massiveSize           = 0;
    int output                = 0;

    int bestGeneration        = 0;

    std::cout << "Welcome to the sequential 2-population competitive coevolution algorithm\r\n";
    std::cout << "Please enter the input data to start\r\n\r\n";

    readInteger(networkPopulationSize, 3, "Set the amount of sorting networks in the population: ");
    readInteger(massivePopulationSize, 3, "Set the amount of massives in the population: ");
    readInteger(massiveSize, 3, "Set the amount of elements in the massive: ");
    readInteger(externalCycles, 1, "Set the value of external fitness test cycles: ");
    readInteger(cyclesCount, 1, "Set the amount of maximum evolution cycles: ");
    readInteger(output, -1, "Would you like to see all output (0 = no, else yes): ");

    std::cout << "Initialization...";

    if (output == 0) isOutput = false;
    else isOutput = true;

    SortingNetworkIndividual best(massiveSize, 20);

    SortingNetworkPopulation sortingNetworks;
    sortingNetworks.setSize(networkPopulationSize);
    sortingNetworks.generatePopulation(massiveSize, 20);
    sortingNetworks.setOutput(isOutput);

    MassivePopulation massives;
    massives.setSize(massivePopulationSize);
    massives.generatePopulation(massiveSize);
    massives.setOutput(isOutput);

    MassivePopulation externalTestMassives;
    externalTestMassives.setSize(massivePopulationSize);
    externalTestMassives.generatePopulation(massiveSize);
    externalTestMassives.setZeroes();
    externalTestMassives = massives;

    SequentialCoevolution coevolution;
    coevolution.setMaxCycles(cyclesCount);

    std::cout << "complete\r\n\r\n";
    std::cout << "Meet the sorting networks population:";
    sortingNetworks.printPopulation();

    std::cout << "Meet the massives population:";
    massives.printPopulation();

    std::cout << "Let the coevolution begin!\r\n";
    std::cout << "\r\n----------------------------------------------------------------------------------------------------------------\r\n";

    clock_t tStart = clock();

    //! coevolution starts here
    do
    {
        coevolution.assertNetworkFitness(sortingNetworks, massives, INTERNAL);
        if ((coevolution.getCurrentCycles() % externalCycles) == 0)
        {
            externalTestMassives = massives;
        }
        coevolution.assertNetworkFitness(sortingNetworks, externalTestMassives, EXTERNAL);
        for (int i = 0; i < sortingNetworks.getSize(); i++)
        {
            if ((best.getExternalFitness() == 0) || (sortingNetworks.getIndividual(i).getExternalFitness() >= best.getExternalFitness()))
            {
                best = sortingNetworks.getIndividual(i);
                bestGeneration = coevolution.getCurrentCycles();
            }
        }
        sortingNetworks.doSort();
        if (isOutput)
        {
            std::cout << "\r\nGeneration " << coevolution.getCurrentCycles() << ":\r\n\r\n";
            std::cout << "Sorting network population: ";
            sortingNetworks.printPopulation();
            std::cout << "Sorting network population breed:";
        }
        sortingNetworks.doBreed();
        sortingNetworks.mutatePopulation();
        coevolution.assertMassiveFitness(massives, sortingNetworks);
        massives.doSort();
        if (isOutput)
        {
            sortingNetworks.printMutation();
            std::cout << "\r\n";
            std::cout << "Massives population: ";
            massives.printPopulation();
            std::cout << "Massives population breed:";
        }
        massives.doBreed();
        massives.mutatePopulation();
        coevolution.setCurrentCycles(coevolution.getCurrentCycles() + 1);
        if (isOutput)
        {
            massives.printMutation();
            std::cout << "\r\n----------------------------------------------------------------------------------------------------------------\r\n";
        }
        else std::cout << ".";

    }
    while((coevolution.getCurrentCycles() <= coevolution.getMaxCycles()) & (best.getExternalFitness() != massives.getSize()));
    //! coevolution ends here
    if (coevolution.getCurrentCycles() > coevolution.getMaxCycles())
    {
        std::cout << "\r\nEvolution time out\r\n";
    }
    std::cout << "And the best sorting network is...\r\n";
    best.printFirstChromosomes();
    std::cout << "\r\n";
    best.printSecondChromosomes();
    std::cout << "\r\nOf " << bestGeneration << " generation\r\n";
    std::cout << "Can sort " << best.getExternalFitness() << " of " << massives.getSize() << " massives\r\n";
    std::cout << "\r\nTime elapsed: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << " s\r\n";
}

void test(std::string testNetwork, std::string testMassive)
{
    //! massive parser begin
    std::regex intrx("-?\\d+");
    std::vector<int> massive;
    std::smatch m;
    while (std::regex_search(testMassive, m, intrx))
    {
        massive.push_back(std::stoi(m.str()));
        testMassive = m.suffix().str();
    }
    //! massive parser end
    MassivePopulation inputMassive;
    inputMassive.setSize(1);
    inputMassive.generatePopulation(massive.size());
    inputMassive.getIndividual(0).setChromosomes(massive);
    std::cout << "Input massive:\r\n";
    for (int i = 0; i < inputMassive.getIndividual(0).getVectorSize(); i++)
    {
        std::cout << inputMassive.getIndividual(0).getSingleChromosome(i) << " ";
    }

    //! network parser begin
    std::vector<std::pair<int, int>> networkParse;
    std::regex noderx("\\d+[-]\\d+");
    intrx = "\\d+";
    std::string node = "";
    int first = 0;
    int second = 0;
    int i = 0;
    int size = 0;
    while (std::regex_search(testNetwork, m, noderx))
    {
        node = m.str();
        testNetwork = m.suffix().str();
        i = 0;
        while(std::regex_search(node, m, intrx))
        {
            if (i != 1) first = std::stoi(m.str());
            else second = std::stoi(m.str());
            node = m.suffix().str();
            i++;
        }
        networkParse.push_back(std::make_pair(first, second));
        size++;
    }
    //! network parser end

    SortingNetworkPopulation inputNetwork;
    inputNetwork.setSize(1);
    inputNetwork.generatePopulation(inputMassive.getIndividual(0).getVectorSize(), size);
    inputNetwork.getIndividual(0).setChromosomes(networkParse);
    std::cout << "\r\n\r\nInput sorting network:\r\n";
    inputNetwork.getIndividual(0).printFirstChromosomes();
    inputNetwork.getIndividual(0).printSecondChromosomes();

    SequentialCoevolution coevolution;
    if (coevolution.testInputNetwork(inputNetwork.getIndividual(0), inputMassive.getIndividual(0)))
    {
        std::cout << "\r\nMassive is sorted! Sorting network won!\r\n";
    }
    else
    {
        std::cout << "\r\nMassive is not sorted. Sorting network lose.\r\n";
    }
}

int main(int argc, char *argv[])
{
    srand (time(NULL));

    int mode = 0;
    readInteger(mode, -1, "Please set the mode: 0 = check mode, else standart coevolution: ");

    if (mode == 0)
    {
        std::string network = "";
        std::string massive = "";
        int i = 0;
        std::ifstream file("input.txt");
        if (file.good())
        {
            for(std::string line; std::getline(file,line); )
            {
                if (i == 0) network = line;
                else massive = line;
                i++;
            }
            test(network, massive);
        }
        else
        {
            std::cout << "\r\nFile does not exists";
        }
        file.close();
    }
    else
    {
        coevolutionAlgorythm();
    }
    std::cout << "\r\n";
    std::system("PAUSE");
}
