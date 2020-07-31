/**
 * \file SegmentList.h
 * \author Victoria Cao
 * 
 * \brief class for a rope data structure
 **/

#pragma once

#include <memory>
#include <iostream>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>
#include <iterator>
#include <cmath>


typedef std::byte Byte; // easy reading

/** struct for finding **/
struct TableEntry
{
    size_t PoolIndex;
    size_t Offset;

    TableEntry(size_t pInd, size_t offset)
        : PoolIndex(pInd), Offset(offset) {}
};


/** basic implementation of rope **/
class SegmentList
{
private:
    /// member variables
    std::vector< size_t > IndexTable; ///< pair(index and location in segmentPool)
    std::vector< std::vector<Byte> > Pool;

    size_t SiteCount = 0;
    size_t Page;

    size_t CalculatePage(size_t size);

public:
    SegmentList() = default;
    SegmentList(size_t size);
    SegmentList(const SegmentList &List);

    ~SegmentList() {}

    size_t GetSiteCount() { return SiteCount; }

    TableEntry Find(size_t index);
    Byte* GetData(size_t index, size_t segmentSize = 1);
    void Resize(size_t size);

    void Overwrite(size_t index, const std::vector<std::byte>& segment);
    void Insert(size_t index, const std::vector<std::byte>& segment);
    void Remove(size_t index, size_t segmentSize);
    void Print();    

};