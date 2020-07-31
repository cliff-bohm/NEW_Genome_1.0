/**
 * \file SegmentList.cpp
 * \author Victoria Cao
 **/

#include <cstdint>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>

#include "SegmentList.h"

#define RESET   "\033[0m"
#define CYAN    "\033[36m"      /* Cyan */


/** 
 * Calculates approximate page size for largest SegmentNode
 * \param size of genome
 * \return page size
 **/
size_t SegmentList::CalculatePage(size_t size)
{
    if (size > 30000)
        return 0.13*size;
    else
        return 4000;
}

/** 
 * Constructor 
 * \param size of new list
 **/
SegmentList::SegmentList(size_t size)
    : SiteCount(size), Page(CalculatePage(size))
{
    size_t poolSize = std::ceil(SiteCount/Page);
    Pool.reserve(poolSize);
    IndexTable.reserve(poolSize);

    // Creates list
    size_t node = 0;
    size_t currSize = 0;

    while(currSize < SiteCount)
    {
        // creates new node
        size_t nodeSize = std::min((size_t)Page, SiteCount - currSize);
        Pool.push_back(std::vector<Byte>(nodeSize));

        // adds node to indexing table
        IndexTable.push_back(currSize);   

        currSize += nodeSize;
    }

}

/** 
 * Copy Constructor 
 * \param list to copy from
 **/
SegmentList::SegmentList(const SegmentList &list)
    : SiteCount(list.SiteCount), Page(list.Page)
{
    Pool = list.Pool;
    IndexTable = list.IndexTable;
}


/**
 * Resizes the genome
 * \param size to resize to
 **/
void SegmentList::Resize(size_t size)
{
    if (size < SiteCount)
    {
        Remove(size, SiteCount-size);
    }
    else
    {
        Insert(SiteCount, std::vector< Byte >(size-SiteCount));
    }

    SiteCount = size;
}

/** 
 * Finds index in list
 * \param index to find
 * \return pair node index in pool and offset within node
 **/
TableEntry SegmentList::Find(size_t index)
{
    // binary sesarch through Index Table 
    auto poolIndex = std::upper_bound(IndexTable.begin(), IndexTable.end(), index) - IndexTable.begin() - 1;
    size_t left = IndexTable.at(poolIndex);

    // iterate through segment list if not in index
    while (poolIndex < Pool.size()-1)
    {
        if (left + Pool.at(poolIndex).size() > index)
            break;
            
        // update index table
        left += Pool.at(poolIndex).size();
        IndexTable.push_back(left);

        ++poolIndex;
    }

    return TableEntry(poolIndex, left);
}


/** 
 * Gets Byte poitner to data
 * \param index in genome
 * \return pointer to data
 **/
Byte* SegmentList::GetData(size_t index, size_t segmentSize)
{
    auto found = Find(index);

    if (found.Offset+segmentSize > Pool.at(found.PoolIndex).size())
    {
        auto insertSize = found.Offset+segmentSize-Pool.at(found.PoolIndex).size();
        Pool.at(found.PoolIndex).insert(Pool.at(found.PoolIndex).begin(), Pool.at(found.PoolIndex+1).begin(), Pool.at(found.PoolIndex+1).begin()+insertSize);

        // update table
        if (found.PoolIndex < IndexTable.size()-1)
        {
            IndexTable.resize(found.PoolIndex+1);
        }
    }

    return Pool.at(found.PoolIndex).data()+(index-found.Offset);
}


/** 
 * Overwrites into index of list
 * \param index 
 * \param segment to overwrite with
 **/
void SegmentList::Overwrite(size_t index, const std::vector<Byte>& segment)
{
    auto found = Find(index);
    auto poolIndex = found.PoolIndex;
    auto localIndex = index-found.Offset;

    size_t startIndex = 0;

    // loop until overwrite is all written
    while(startIndex < segment.size())
    {
        size_t size = std::min((Pool.at(poolIndex).size()-localIndex), (segment.size()-startIndex));
        std::copy_n(segment.begin()+startIndex, size, Pool.at(poolIndex).begin()+localIndex);

        startIndex += size;
        localIndex = 0;
        
        ++poolIndex;      
    }
}


/** 
 * Inserts into list
 * \param index 
 * \param segment to insert
 **/
void SegmentList::Insert(size_t index, const std::vector<Byte>& segment)
{
    auto found = Find(index);
    auto localIndex = index-found.Offset;

    // overwrite current genome
    Pool.at(found.PoolIndex).insert(Pool.at(found.PoolIndex).begin()+localIndex, segment.begin(), segment.end());

    // update size
    SiteCount += segment.size();

    // update table
    if (found.PoolIndex < IndexTable.size()-1)
    {
        IndexTable.resize(++found.PoolIndex);
    }
}


/** 
 * Inserts into list
 * \param index 
 * \param segmentSize to remove
 **/
void SegmentList::Remove(size_t index, size_t segmentSize)
{
    auto found = Find(index);
    auto poolIndex = found.PoolIndex;
    auto localIndex = index-found.Offset;

    // update size
    SiteCount -= segmentSize;

    // loop until the whole segmentSize is removed
    while(segmentSize)
    {
        size_t removeSize = std::min(Pool.at(poolIndex).size()-localIndex, segmentSize);

        // remove whole node
        if (!localIndex && removeSize == Pool.at(poolIndex).size())
        {
            Pool.erase(Pool.begin()+poolIndex);
        }
        else
        {
            Pool.at(poolIndex).erase(Pool.at(poolIndex).begin()+localIndex, Pool.at(poolIndex).begin()+localIndex+removeSize);
            poolIndex++;
        }
        
        segmentSize -= removeSize;
        localIndex = 0;
    }

    // update table
    if (found.PoolIndex < IndexTable.size()-1)
    {
        IndexTable.resize(++found.PoolIndex);
    }
        
}

/** 
 * Prints the segment list
 **/
void SegmentList::Print()
{
    // print index table
    std::cout << CYAN << "\nIndex Table:" << std::endl;;
    for (const auto &entry : IndexTable)
    {
        std::cout << entry << ",";
    }

    std::cout << "\n" << RESET << std::endl;

    
    // print segment list
    for (const auto &segment : Pool)
    {
        std::cout << "\nSegment" << std::endl;
        for (const auto &site : segment)
        {
            std::cout << (int)site << ", ";
        }
    }
    std::cout << std::endl;
}
