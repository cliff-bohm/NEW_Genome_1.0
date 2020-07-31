#pragma once
#include <stdint.h>

#include <vector>
#include <iostream>
#include <unordered_map>
#include <cstddef>
#include <cstring>

class AbstractGenome {

public:
    struct GeneDefinition {
        std::string name;
        std::vector<std::byte> startCodon;
        size_t geneSize; // size in bytes
    };

    AbstractGenome() {};

    virtual ~AbstractGenome() {}
    
    virtual size_t size() = 0;
    
    virtual void resize(size_t new_size) = 0;

    /** Gives the user a new byte array of memory
     * \param index index into the genome
     * \param byteSize size of memory to get (0: entire genome of contiguous memory)
     * \returns byte pointer of contiguous memory of byteSize at index of genome
    **/
    virtual std::byte* data(size_t index = 0, size_t byteSize = 0) {
        std::cout << "data has not been written for this genome class" << std::endl;
        exit(1);
    }

    virtual AbstractGenome* clone(bool forceCopy = false) {
        std::cout << "clone has not been written for this genome class" << std::endl;
        exit(1);
    }

    virtual void mutate() {
        std::cout << "mutate has not been written for this genome class" << std::endl;
        exit(1);
    }

    virtual void initalize() {
        std::cout << "initalize has not been written for this genome class" << std::endl;
        exit(1);
    }

    // return an int key to the genes in question
    virtual int initGeneSet(std::vector<GeneDefinition> geneInfo) {
        std::cout << "initGeneView has not been written for this genome class" << std::endl;
        exit(1);
    }

    virtual std::unordered_map<std::string,std::vector<size_t>> getGenePositions(int key) {
        std::cout << "getGenePositions has not been written for this genome class" << std::endl;
        exit(1);
    }

    // new functions

    // starting at index, write values in segement over values currently in genome
    virtual void overwrite(size_t index, const std::vector<std::byte>& segment) {
        std::cout << "overwrite has not been written for this genome class" << std::endl;
        exit(1);
    }

    // starting at index, write values in segement genome between genome[index-1] and genome[index]
    virtual void insert(size_t index, const std::vector<std::byte>& segment) {
        std::cout << "insert has not been written for this genome class" << std::endl;
        exit(1);
    }

    // starting at index, delete segmentSize values from genome starting at genome[index]
    virtual void remove(size_t index, size_t segmentSize) {
        std::cout << "remove has not been written for this genome class" << std::endl;
        exit(1);
    }

    // print the whole genome
    virtual void show()
    {
        std::cout << "show has not been written for this genome class :(" << std::endl;
    }

    virtual std::vector<size_t> find_all(std::vector<std::byte>& pattern)
    {
        std::cout << "find_all has not been write for this genome type. returning empty vector for now..." << std::endl;
        return std::vector<size_t>({});
    }

};


namespace GN {

    template <class T>
    auto genomeRead(AbstractGenome* genome, size_t index) -> T& {
        return reinterpret_cast<T*>(genome->data(index))[0];
    }

    template <class T>
    auto genomeWrite(AbstractGenome* genome, size_t index, const T& value) -> void {
        memcpy(genome->data(index), &value, sizeof(T));
    }

    // ==============================================
    // python-like named arguments
    // ==============================================

    struct GenomeReadParams {
        AbstractGenome* genome;
        size_t index;
    };
    template <class T>
    auto genomeRead(const GenomeReadParams& params) -> T& {
        return genomeRead<T>(params.genome, params.index);
    }

    template <class T>
    struct GenomeWriteParams {
        AbstractGenome* genome;
        size_t index;
        const T& value;
    };
    template <class T>
    auto genomeWrite(const GenomeWriteParams<T>& params) -> void {
        genomeWrite<T>(params.genome, params.index, params.value);
    }
}
