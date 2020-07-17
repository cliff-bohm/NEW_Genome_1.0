/**
 * \file GenomeLite.cpp
 * \author Victoria Cao
 **/

#include "GenomeLite.h"

GenomeLite::GenomeLite(size_t size)
{
    List = new SegmentList(size);
}


AbstractGenome* GenomeLite::clone()
{
    return new GenomeLite(*this);
}

/** Gets size of genome sites
 * \return size of tree **/
size_t GenomeLite::size() 
{ 
    return List->GetSiteCount(); 
}

/** Gets size of genome sites
 * \param newSize **/
void GenomeLite::resize(size_t newSize) 
{ 
    List->Resize(newSize);
}

/** Gets contiguous data from genome
 * \param index to start
 * \param byteSize number of bytes
 * \returns start of memory
 **/
Byte* GenomeLite::data(size_t index, size_t byteSize)
{
    return List->GetData(index);
}

/** Overwrites an index in the gene
 * \param index
 * \param segment
 **/
void GenomeLite::overwrite(size_t index, const std::vector<std::byte>& segment)
{
    if (List->IsFull())
        List->Reallocate();
    List->Overwrite(index, segment);
}

/** Inserts at index in the gene
 * \param index
 * \param segment
 **/
void GenomeLite::insert(size_t index, const std::vector<std::byte>& segment)
{
    if (List->IsFull())
        List->Reallocate();
    List->Insert(index, segment);
}

/** Removes at index in the gene
 * \param index
 * \param segmentSize
 **/
void GenomeLite::remove(size_t index, size_t segmentSize)
{
    List->Remove(index, segmentSize);
}

/** Prints the tree **/
void GenomeLite::show()
{
    List->Print();
}

/** Finds all instances of pattern in genome
 * \param pattern to find
 * \return vector of indexes 
 **/
std::vector<size_t> GenomeLite::find_all(std::vector<std::byte>& pattern)
{
    exit(0);
}
