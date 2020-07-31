// stl library
#include <iostream>
#include <cassert>
#include <array>
#include <vector>
#include <bitset>
#include <random>
#include <map>
#include <cstddef>

// genome
#include "AbstractGenome.h"


// basic testing library 
namespace CliffTests
{
    void testData(AbstractGenome* genome)
    {
        for (size_t i(0); i < genome->size(); i++)
        {
            *genome->data(i) = (std::byte)(i*2);
            // std::cout << (int)*genome->data(i) << std::endl;
        }

        auto data = genome->data(2, 2);
        std::cout << (int)*data << std::endl;
        assert(*data == (std::byte)4);
        assert(*(data+1) == (std::byte)6);
        
    }


    void runTests(AbstractGenome* genome) {
        //initialize genome to 8 sites
        genome->resize(8);
        auto readHead = genome->data();
        for (size_t i(0); i < genome->size(); ++i)
            readHead[i] = (std::byte)(i + 1);
        readHead[7] = (std::byte)(0b10000001); // 129, or -127

        /* this test demonstrates no time is spent copying into num if we use references.
        * Note: genomeRead<>() is defined in AbstractGenome.h
        */
        {
            std::byte& num = GN::genomeRead<std::byte>(genome, 0);
            assert((int)num == 1); // same as above
            genome->data()[0] = (std::byte)3;
            assert((int)num == 3);
            num = (std::byte)1; // reset it to 1
        }

        int num;

        // 1-byte read
        num = (int)GN::genomeRead<std::byte>(genome, 0);
        assert(num == 0b00000001);
        assert(num == 1); // same as above

        // 1-byte read (with named parameters for readability)
        num = (int)GN::genomeRead<std::byte>({ .genome = genome, .index = 0 });
        assert(num == 0b00000001);
        assert(num == 1); // same as above

        // 2-byte read
        num = GN::genomeRead<uint16_t>(genome, 0);
        assert(num == 0b00000010'00000001);
        assert(num == 513); // same as above

        // 4-byte read
        num = GN::genomeRead<uint32_t>(genome, 0);
        assert(num == 0b00000100'00000011'00000010'00000001);
        assert(num == 67'305'985); // same as above

        // 1-double read
        double& dbl = GN::genomeRead<double>(genome, 0);
        uint64_t bitanswer = 0b10000001'00000111'00000110'00000101'00000100'00000011'00000010'00000001; // roughly, = -1.04917e-303
        assert(dbl == reinterpret_cast<double*>(&bitanswer)[0]);

        // 2's complement
        // left-most bit interpretation:
        // unsigned vs signed
        num = GN::genomeRead<uint8_t>(genome, 7); // range [0,255] [00000000, 11111111]
        assert(num == 0b10000001);
        assert(num == 129); // same as above
        num = GN::genomeRead<int8_t>(genome, 7); // range [-128,127] [10000000,01111111]
        assert(num == static_cast<int8_t>(0b10000001));
        assert(num == -127); // same as above

        // byte-array read with no copy
        {
            std::array<uint8_t, 4>& arr = GN::genomeRead<std::array<uint8_t, 4>>(genome, 0);
            for (size_t i(0); i < arr.size(); i++)
                assert(arr[i] == i + 1);
        }

        // int32-array read with no copy
        {
            std::array<unsigned int, 2>& arr = GN::genomeRead<std::array<unsigned int, 2>>(genome, 0);
            assert(arr[0] == 67'305'985);
            assert(arr[1] == 2'164'721'157);
        }

        std::cout << "all read tests passed" << std::endl;

        // write single byte
        GN::genomeWrite<uint8_t>(genome, 0, 255);
        assert(GN::genomeRead<uint8_t>(genome, 0) == 255);

        // write several bytes
        for (size_t i = 0; i < 4; i++) { // rewrite first 4 bytes with (2,4,6,8)
            GN::genomeWrite<uint8_t>({ .genome = genome, .index = i, .value = uint8_t((i + 1) * 2) });
            assert(GN::genomeRead<uint8_t>(genome, i) == (i + 1) * 2);
        }

        // write array of integers (and let compiler guess the type!)
        {
            std::array<uint32_t, 2> arr = { 42,213 };
            GN::genomeWrite(genome, 0, arr);
            auto& result = GN::genomeRead<std::array<uint32_t, 2>>(genome, 0);
            assert(result[0] == 42);
            assert(result[1] == 213);
        }

        std::cout << "all write tests passed" << std::endl;
    }

    void runGeneTest(AbstractGenome* genome) {

        std::cout << "\n\nrunGeneTest...\nThis shows an example of loading\na struct into the genome and\nhow memory is affected.\n" << std::endl;

        // define payload and GeneDefinition for deterministic gate
        struct MyGenePayload {
            int num_in, num_out;
            std::array<uint8_t, 7> addresses;
            std::bitset<17> logic; // will use 4 bytes, bitset uses 4 bytes at a time
            double answer;
        };

        AbstractGenome::GeneDefinition MyGeneDef = { "MyGene",{(std::byte)42,(std::byte)212},sizeof(MyGenePayload) };
        //GeneDefinition name, start codon, size of gene

        std::cout << "gene contains:\n  ints  'num_in', 'num_out'\n  array<uint8_t, 7> 'addresses'\n  bitset<17> 'logic'\n  double 'answer'";
        
        // write a MyGenomePayload into the genome at index 0
        MyGenePayload gene_instance;
        clean(gene_instance); // zero out memory
        gene_instance.num_in = 255+10;
        gene_instance.num_out = 20;
        gene_instance.addresses = {30,31,32,33,34,35,36};
        gene_instance.logic = 0b111100101100101101;
        gene_instance.answer = 42.42;
        GN::genomeWrite(genome, 0, gene_instance);
        // note that the bitstring will print in reverse order below (least signifigent diget first)

        // set up genes set in genome
        // the list can contain more then one GeneDefinition
        // key is a value used to get these genes
        int key = genome->initGeneSet({ MyGeneDef });

        // get the list of start positions for the genes
        auto startPos = genome->getGenePositions(key);

        // read a MyGene from start of first deterministic gate
        const auto& MyGene_data = GN::genomeRead<MyGenePayload>(genome, 0);

        // print sizes
        std::cout << "Det MyGene_data sizeof() " << sizeof(MyGene_data) << std::endl;
        std::cout << "Det MyGene_data.num_in sizeof() " << sizeof(MyGene_data.num_in) << std::endl;
        std::cout << "Det MyGene_data.num_out sizeof() " << sizeof(MyGene_data.num_out) << std::endl;
        std::cout << "Det MyGene_data.addresses sizeof() " << sizeof(MyGene_data.addresses) << std::endl;
        std::cout << "Det MyGene_data.logic sizeof() " << sizeof(MyGene_data.logic) << std::endl;
        std::cout << "Det MyGene_data.answer sizeof() " << sizeof(MyGene_data.answer) << std::endl;

        std::cout << "Det Gate:" << std::endl;
        std::cout << "  num_in:  " << MyGene_data.num_in << std::endl;
        std::cout << "  num_out: " << MyGene_data.num_out << std::endl;
        std::cout << "  addresses: ";
        for (auto& v : MyGene_data.addresses) {
            std::cout << " " << int(v);
        }
        std::cout << "\n  logic: ";
        for (size_t v(0); v < MyGene_data.logic.size(); v++) {
            std::cout << " " << MyGene_data.logic[v];
        }
        std::cout << std::endl;
        std::cout << "  val: " << MyGene_data.answer << std::endl;

        // iterate over MyGene_data size locations in genome
        auto head = genome->data();
        std::cout << "genome byte values for MyGene:" << std::endl;
        for (int i(0); i < sizeof(MyGenePayload); i++) {
            std::cout << " " << i << ":" << (int)head[i] << std::endl;
        }
        std::cout << std::endl;
        std::cout << "0-3 = num_in (int), 4-7 = num_out (int),\n"
            "8-14 = addresses (vect of uint8_t),"
            "\n15 is skipped so bitstring can start on word,\n"
            "16-23 logic (bitset), 24-31 anwser (double)\n" << std::endl;
    }

    void find_patterns_tests() {
        AbstractGenome* test_genome = new TestGenome(30);
        size_t i(0);
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(3) });
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(4) });
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(5) });
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(3) });
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(3) });
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(7) });
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(2) });
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(3) });
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(4) });
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(2) });
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(2) });
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(3) });
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(4) });
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(5) });
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(3) });
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(2) });
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(3) });
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(4) });
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(5) });
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(3) });
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(4) });
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(3) });
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(3) });
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(3) });
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(3) });
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(4) });
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(3) });
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(3) });
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(3) });
        GN::genomeWrite<std::byte>({ .genome = test_genome, .index = i++, .value = std::byte(3) });

        std::vector<std::byte> pattern1({ (std::byte)2,(std::byte)3,(std::byte)4 });
        std::vector<std::byte> pattern2({ (std::byte)3,(std::byte)4,(std::byte)5,(std::byte)3 });
        std::vector<std::byte> pattern3({ (std::byte)3,(std::byte)3,(std::byte)3 });


        assert(test_genome->find_all(pattern1) == std::vector<size_t>({6, 10, 15}));
        assert(test_genome->find_all(pattern2) == std::vector<size_t>({ 0,11,16 }));
        assert(test_genome->find_all(pattern3) == std::vector<size_t>({ 21,22,26,27 }));

        std::cout << "all find pattern tests passed" << std::endl;
        /*	
        for (auto& pat : std::vector< std::vector<std::byte>>({ pattern1,pattern2,pattern3 })) {
            std::cout << "looking for pattern: ";
            for (auto& v : pat) {
                std::cout << (int)v << " ";
            }
            std::cout << std::endl;
            auto gene_indexes = test_genome->find_all(pat);
            std::cout << "found locations: ";
            for (auto v : gene_indexes) {
                std::cout << v << " ";
            }
            std::cout << std::endl << std::endl;
        }
        */
    }

    void test_alterations() {
        std::cout << "----------------------------" << std::endl;
        std::cout << "-- begin test_alterations --" << std::endl;
        AbstractGenome* test_genome = new TestGenome(0);
        test_genome->show();
        test_genome->insert(0, std::vector<std::byte>{ (std::byte)1, (std::byte)2, (std::byte)3 });
        test_genome->show();
        test_genome->insert(0, std::vector<std::byte>{ (std::byte)1, (std::byte)2, (std::byte)3 });
        test_genome->show();
        test_genome->overwrite(2, std::vector<std::byte>{ (std::byte)4, (std::byte)4, (std::byte)4 });
        test_genome->show();
        test_genome->remove(1, 2);
        test_genome->show();
        std::cout << "-- done test_alterations --" << std::endl;
        std::cout << "---------------------------" << std::endl << std::endl;
    }
}