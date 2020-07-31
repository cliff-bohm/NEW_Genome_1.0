/**
 * \file Bench.cpp
 * \author Victoria Cao
 * 
 * \brief Tests for benchmarking genomes.
 * Terminal output is saved to logs folder under GENOMETYPE.log
 **/

#include <ctime>
#include <string>
#include <fstream>
#include <vector>

#include "AbstractGenome.h"
#include "GenomeLite.h"
#include "TestGenome.h"
#include "UmaGenome.h"

#include "benchUtilities.h"

#define CATCH_CONFIG_MAIN 
#define CATCH_CONFIG_ENABLE_BENCHMARKING

#include "catch.hpp"

// Variables
#define MutationRate 0.005     //< any mutation rate <= 0.02
#define Size 75000    //< 500,000 ; 250,000 ; 100,000 ; 75,000, 50,000, 20,000 ; 5,000 avaliable 

typedef std::byte Byte;
typedef TestGenome GenomeType;  //< change to genomeType

std::string name = typeid(GenomeType).name();  
const std::vector<size_t> mutations = randomList(Size, MutationRate);


/*********************************************************************************
 * 
 *                                  TESTING
 * 
 ********************************************************************************/
// TEST_CASE("Resize Benchmarks", "[benchmark]") 
// {
//     std::string file = "logs/"+name+".log";
//     freopen(file.c_str(), "a", stdout);

//     // initializing mutation list 
//     size_t newSize = Size+(Size/10);

//     // Nested Insertion
//     std::cout << "BENCHING: Resize" << std::endl;
//     printTime();
//     std::cout << "\n" << name << ": \nSize\t" << Size << "\nNew Size\t" << newSize << std::endl;  

//     BENCHMARK("Resize") 
//     {
//         AbstractGenome* genome = new GenomeType(Size);

//         genome->resize(newSize);

//         delete genome;
//     };

// } 

// TEST_CASE("Clone Construction Benchmarks", "[benchmark]") 
// {
//     std::string file = "logs/"+name+".log";
//     freopen(file.c_str(), "a", stdout);

//     // Apply multi mutations to genome
//     AbstractGenome* genome = new GenomeType(Size);

//     for (size_t i(0); i < mutations.size(); i++)
//     {
//         if (i%3 == 0)
//             genome->overwrite(mutations[i], std::vector< Byte >(1, (Byte)1));
//         else if (i%3 == 1)
//             genome->insert(mutations[i], std::vector< Byte >(1, (Byte)1));   
//         else
//             genome->remove(mutations[i], 1);
//     }

//     size_t childNum = 100;

//     // Nested Insertion
//     std::cout << "BENCHING: Clone" << std::endl;
//     printTime();
//     std::cout << "\n" << name << ": \nSize\t" << Size << "\nChildren\t" << childNum << std::endl;  

//     BENCHMARK("Clone Constructor") 
//     {
//         std::vector<AbstractGenome*> children;
//         children.reserve(childNum);

//         for (size_t i(0); i < childNum; ++i)
//         {
//             children.push_back(genome->clone(0));
//         }

//         for (size_t i(0); i < childNum; i++)
//         {
//             delete children[i];
//         }
//     };

//      BENCHMARK("Force Clone Constructor") 
//     {        
//         std::vector<AbstractGenome*> children;
//         children.reserve(childNum);

//         for (size_t i(0); i < childNum; ++i)
//         {
//             children.push_back(genome->clone(1));
//         }

//         for (size_t i(0); i < childNum; i++)
//         {
//             delete children[i];
//         }
//     }; 

//     delete genome; 
// } 


TEST_CASE("Overwrite Benchmarks", "[benchmark]") 
{
    std::string file = "logs/"+name+".log";
    freopen(file.c_str(), "a", stdout);

    // Nested Insertion
    std::cout << "BENCHING: Overwrites" << std::endl;
    printTime();
    std::cout << "\n" << name << ": \nSize\t" << Size << "\nMutations\t" << mutations.size() << std::endl;  
    
    // BENCHMARK("Whole Genome Overwrite") 
    // {
    //     AbstractGenome* genome = new GenomeType(Size);

    //     genome->overwrite(0, std::vector<Byte>(Size, (Byte)0));

    //     delete genome;
    // }; 

    std::cout << "\n" << name << ": \nSize\t" << Size << "\nMutations\t" << mutations.size() << "\nMutation Rate\t" << MutationRate << std::endl;  
    BENCHMARK("Random Overwrites") 
    {
        AbstractGenome* genome = new GenomeType(Size);

        for (const auto& site : mutations)
        {
            genome->overwrite(site, std::vector< Byte >(1, (Byte)1));
        }

        delete genome;
    };

    

}


TEST_CASE("Insertion Benchmarks", "[benchmark]") 
{
    std::string file = "logs/"+name+".log";
    freopen(file.c_str(), "a", stdout);

    // Nested Insertion
    std::cout << "BENCHING: Insertion" << std::endl;
    printTime();
    std::cout << "\n" << name << ": \nSize\t" << Size << "\nMutations\t" << mutations.size() << "\nMutation Rate\t"  <<MutationRate <<  std::endl;  

    BENCHMARK("Random Insertion") 
    {
        AbstractGenome* genome = new GenomeType(Size);

        for (const auto& site : mutations)
        {
            genome->insert(site, std::vector< Byte >(1, (Byte)1));
        }

        delete genome;
    };

}


TEST_CASE("Deletion Benchmarks", "[benchmark]") 
{
    std::string file = "logs/"+name+".log";
    freopen(file.c_str(), "a", stdout);

    // Nested Insertion
    std::cout << "BENCHING: Deletion" << std::endl;
    printTime();
    std::cout << "\n" << name << ": \nSize\t" << Size << "\nMutations\t" << mutations.size() << "\nMutation Rate\t" << MutationRate << std::endl;  

    BENCHMARK("Random Deletion") 
    {
        AbstractGenome* genome = new GenomeType(Size);

        for (size_t i(0); i < mutations.size(); i++)
        {
            genome->remove(mutations[i]%(Size-i-1), 1);
        }

        delete genome;
    };

}


TEST_CASE("Multi-Mutation Benchmarks", "[benchmark]") 
{
    std::string file = "logs/"+name+".log";
    freopen(file.c_str(), "a", stdout);

    // Nested Insertion
    std::cout << "BENCHING: Multi-Mutation" << std::endl;
    printTime();
    std::cout << "\n" << name << ": \nSize\t" << Size << "\nMutations\t" << mutations.size() << "\nMutation Rate\t" << MutationRate << std::endl;  

    BENCHMARK("Random Multi-Mutation") 
    {
        AbstractGenome* genome = new GenomeType(Size);

        for (size_t i(0); i < mutations.size(); i++)
        {
            if (i%3 == 0)
                genome->overwrite(mutations[i], std::vector< Byte >(1, (Byte)1));

            else if (i%3 == 1)
                genome->insert(mutations[i], std::vector< Byte >(1, (Byte)1));
            
            else
                genome->remove(mutations[i], 1);
        }

        delete genome;
    };

}




TEST_CASE("Clone Mutation Benchmarks", "[benchmark]") 
{
    std::string file = "logs/"+name+".log";
    freopen(file.c_str(), "a", stdout);

    // Nested Insertion
    std::cout << "BENCHING: Clone" << std::endl;
    printTime();
    // std::cout << "\n" << name << ": \nSize\t" << Size << "\nMutations\t" << mutations.size() << "\nMutation Rate\t" << MutationRate << std::endl;  

 
    /** BENCHMARK("Single Clone Mutation") 
    {
        AbstractGenome* genome = new GenomeType(Size);

        AbstractGenome* child = genome->clone();

        // apply mutation
        for (size_t i(0); i < mutations.size(); i++)
        {
            if (i%3 == 0)
                child->overwrite(mutations[i], std::vector< Byte >(1, (Byte)1));

            else if (i%3 == 1)
                child->insert(mutations[i], std::vector< Byte >(1, (Byte)1));
            
            else
                child->remove(mutations[i]%(Size-i-1), 1);
        }

        delete genome;
        delete child;
    }; **/


    size_t childNum = 100;
    std::cout << "\n" << name << ": \nSize\t" << Size << "\nMutations\t" << mutations.size() << "\nMutation Rate\t" << MutationRate << "\nChildren\t" << childNum << std::endl;  

    BENCHMARK("Multiple Clone Mutation") 
    {
        AbstractGenome* genome = new GenomeType(Size);

        std::vector<AbstractGenome*> children;
        children.reserve(childNum);

        // clone and apply mutation
        for (size_t i(0); i < childNum; ++i)
        {
            children.push_back(genome->clone());
            auto currGenome = children.back();

            // apply mutation
            for (size_t i(0); i < mutations.size(); i++)
            {
                if (i%3 == 0)
                    currGenome->overwrite(mutations[i], std::vector< Byte >(1, (Byte)1));

                else if (i%3 == 1)
                    currGenome->insert(mutations[i], std::vector< Byte >(1, (Byte)1));
                
                else
                    currGenome->remove(mutations[i]%(Size-i-1), 1);
            }
        }

        // delete children
        for (size_t i(0); i < childNum; i++)
        {
            delete children[i];
        }

        delete genome;
    };

    size_t generations = 5;
    childNum = 10;
    std::cout << "\n" << name << ": \nSize\t" << Size << "\nMutations\t" << mutations.size() << "\nMutation Rate\t" << MutationRate << "\nChildren\t" << childNum << "\nGenerations\t" << generations << std::endl;  
    
    BENCHMARK("Generation Clone Mutation") 
    {
        std::vector<AbstractGenome*> children;
        children.reserve(childNum+1);

        AbstractGenome* genome = new GenomeType(Size);

        children.push_back(genome);

        for (size_t gen(0); gen < generations; ++gen)
        {
            // create population loop
            for (size_t i(0); i < childNum; ++i)
            {
                children.push_back(children[0]->clone(0));
                auto currGenome = children.back();

                // apply mutation
                for (size_t i(0); i < mutations.size(); i++)
                {
                    if (i%3 == 0)
                        currGenome->overwrite(mutations[i], std::vector< Byte >(1, (Byte)1));

                    else if (i%3 == 1)
                        currGenome->insert(mutations[i], std::vector< Byte >(1, (Byte)1));
                    
                    else
                        currGenome->remove(mutations[i]%(Size-i-1), 1);
                }
            }

            std::swap(children[0],children[1]);

            // delete children
            for (size_t i(1); i < childNum+1; i++)
            {
                delete children[i];
            }
            children.resize(1);
        }

        delete children[0];
    };

    
    /** BENCHMARK("Generation Clone Mutation, Force Copy") 
    {
        std::vector<AbstractGenome*> children;
        children.reserve(childNum+1);

        AbstractGenome* genome = new GenomeType(Size);

        children.push_back(genome);

        for (size_t gen(0); gen < generations; ++gen)
        {
            // create population loop
            for (size_t i(0); i < childNum; ++i)
            {
                children.push_back(children[0]->clone(1));
                auto currGenome = children.back();

                // apply mutation
                for (size_t i(0); i < mutations.size(); i++)
                {
                    if (i%3 == 0)
                        currGenome->overwrite(mutations[i], std::vector< Byte >(1, (Byte)1));

                    else if (i%3 == 1)
                        currGenome->insert(mutations[i], std::vector< Byte >(1, (Byte)1));
                    
                    else
                        currGenome->remove(mutations[i]%(Size-i-1), 1);
                }
            }

            std::swap(children[0],children[1]);

            // delete children
            for (size_t i(1); i < childNum+1; i++)
            {
                delete children[i];
            }
            children.resize(1);
        }

        delete children[0];
    }; **/
}


