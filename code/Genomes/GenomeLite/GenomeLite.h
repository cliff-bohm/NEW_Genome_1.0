/**
 * \file GenomeLite.h
 * \author Victoria Cao
 * 
 * \brief Base class for a simple GenomeLite class using SegmentNode 
 * implementation
 **/

#pragma once
#include <cstdint>
#include <iostream>

#include "../AbstractGenome.h"
#include "SegmentList.h"


typedef std::byte Byte;


/** Implementation of a genomeLite object **/
class GenomeLite : public AbstractGenome
{
private:
    SegmentList* List;

public:
    /** (deleted) default constructor **/
    GenomeLite() = default;

    /** size constructor **/
    GenomeLite(size_t size);

    /** size constructor **/
    GenomeLite(const GenomeLite &genome) 
        : List(new SegmentList(*(genome.List))) {}

    /** destructor **/
    ~GenomeLite() { delete List; }


    virtual size_t size() override;
    virtual void resize(size_t newSize) override;
    virtual AbstractGenome* clone(bool forceCopy = false) override;
    virtual Byte* data(size_t index = 0, size_t byteSize = 0) override;
    virtual void overwrite(size_t index, const std::vector<std::byte>& segment) override;
    virtual void insert(size_t index, const std::vector<std::byte>& segment) override;
    virtual void remove(size_t index, size_t segmentSize) override;
    virtual void show() override;
    virtual std::vector<size_t> find_all(std::vector<std::byte>& pattern) override;

};