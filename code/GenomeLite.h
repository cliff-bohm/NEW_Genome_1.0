/**
 * \file GenomeLite.h
 * \author Victoria Cao
 * 
 * \brief Base class for a simple GenomeLite class using SegmentNode 
 * implementation
 **/

#pragma once
#include <vector>
#include <cstdint>
#include <cstddef>
#include <memory>
#include <iostream>

#include "AbstractGenome.h"
#include "SegmentList.h"
#include "SegmentNode.h"

typedef char Byte; // c++17 std::byte doesn't always work


/** Implementation of a genomeLite object **/
class GenomeLite
{
private:
    /// Gives handler access to variables
    friend class Handler; 
    friend class MutatorHandler;

	AbstractGenome* ParentGenome; ///< pointer to parent genome
    SegmentList* GeneSegments;  ///< list of gene segments

public:
    /** Constructor
     * \param  genome Parent genome the GenomeLite is constructed from*/
	GenomeLite(AbstractGenome* genome) : ParentGenome(genome)
    {
        auto segment = std::make_shared< GeneSegment >(genome->data(), genome->size());
        GeneSegments = new SegmentList(segment);
    }

    /** Deconstructor **/
	~GenomeLite() { delete GeneSegments; }

    /** Gets size 
     * \returns size of genome **/
    size_t size() { return GeneSegments->siteCount(); }

    /** Gets size 
     * \returns size of genome **/
    size_t segmentsCount() { return GeneSegments->size(); }

    /** Prints Segment list **/
    void print()
    {
        GeneSegments->print();
    }
};