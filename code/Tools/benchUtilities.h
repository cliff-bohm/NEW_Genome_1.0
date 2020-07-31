/**
 * \file Bench.cpp
 * \author Victoria Cao
 * 
 * \brief Tests for benchmarking genomes.
 * Terminal output is saved to bench.log
 * 
 **/

#include <ctime>
#include <unistd.h>

#include <vector>

#include <iostream>
#include <fstream>
#include <string>


/** 
 * gets current directory
 * \returns current working directory 
 **/
std::string currentDir() {
   char buff[FILENAME_MAX]; //create string buffer to hold path
   getcwd( buff, FILENAME_MAX );
   std::string current_working_dir(buff);
   return current_working_dir;
}

/**
 * prints current time
 **/
void printTime() {
    time_t t = time(0); 
    struct tm * timeStruct = localtime(&t);
    std::cout << (timeStruct->tm_year) << '-' << (timeStruct->tm_mon) << '-'<<  (timeStruct->tm_mday);
    std::cout << "\t" << (timeStruct->tm_hour) << ":" << (timeStruct->tm_min) << ":" << (timeStruct->tm_sec) <<  std::endl;
}

/**
 * Creates random list from sequences file
 * \param size of genome
 * \returns vector of predetermined random numbers 
 **/
std::vector<size_t> randomList(size_t size, double rate=0.01)
{
    // Abort if larger than 0.01 mutation rate
    if (rate > 0.02)
    {
        std::cout << "Error: Mutation rate larger than 0.02" << std::endl;
        exit(1);
    }

    // init vector
    std::vector<size_t> randomList;
    randomList.reserve((double)size*rate);
    
    // open file
    std::string file = currentDir()+"/../Tools/Sequences/"+std::to_string(size)+"List.txt";
    std::ifstream infile(file.c_str());
    
    // get random numbers
    size_t num;
    while (infile >> num)
    {
        randomList.push_back(num);
        if (randomList.size()+1 > randomList.capacity())
            break;
    }
    
    infile.close();

    return randomList;
}