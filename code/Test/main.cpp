// stl library
#include <iostream>
#include <cassert>
#include <array>
#include <vector>
#include <bitset>
#include <random>
#include <map>
#include <cstddef>

// testing
#include "UmaChangelogTests.h"
#include "VictoriaTests.h"

// genomes
#include "AbstractGenome.h"
#include "TestGenome.h"
#include "GenomeLite.h"

// misc
#include "utilities.h"


/** main function for running tests **/
int main() 
{
    /**     Uma's Testing Suite         **/
    // pass in 0 to just see pass/fail results of all tests
    // pass in 1 to see pass/fail results AND debug output of all tests
    // pass in <GenomeName> based on which genome class you want to test
    // runUmaChangelogTests<GenomeLite>(0);
    // runAllStressTests<GenomeLite>(0);

    /**     Victoria's Testing Suite         **/
    // pass in 0 to just see pass/fail results of all tests
    // pass in 1 to see pass/fail results AND debug output of all tests
    // pass in <GenomeName> based on which genome class you want to test
     VictoriaTests::TestAll<GenomeLite>(0);

    return(0);
}