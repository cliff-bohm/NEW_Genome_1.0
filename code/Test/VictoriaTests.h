/**
 * \file VictoriaTests.h
 * \author Victoria Cao
 * 
 * \brief namespace for testing genome functions
 **/

#pragma once
#include <cassert>
#include <iostream>
#include <string>

#include "../AbstractGenome.h"
#include "../GenomeLite/GenomeLite.h"

typedef std::byte Byte; // c++17 Byte doesn't always work

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */


/** handler testing functions **/
namespace VictoriaTests
{

    /*******************************************************
     * 
     *          CONSTRUCTOR TESTS
     * 
     ******************************************************/

    /**
     * Tests constructor 50
     **/
    template <class genomeName>
    void TestConstructor50(bool debug)
    {
        // test size 50
        size_t size = 50;
        AbstractGenome* genome = new genomeName(size);

        if (debug)
            genome->show();

        assert(genome->size() == size);
        std::cout << "Test Constructor " << size << ": " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
    }

    /**
     * Tests constructor 5000
     **/
    template <class genomeName>
    void TestConstructor5000(bool debug)
    {
        // test size 5000
        size_t size = 5000;
        AbstractGenome* genome = new genomeName(size);

        if (debug)
            genome->show();

        assert(genome->size() == size);
        std::cout << "Test Constructor " << size << ": " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
    }

    /**
     * Tests constructor 500000
     **/
    template <class genomeName>
    void TestConstructor500000(bool debug)
    {
        // test size 500000
        size_t size = 500000;
        AbstractGenome* genome = new genomeName(size);

        if (debug)
            genome->show();

        assert(genome->size() == size);
        std::cout << "Test Constructor " << size << ": " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
    }

    /**
     * Tests cloning functions for making population
     **/
    template <class genomeName>
    void TestConstructor(bool debug)
    {
        std::cout << "\n" BOLDWHITE "Running " BOLDMAGENTA "CONSTRUCTOR TESTS " BOLDWHITE " for " BOLDMAGENTA << typeid(genomeName).name() << RESET << std::endl;   

        TestConstructor50<genomeName>(debug);
        TestConstructor5000<genomeName>(debug);
        TestConstructor500000<genomeName>(debug);
    }


    /*******************************************************
     * 
     *          OVERWRITE TESTS
     * 
     ******************************************************/


    /*******************************************************
     *          OVERWRITE ALL TESTS
     ******************************************************/

    /**
     * Tests overwriting the whole genome size 50
     **/
    template <class genomeName>
    void TestOverwriteAll50(bool debug)
    {
        // test size 50
        size_t size = 50;
        AbstractGenome* genome = new genomeName(size);

        genome->overwrite(0, std::vector<Byte>(size, (Byte)10));

        if (debug)
            genome->show();

        // assertions
        for (size_t i(0); i < size; i++)
        {
            assert(*(genome->data(i, 1)) == (Byte)10);
        }
        assert(genome->size() == size);

        std::cout << "Test Overwrite All " << size << ": " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
    }

    /**
     * Tests overwriting the whole genome size 5000
     **/
    template <class genomeName>
    void TestOverwriteAll5000(bool debug)
    {
        // test size 5000
        size_t size = 5000;
        AbstractGenome* genome = new genomeName(size);

        genome->overwrite(0, std::vector<Byte>(size, (Byte)10));

        if (debug)
            genome->show();

        // assertions
        for (size_t i(4001); i < size; i++)
        {
            assert(*(genome->data(i, 1)) == (Byte)10);
        }
        assert(genome->size() == size);

        std::cout << "Test Overwrite All " << size << ": " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
    }

    /**
     * Tests overwriting the whole genome size 500000
     **/
    template <class genomeName>
    void TestOverwriteAll500000(bool debug)
    {
        // test size 500000
        size_t size = 500000;
        AbstractGenome* genome = new genomeName(size);

        genome->overwrite(0, std::vector<Byte>(size, (Byte)10));

        if (debug)
            genome->show();

        // assertions
        for (size_t i(0); i < size; i++)
        {
            if (*(genome->data(i, 1)) != (Byte)10)
                std::cout << i << std::endl;
            assert(*(genome->data(i, 1)) == (Byte)10);
        }
        assert(genome->size() == size);

        std::cout << "Test Overwrite All " << size << ": " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
    }

    /**
     * Tests overwriting the whole genome
     **/
    template <class genomeName>
    void TestOverwriteAll(bool debug)
    {
        std::cout << "\n" BOLDWHITE "Running " BOLDMAGENTA "OVERWRITE ALL TESTS " BOLDWHITE " for " BOLDMAGENTA << typeid(genomeName).name() << RESET << std::endl;   

        TestOverwriteAll50<genomeName>(debug);
        TestOverwriteAll5000<genomeName>(debug);
        TestOverwriteAll500000<genomeName>(debug);
    }


    /*******************************************************
     *          OVERWRITE PART TESTS
     ******************************************************/

    /**
     * Tests overwriting the whole genome size 50
     **/
    template <class genomeName>
    void TestOverwriteFront(bool debug)
    {
        // test size 50
        size_t size = 50;
        AbstractGenome* genome = new genomeName(size);

        genome->overwrite(0, std::vector<Byte>(10, (Byte)10));

        if (debug)
            genome->show();

        // assertions
        for (size_t i(0); i < size; i++)
        {
            if (i < 10)
                assert(*(genome->data(i, 1)) == (Byte)10);
            else
                assert(*(genome->data(i, 1)) != (Byte)10);
            
        }
        assert(genome->size() == size);

        std::cout << "Test Overwrite Front: " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
    }


    /**
     * Tests overwriting the whole genome size 50
     **/
    template <class genomeName>
    void TestOverwriteMiddle(bool debug)
    {
        // test size 5000
        size_t size = 5000;
        AbstractGenome* genome = new genomeName(size);

        genome->overwrite(2950, std::vector<Byte>(100, (Byte)10));

        if (debug)
            genome->show();

        // assertions
        for (size_t i(0); i < size; i++)
        {
            if (i >= 2950 && i < 3050)
                assert(*(genome->data(i, 1)) == (Byte)10);
            else
                assert(*(genome->data(i, 1)) != (Byte)10);
            
        }
        assert(genome->size() == size);

        std::cout << "Test Overwrite Middle: " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
    }


    /**
     * Tests overwriting the whole genome size 50
     **/
    template <class genomeName>
    void TestOverwriteBack(bool debug)
    {
        // test size 50
        size_t size = 50;
        AbstractGenome* genome = new genomeName(size);

        genome->overwrite(40, std::vector<Byte>(10, (Byte)10));

        if (debug)
            genome->show();

        // assertions
        for (size_t i(0); i < size; i++)
        {
            if (i >= 40)
                assert(*(genome->data(i, 1)) == (Byte)10);
            else
                assert(*(genome->data(i, 1)) != (Byte)10);
            
        }
        assert(genome->size() == size);

        std::cout << "Test Overwrite Back: " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
    }


    /**
     * Tests overwriting the whole genome
     **/
    template <class genomeName>
    void TestOverwritePart(bool debug)
    {
        std::cout << "\n" BOLDWHITE "Running " BOLDMAGENTA "OVERWRITE PART TESTS " BOLDWHITE " for " BOLDMAGENTA << typeid(genomeName).name() << RESET << std::endl;   

        TestOverwriteFront<genomeName>(debug);
        TestOverwriteMiddle<genomeName>(debug);
        TestOverwriteBack<genomeName>(debug);
    }


    /*******************************************************
     *          OVERWRITE POINT TESTS
     ******************************************************/
 
    /**
     * Tests overwriting the whole genome size 50
     **/
    template <class genomeName>
    void TestOverwritePointSmall(bool debug)
    {
        // test size 10
        size_t size = 10;
        AbstractGenome* genome = new genomeName(size);

        genome->overwrite(0, std::vector<Byte>({(Byte)4,(Byte)3,(Byte)2,(Byte)0,(Byte)1,(Byte)2,(Byte)4,(Byte)3,(Byte)1,(Byte)0}));
        genome->overwrite(1, std::vector<Byte>({(Byte)(4)}));
        genome->overwrite(7, std::vector<Byte>({(Byte)(2)}));
        genome->overwrite(3, std::vector<Byte>({(Byte)(4)}));

        if (debug)
            genome->show();

        std::vector<Byte> compare({(Byte)4,(Byte)4,(Byte)2,(Byte)4,(Byte)1,(Byte)2,(Byte)4,(Byte)2,(Byte)1,(Byte)0});
        for (size_t i(0); i < size; i++)
        {
            assert(*(genome->data(i, 1)) == compare[i]);
        }
        assert(genome->size() == size);

        std::cout << "Test Overwrite Point Small Genome: " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
    }


    /**
     * Tests overwriting the whole genome size 50
     **/
    template <class genomeName>
    void TestOverwritePointLarge(bool debug)
    {
        // test size 5000
        size_t size = 5000;
        AbstractGenome* genome = new genomeName(size);

        genome->overwrite(0, std::vector<Byte>(size, (Byte)0));
        genome->overwrite(0, std::vector<Byte>(1, (Byte)1));
        genome->overwrite(10, std::vector<Byte>(1, (Byte)2));
        genome->overwrite(2999, std::vector<Byte>(1, (Byte)3));
        genome->overwrite(4999, std::vector<Byte>(1, (Byte)4));

        if (debug)
            genome->show();

        // assertions
        for (size_t i(2999); i < size; i++)
        {
            if (i == 0)
                assert(*(genome->data(i, 1)) == (Byte)1);
            else if (i == 10)
                assert(*(genome->data(i, 1)) == (Byte)2);
            else if (i == 2999)
                assert(*(genome->data(i, 1)) == (Byte)3);
            else if (i == 4999)
                assert(*(genome->data(i, 1)) == (Byte)4);
            else
                assert(*(genome->data(i, 1)) == (Byte)0);       
        }
        assert(genome->size() == size);

        genome->overwrite(0, std::vector<Byte>(1, (Byte)5));
        genome->overwrite(10, std::vector<Byte>(1, (Byte)6));
        genome->overwrite(2999, std::vector<Byte>(1, (Byte)7));
        genome->overwrite(4999, std::vector<Byte>(1, (Byte)8));

        if (debug)
            genome->show();

        // assertions
        for (size_t i(0); i < size; i++)
        {
            if (i == 0)
                assert(*(genome->data(i, 1)) == (Byte)5);
            else if (i == 10)
                assert(*(genome->data(i, 1)) == (Byte)6);
            else if (i == 2999)
                assert(*(genome->data(i, 1)) == (Byte)7);
            else if (i == 4999)
                assert(*(genome->data(i, 1)) == (Byte)8);
            else
                assert(*(genome->data(i, 1)) == (Byte)0);       
        }
        assert(genome->size() == size);

        std::cout << "Test Overwrite Point Large Genome: " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
    }


    /*******************************************************
     *          RUN OVERWRITE TESTS
     ******************************************************/

    /**
     * Tests all of the overwrite functions
     **/
    template <class genomeName>
    void TestOverwrite(bool debug)
    {
        TestOverwriteAll<genomeName>(debug);
        TestOverwritePart<genomeName>(debug);
        TestOverwritePointSmall<genomeName>(debug);
        TestOverwritePointLarge<genomeName>(debug);
    }

 
    /*******************************************************
     * 
     *          INSERT TESTS
     * 
     ******************************************************/

    /*******************************************************
     *          INSERT TESTS
     ******************************************************/

    /**
     * Tests inserting the whole genome size 50
     **/
    template <class genomeName>
    void TestInsertFront(bool debug)
    {
        // test size 50
        size_t size = 50;
        AbstractGenome* genome = new genomeName(size);

        genome->insert(0, std::vector<Byte>(10, (Byte)10));

        if (debug)
            genome->show();

        // assertions
        for (size_t i(0); i < genome->size(); i++)
        {
            if (i < 10)
                assert(*(genome->data(i, 1)) == (Byte)10);
            else
                assert(*(genome->data(i, 1)) != (Byte)10);      
        }
        assert(genome->size() == size+10);

        std::cout << "Test Insert Front: " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
    }


    /**
     * Tests inserting the whole genome size 50
     **/
    template <class genomeName>
    void TestInsertMiddle(bool debug)
    {
        // test size 5000
        size_t size = 5000;
        AbstractGenome* genome = new genomeName(size);

        genome->insert(2999, std::vector<Byte>(100, (Byte)10));

        if (debug)
            genome->show();

        // assertions
        for (size_t i(0); i < genome->size(); i++)
        {
            if (i >= 2999 && i < 3099)
                assert(*(genome->data(i, 1)) == (Byte)10);
            else
                assert(*(genome->data(i, 1)) != (Byte)10);
            
        }
        assert(genome->size() == size+100);

        std::cout << "Test Insert Middle: " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
    }


    /**
     * Tests inserting the whole genome size 50
     **/
    template <class genomeName>
    void TestInsertBack(bool debug)
    {
        // test size 50
        size_t size = 50;
        AbstractGenome* genome = new genomeName(size);

        genome->insert(50, std::vector<Byte>(10, (Byte)10));

        if (debug)
            genome->show();

        // assertions
        for (size_t i(0); i < size; i++)
        {
            if (i >= 50)
                assert(*(genome->data(i, 1)) == (Byte)10);
            else
                assert(*(genome->data(i, 1)) != (Byte)10);
            
        }
        assert(genome->size() == size+10);

        std::cout << "Test Insert Back: " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
    }


    /**
     * Tests inserting the whole genome size 50
     **/
    template <class genomeName>
    void TestInsertNested(bool debug)
    {
        // test size 50
        size_t size = 50;
        AbstractGenome* genome = new genomeName(size);

        genome->overwrite(0, std::vector<Byte>(size, (Byte)0));

        for (size_t i(0); i < 10; i++)
            genome->insert(i, std::vector<Byte>(2, (Byte)i));

        if (debug)
            genome->show();

        // assertions
        for (size_t i(0); i < genome->size(); i++)
        {
            if (i < 10)
                assert(*(genome->data(i, 1)) == (Byte)i);
            else if (i < 20)
                assert(*(genome->data(i, 1)) == (Byte)(9-(i%10)));
            else
                assert(*(genome->data(i, 1)) == (Byte)0);
            
        }
        assert(genome->size() == size+20);

        std::cout << "Test Insert Nested: " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
    }


    /**
     * Tests cloning functions for making population
     **/
    template <class genomeName>
    void TestInsert(bool debug)
    {
        std::cout << "\n" BOLDWHITE "Running " BOLDMAGENTA "INSERT TESTS " BOLDWHITE " for " BOLDMAGENTA << typeid(genomeName).name() << RESET << std::endl;   

        TestInsertFront<genomeName>(debug);
        TestInsertMiddle<genomeName>(debug);
        TestInsertBack<genomeName>(debug);
        TestInsertNested<genomeName>(debug);
    }


    /*******************************************************
     * 
     *          DELETE TESTS
     * 
     ******************************************************/


    /**
     * Tests inserting the whole genome size 50
     **/
    template <class genomeName>
    void TestDeleteFront(bool debug)
    {
        // test size 50
        size_t size = 50;
        AbstractGenome* genome = new genomeName(size);

        for (size_t i(0); i < genome->size(); i++)
        {
            *(genome->data(i, 1)) = (Byte)i;
        }

        genome->remove(0, 10);

        if (debug)
            genome->show();

        // assertions
        for (size_t i(0); i < genome->size(); i++)
        {
            assert(*(genome->data(i, 1)) == (Byte)(i+10));
        }
        assert(genome->size() == size-10);

        std::cout << "Test Delete Front: " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
    }


    /**
     * Tests inserting the whole genome size 50
     **/
    template <class genomeName>
    void TestDeleteMiddle(bool debug)
    {
        // test size 5000
        size_t size = 5000;
        AbstractGenome* genome = new genomeName(size);

        for (size_t i(0); i < genome->size(); i++)
        {
            *(genome->data(i, 1)) = (Byte)i;
        }

        genome->remove(2999, 100);

        if (debug)
            genome->show();

        // assertions
        for (size_t i(0); i < genome->size(); i++)
        {
            if (i < 2999)
                assert(*(genome->data(i, 1)) == (Byte)i);
            else
                assert(*(genome->data(i, 1)) == (Byte)(i+100));
            
        }
        assert(genome->size() == size-100);

        std::cout << "Test Delete Middle: " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
    }


    /**
     * Tests inserting the whole genome size 50
     **/
    template <class genomeName>
    void TestDeleteBack(bool debug)
    {
         // test size 5000
        size_t size = 5000;
        AbstractGenome* genome = new genomeName(size);

        for (size_t i(0); i < genome->size(); i++)
        {
            *(genome->data(i, 1)) = (Byte)i;
        }
        
        genome->remove(4900, 100);

        if (debug)
            genome->show();

        // assertions
        for (size_t i(0); i < genome->size(); i++)
        {
            assert(*(genome->data(i, 1)) == (Byte)i);    
        }

        assert(genome->size() == size-100);

        std::cout << "Test Delete Middle: " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
    }


    /**
     * Tests Delete function
     **/
    template <class genomeName>
    void TestDelete(bool debug)
    {
        std::cout << "\n" BOLDWHITE "Running " BOLDMAGENTA "DELETE TESTS " BOLDWHITE " for " BOLDMAGENTA << typeid(genomeName).name() << RESET << std::endl;   

        TestDeleteFront<genomeName>(debug);
        TestDeleteMiddle<genomeName>(debug);
        TestDeleteBack<genomeName>(debug);
    }


    /*******************************************************
     * 
     *          MULTI MUTATION TESTS
     * 
     ******************************************************

    /**
     * Tests inserting the whole genome size 50
     **/
    template <class genomeName>
    void TestOverwriteDelete(bool debug)
    {
        // test size 50
        size_t size = 50;
        AbstractGenome* genome = new genomeName(size);

        for (size_t i(0); i < genome->size(); i++)
        {
            *(genome->data(i, 1)) = (Byte)i;
        }

        genome->overwrite(20, std::vector<Byte>(10, (Byte)99));
        genome->remove(22, 6);

        if (debug)
            genome->show();

        // assertions
        for (size_t i(0); i < genome->size(); i++)
        {
            if (i < 20)
                assert(*(genome->data(i, 1)) == (Byte)i);
            else if (i >= 20 && i < 24)
                assert(*(genome->data(i, 1)) == (Byte)99);
            else
                assert(*(genome->data(i, 1)) == (Byte)(i+6));
        }
        assert(genome->size() == size-6);

        std::cout << "Test Overwrite Delete: " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
    }


    /**
     * Tests inserting the whole genome size 50
     **/
    template <class genomeName>
    void TestOverwriteInsert(bool debug)
    {
         // test size 50
        size_t size = 50;
        AbstractGenome* genome = new genomeName(size);

        for (size_t i(0); i < genome->size(); i++)
        {
            *(genome->data(i, 1)) = (Byte)i;
        }

        genome->overwrite(20, std::vector<Byte>(10, (Byte)99));
        genome->insert(24, std::vector<Byte>(10, (Byte)0));

        if (debug)
            genome->show();

        // assertions
        for (size_t i(0); i < genome->size(); i++)
        {
            if (i < 20)
                assert(*(genome->data(i, 1)) == (Byte)i);
            else if ((i >= 20 && i < 24) || (i >= 34 && i < 40))
                assert(*(genome->data(i, 1)) == (Byte)99);
            else if (i >= 24 && i < 34)
                assert(*(genome->data(i, 1)) == (Byte)0);
            else
                assert(*(genome->data(i, 1)) == (Byte)(i-10));
        }
        assert(genome->size() == size+10);

        std::cout << "Test Overwrite Insert: " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
    }


    /**
     * Tests inserting the whole genome size 50
     **/
    template <class genomeName>
    void TestInsertOverwrite(bool debug)
    {
        // test size 50
        size_t size = 50;
        AbstractGenome* genome = new genomeName(size);

        for (size_t i(0); i < genome->size(); i++)
        {
            *(genome->data(i, 1)) = (Byte)i;
        }

        genome->insert(20, std::vector<Byte>(10, (Byte)0));
        genome->overwrite(22, std::vector<Byte>(5, (Byte)99));


        if (debug)
            genome->show();

        // assertions
        for (size_t i(0); i < genome->size(); i++)
        {
            if (i < 20)
                assert(*(genome->data(i, 1)) == (Byte)i);
            else if ((i >= 20 && i < 22) || (i >= 27 && i < 30))
                assert(*(genome->data(i, 1)) == (Byte)0);
            else if (i >= 22 && i < 27)
                assert(*(genome->data(i, 1)) == (Byte)99);
            else
                assert(*(genome->data(i, 1)) == (Byte)(i-10));
        }
        assert(genome->size() == size+10);

        std::cout << "Test Insert Overwrite: " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
    }


    /**
     * Tests inserting the whole genome size 50
     **/
    template <class genomeName>
    void TestInsertDelete(bool debug)
    {
        // test size 50
        size_t size = 50;
        AbstractGenome* genome = new genomeName(size);

        for (size_t i(0); i < genome->size(); i++)
        {
            *(genome->data(i, 1)) = (Byte)i;
        }

        genome->insert(20, std::vector<Byte>(10, (Byte)0));
        genome->remove(22, 5);


        if (debug)
            genome->show();

        // assertions
        for (size_t i(0); i < genome->size(); i++)
        {
            if (i < 20)
                assert(*(genome->data(i, 1)) == (Byte)i);
            else if (i >= 20 && i < 25)
                assert(*(genome->data(i, 1)) == (Byte)0);
            else
                assert(*(genome->data(i, 1)) == (Byte)(i-5));
        }
        assert(genome->size() == size+5);

        std::cout << "Test Insert Delete: " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
    }


    /**
     * Tests inserting the whole genome size 50
     **/
    template <class genomeName>
    void TestDeleteOverwrite(bool debug)
    {
          // test size 50
        size_t size = 50;
        AbstractGenome* genome = new genomeName(size);

        for (size_t i(0); i < genome->size(); i++)
        {
            *(genome->data(i, 1)) = (Byte)i;
        }

        genome->remove(20, 10);
        genome->overwrite(15, std::vector<Byte>(10, (Byte)99));


        if (debug)
            genome->show();

        // assertions
        for (size_t i(0); i < genome->size(); i++)
        {
            if (i < 15)
                assert(*(genome->data(i, 1)) == (Byte)i);
            else if (i >= 15 && i < 25)
                assert(*(genome->data(i, 1)) == (Byte)99);
            else
                assert(*(genome->data(i, 1)) == (Byte)(i+10));
        }
        assert(genome->size() == size-10);

        std::cout << "Test Delete Overwrite: " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
    }


    /**
     * Tests inserting the whole genome size 50
     **/
    template <class genomeName>
    void TestDeleteInsert(bool debug)
    {
        // test size 50
        size_t size = 50;
        AbstractGenome* genome = new genomeName(size);

        for (size_t i(0); i < genome->size(); i++)
        {
            *(genome->data(i, 1)) = (Byte)i;
        }

        genome->remove(20, 10);
        genome->insert(20, std::vector<Byte>(10, (Byte)99));


        if (debug)
            genome->show();

        // assertions
        for (size_t i(0); i < genome->size(); i++)
        {
            if (i < 20)
                assert(*(genome->data(i, 1)) == (Byte)i);
            else if (i >= 20 && i < 30)
                assert(*(genome->data(i, 1)) == (Byte)99);
            else
                assert(*(genome->data(i, 1)) == (Byte)i);
        }
        assert(genome->size() == size);

        std::cout << "Test Delete Insert: " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
    }


    /**
     * Tests inserting the whole genome size 50
     **/
    template <class genomeName>
    void TestAllMutation1(bool debug)
    {
        // test size 50
        size_t size = 50;
        AbstractGenome* genome = new genomeName(size);

        for (size_t i(0); i < genome->size(); i++)
        {
            *(genome->data(i, 1)) = (Byte)i;
        }

        genome->remove(20, 10);
        genome->insert(20, std::vector<Byte>(10, (Byte)99));
        genome->overwrite(22, std::vector<Byte>(10, (Byte)0));


        if (debug)
            genome->show();

        // assertions
        for (size_t i(0); i < genome->size(); i++)
        {
            if (i < 20)
                assert(*(genome->data(i, 1)) == (Byte)i);
            else if (i >= 20 && i < 22)
                assert(*(genome->data(i, 1)) == (Byte)99);
            else if (i >= 22 && i < 32)
                assert(*(genome->data(i, 1)) == (Byte)0);
            else
                assert(*(genome->data(i, 1)) == (Byte)i);
        }
        assert(genome->size() == size);

        std::cout << "Test All Mutation 1: " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
    }


    /**
     * Tests Delete function
     **/
    template <class genomeName>
    void TestMultiMutation(bool debug)
    {
        std::cout << "\n" BOLDWHITE "Running " BOLDMAGENTA "MULTI MUTAITON TESTS " BOLDWHITE " for " BOLDMAGENTA << typeid(genomeName).name() << RESET << std::endl;   

        TestOverwriteDelete<genomeName>(debug);
        TestOverwriteInsert<genomeName>(debug);
        TestInsertOverwrite<genomeName>(debug);
        TestInsertDelete<genomeName>(debug);
        TestDeleteOverwrite<genomeName>(debug);
        TestDeleteInsert<genomeName>(debug);
        TestAllMutation1<genomeName>(debug);
    }



    /*******************************************************
     * 
     *          CLONE TESTS
     * 
     ******************************************************/

    /*******************************************************
     *          CLONE CONSTRUCTORS TESTS
     ******************************************************/

    /**
     * Tests constructor 50
     **/
    template <class genomeName>
    void TestCloneConstructor50(bool debug)
    {
        // test size 50
        size_t size = 50;
        AbstractGenome* genome = new genomeName(size);

        for (size_t i(0); i < genome->size(); i++)
        {
            *(genome->data(i, 1)) = (Byte)i;
        }

        AbstractGenome* clone = genome->clone();

        if (debug)
        {
            genome->show();
            clone->show();
        }


        for (size_t i(0); i < genome->size(); i++)
        {
            assert(*genome->data(i, 1) == *clone->data(i, 1));
        }

        assert(genome->size() == clone->size());
        std::cout << "Test Clone Constructor " << size << ": " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
        delete clone;
    }


    /**
     * Tests constructor 5000
     **/
    template <class genomeName>
    void TestCloneConstructor5000(bool debug)
    {
        // test size 5000
        size_t size = 5000;
        AbstractGenome* genome = new genomeName(size);

        for (size_t i(0); i < genome->size(); i++)
        {
            *(genome->data(i, 1)) = (Byte)i;
        }

        AbstractGenome* clone = genome->clone();

        if (debug)
        {
            genome->show();
            clone->show();
        }


        for (size_t i(0); i < genome->size(); i++)
        {
            assert(*genome->data(i, 1) == *clone->data(i, 1));
        }

        assert(genome->size() == clone->size());
        std::cout << "Test Clone Constructor " << size << ": " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
        delete clone;
    }


    /**
     * Tests constructor 500000
     **/
    template <class genomeName>
    void TestCloneConstructor500000(bool debug)
    {
        // test size 500000
        size_t size = 500000;
        AbstractGenome* genome = new genomeName(size);

        for (size_t i(0); i < genome->size(); i++)
        {
            *(genome->data(i, 1)) = (Byte)i;
        }

        AbstractGenome* clone = genome->clone();

        if (debug)
        {
            genome->show();
            clone->show();
        }


        for (size_t i(0); i < genome->size(); i++)
        {
            assert(*genome->data(i, 1) == *clone->data(i, 1));
        }

        assert(genome->size() == clone->size());
        std::cout << "Test Clone Constructor " << size << ": " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
        delete clone;
    }


    /**
     * Tests cloning functions for making population
     **/
    template <class genomeName>
    void TestCloneConstructor(bool debug)
    {
        std::cout << "\n" BOLDWHITE "Running " BOLDMAGENTA "CLONE CONSTRUCTOR TESTS " BOLDWHITE " for " BOLDMAGENTA << typeid(genomeName).name() << RESET << std::endl;   

        TestCloneConstructor50<genomeName>(debug);
        TestCloneConstructor5000<genomeName>(debug);
        TestCloneConstructor500000<genomeName>(debug);
    }

    /*******************************************************
     *          CLONE MUTATION TESTS
     ******************************************************/

    /**
     * Tests constructor 5000
     **/
    template <class genomeName>
    void TestCloneOverwrite(bool debug)
    {
        // test size 5000
        size_t size = 5000;
        AbstractGenome* genome = new genomeName(size);

        for (size_t i(0); i < genome->size(); i++)
        {
            *(genome->data(i, 1)) = (Byte)i;
        }

        AbstractGenome* clone = genome->clone();

        clone->overwrite(40, std::vector<Byte>(100, (Byte)10));
        clone->overwrite(2950, std::vector<Byte>(100, (Byte)10));
        clone->overwrite(4000, std::vector<Byte>(100, (Byte)10));

        AbstractGenome* forceClone = clone->clone(1);

        if (debug)
        {
            genome->show();
            clone->show();
            forceClone->show();
        }

        // test overwrite
        for (size_t i(0); i < genome->size(); i++)
        {
            // std::cout << i << "\t" << (int)*clone->data(i, 1) << "\t" << (int)*genome->data(i, 1) << std::endl;
            if ((i >= 40 && i < 140)|| (i >= 2950 && i < 3050) || (i >= 4000 && i < 4100))
            {
                assert(*clone->data(i, 1) == (Byte)10);
                assert(*genome->data(i, 1) == (Byte)i);
            }
            else
                assert(*genome->data(i, 1) == *clone->data(i, 1));

            assert(*clone->data(i, 1) == *forceClone->data(i, 1));
        }

        assert(genome->size() == clone->size());
        assert(clone->size() == forceClone->size());
        std::cout << "Test Clone Overwrite: " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
        delete clone;
        delete forceClone;
    }


    /**
     * Tests constructor 50
     **/
    template <class genomeName>
    void TestCloneInsert(bool debug)
    {
       // test size 5000
        size_t size = 5000;
        AbstractGenome* genome = new genomeName(size);

        for (size_t i(0); i < genome->size(); i++)
        {
            *(genome->data(i, 1)) = (Byte)i;
        }

        AbstractGenome* clone = genome->clone();

        clone->insert(0, std::vector<Byte>(100, (Byte)10));
        clone->insert(400, std::vector<Byte>(100, (Byte)10));
        clone->insert(3200, std::vector<Byte>(100, (Byte)10));
        clone->insert(5300, std::vector<Byte>(100, (Byte)10));

        AbstractGenome* forceClone = clone->clone(1);

        if (debug)
        {
            genome->show();
            clone->show();
            forceClone->show();
        }


        for (size_t i(0); i < genome->size(); i++)
        {
            assert(*(genome->data(i, 1)) == (Byte)i);
        }

        for (size_t i(0); i < clone->size(); i++)
        {
            // std::cout << i << "\t" << (int)*clone->data(i, 1) << "\t" << (int)*genome->data(i, 1) << std::endl;
            if ((i < 100)|| (i >= 400 && i < 500) || (i >= 3200 && i < 3300) || i >= 5300 )
            {
                assert(*clone->data(i, 1) == (Byte)10);
            }
            else if (i >= 100 && i < 400)
                assert(*clone->data(i, 1) == (Byte)(i-100));
            else if (i >= 500 && i < 3200)
                assert(*clone->data(i, 1) == (Byte)(i-200));
            else if (i >= 3300 && i < 5300)
                assert(*clone->data(i, 1) == (Byte)(i-300));

            if (*clone->data(i, 1) != *forceClone->data(i, 1))
                std::cout << i << "\t" << (int)*clone->data(i, 1) << "\t"  << (int)*forceClone->data(i, 1) << std::endl;
            assert(*clone->data(i, 1) == *forceClone->data(i, 1));
        }

        assert(genome->size() != clone->size());
        assert(clone->size() == forceClone->size());

        std::cout << "Test Clone Insert: " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
        delete clone;
        delete forceClone;
    }


    /**
     * Tests constructor 5000
     **/
    template <class genomeName>
    void TestCloneDelete(bool debug)
    {
         // test size 5000
        size_t size = 5000;
        AbstractGenome* genome = new genomeName(size);

        for (size_t i(0); i < genome->size(); i++)
        {
            *(genome->data(i, 1)) = (Byte)i;
        }

        AbstractGenome* clone = genome->clone();

        clone->remove(0, 100);
        clone->remove(400, 100);
        clone->remove(2700, 100);
        clone->remove(2600, 200);
        clone->remove(4400, 100);

        AbstractGenome* forceClone = clone->clone(1);

        if (debug)
        {
            genome->show();
            clone->show();
            forceClone->show();
        }

        for (size_t i(0); i < genome->size(); i++)
        {
            assert(*(genome->data(i, 1)) == (Byte)i);
        }

        for (size_t i(0); i < clone->size(); i++)
        {
            if (i < 400)
                assert(*clone->data(i, 1) == (Byte)(i+100));
            else if (i >= 400 && i < 2600)
                assert(*clone->data(i, 1) == (Byte)(i+200));
            else if (i >= 2600)
                assert(*clone->data(i, 1) == (Byte)(i+500));

            assert(*clone->data(i, 1) == *forceClone->data(i, 1));
        }

        assert(genome->size() != clone->size());
        assert(clone->size() == forceClone->size());

        std::cout << "Test Clone Delete: " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
        delete clone;
        delete forceClone;
    }

    /**
     * Tests constructor 5000
     **/
    template <class genomeName>
    void TestCloneMulti(bool debug)
    {
         // test size 5000
        size_t size = 5000;
        AbstractGenome* genome = new genomeName(size);

        for (size_t i(0); i < genome->size(); i++)
        {
            *(genome->data(i, 1)) = (Byte)i;
        }

        AbstractGenome* clone = genome->clone();

        clone->remove(0, 100);
        clone->remove(400, 100);
        clone->remove(2700, 100);
        clone->remove(2600, 200);
        clone->remove(4400, 100);

        if (debug)
        {
            genome->show();
            clone->show();
        }

        for (size_t i(0); i < genome->size(); i++)
        {
            assert(*(genome->data(i, 1)) == (Byte)i);
        }

        for (size_t i(0); i < clone->size(); i++)
        {
            if (i < 400)
                assert(*clone->data(i, 1) == (Byte)(i+100));
            else if (i >= 400 && i < 2600)
                assert(*clone->data(i, 1) == (Byte)(i+200));
            else if (i >= 2600)
                assert(*clone->data(i, 1) == (Byte)(i+500));

        }

        assert(genome->size() != clone->size());
        std::cout << "Test Clone Delete: " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
        delete clone;
    }



    /**
     * Tests cloning functions for making population
     **/
    template <class genomeName>
    void TestCloneMutation(bool debug)
    {
        std::cout << "\n" BOLDWHITE "Running " BOLDMAGENTA "CLONE MUTATION TESTS " BOLDWHITE " for " BOLDMAGENTA << typeid(genomeName).name() << RESET << std::endl;   

        TestCloneOverwrite<genomeName>(debug);
        TestCloneInsert<genomeName>(debug);
        TestCloneDelete<genomeName>(debug);
    }


    /*******************************************************
     *          ALl CLONE TESTS
     ******************************************************/

    /**
     * Tests cloning functions for making population
     **/
    template <class genomeName>
    void TestClone(bool debug)
    {
        TestCloneConstructor<genomeName>(debug);
        TestCloneMutation<genomeName>(debug);
    }


    /*******************************************************
     * 
     *          REALLOCATION TESTS
     * 
     ******************************************************

    /**
     * Tests inserting the whole genome size 50
     **/
    template <class genomeName>
    void TestReallocation(bool debug)
    {
     // test size 5000
        size_t size = 50;
        AbstractGenome* genome = new genomeName(size);

        for (size_t i(0); i < genome->size(); i++)
        {
            *(genome->data(i, 1)) = (Byte)i;
        }

        AbstractGenome* clone = genome->clone();

        for (size_t i(0); i < 40; i+=2)
        {
            clone->insert(i, std::vector<Byte>(1, (Byte)10));
        }

        if (debug)
        {
            genome->show();
            clone->show();
        }

        assert(clone->size() == size+20);
        assert(genome->size() != clone->size());
        std::cout << "Test Reallocation: " BOLDGREEN " PASSED" << RESET << std::endl;

        delete genome;
        delete clone;
    }



    /*******************************************************
     * 
     *          RUN ALL TESTS
     * 
     ******************************************************/

    /** 
     * Tests all of the previous tests
     **/
    template <class genomeName>
    void TestAll(bool debug)
    {
        TestConstructor<genomeName>(debug);
        TestOverwrite<genomeName>(debug);
        TestInsert<genomeName>(debug);
        TestDelete<genomeName>(debug);
        TestMultiMutation<genomeName>(debug);
        TestClone<genomeName>(debug);
    }

}