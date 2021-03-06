#include <iostream>
#include <cassert>
#include <array>
#include <vector>
#include <bitset>
#include <random>
#include <map>
#include <cstddef>

// testing
#include "UmaTests.h"
#include "VictoriaTests.h"
#include "InvalidMutationTests.h"

// genomes
#include "AbstractGenome.h"
#include "GenomeLite.h"
#include "StephanieGenome.h"
#include "TetianaGenome.h"
#include "TestGenome.h"
#include "UmaGenome.h"

// misc
#include "utilities.h"

// ASSUMES
// GenomeType is defined at compile-time
// ex: g++ -DGenomeType=TestGenome <regular files...>
// or
// cd build; ccmake ../Test; # now choose option using ccmake gui
// or
// cd build; cmake ../Test -DGenomeType=TestGenome

/** main function for running tests **/
int main()
{
    /**     Uma's Testing Suite         **/
    /* Pass in false(0) to just see pass/fail results of all tests.
       Pass in true(1) to see pass/fail results AND debug output of all tests.
       Pass in <GenomeType> based on which genome class you want to test. */
    UmaTests::runAllTests<GenomeType>(0);

    /**     Victoria's Testing Suite         **/
    /* Pass in false(0) to just see pass/fail results of all tests.
       Pass in true(1) to see pass/fail results AND debug output of all tests.
       Pass in <GenomeType> based on which genome class you want to test. */
     VictoriaTests::TestAll<GenomeType>(0);

    /**     Invalid Mutations Test Suite     **/
    /* The tests below test the out of bounds checks in the mutation methods.
       Run each test by itself, not all three together, since each test should exit.
       Pass in <GenomeType> based on which genome class you want to test.
       Pass in true(1) to enable debug mode. */
    InvalidMutationTests::invalidOverwriteTest<GenomeType>(0);
    //InvalidMutationTests::invalidInsertTest<GenomeType>(0);
    //InvalidMutationTests::invalidRemoveTest<GenomeType>(0);

    return(0);
}
