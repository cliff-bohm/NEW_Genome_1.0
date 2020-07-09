/**
 * \file SegmentNode.cpp
 * \author Victoria Cao
 **/

#include <iostream>
#include "SegmentNode.h"

#include "SegmentPool.h"

/** Gets data from Segment
 * \returns size of data **/
Byte* SegmentNode::GetData(size_t index)
{
    if (index < Size)
        return Start+index;
    else
    {
        std::cout << "Error: trying to get data from index " << (int)index << std::endl;
        Print();
        exit(1);
    }
    
}


// /** Gets right node referencet
//  * \returns node reference **/
// SegmentNode* SegmentNode::GetParent(SegmentPool* pool)
// {
//     if (Parent == std::numeric_limits<size_t>::max())
//         return nullptr;
//     return pool->At(Parent);
// }

// /** Sets Left node
//  * \param node **/
// void SegmentNode::SetLeft(SegmentNode* node)
// {
//     if (node)
//         Left = node->GetPos();
//     else
//         Left = std::numeric_limits<size_t>::max();
// }



/** Truncates Data from left 
 * \param cutSize amount to cut off the left of current segment 
 **/
void SegmentNode::TruncateLeft(size_t cutSize)
{
    Start += cutSize;
    Size -= cutSize;
    Weight -= (int)cutSize;
}

/** Truncates Data from right 
 * \param cutSize amount to cut off the right of current segment 
 **/
void SegmentNode::TruncateRight(size_t cutSize)
{
    Size -= cutSize;
    Weight -= (int)cutSize;
}


/** Subdivide segment at index
 * \param pool The pool of memory to make a pointer from
 * \param index Index to cut the segment
 * \return pair of two new SegmentNodes to the cut segments 
 **/
SegmentNode* SegmentNode::Cut(SegmentPool* pool, size_t index)
{
    SegmentNode* cutSegment = pool->Allocate(Data, Start+index, Size-index);
    TruncateRight(Size-index);

    return cutSegment;
}

/** Overwrites segmentNode
 * \param index to start overwriting
 * \param segment to overwrite with
 **/
size_t SegmentNode::Overwrite(size_t index, const std::vector<std::byte>& segment, size_t segmentStart)
{
    size_t size = segment.size()-segmentStart;
    if (size > Size)
        size = Size;
    std::memcpy(Start+index, &segment[segmentStart], size);

    return segmentStart + size;
}

/** Overwrites segmentNode
 * \param index to start overwriting
 * \param segment to overwrite with
 **/
size_t SegmentNode::Insert(size_t index, const std::vector<std::byte>& segment, size_t segmentStart)
{
    size_t insertSize = segment.size()-segmentStart;
    if (Size+insertSize > Data->MaxSize)
        insertSize = Data->MaxSize - Size;

    
    std::memcpy(Start+index+insertSize, Start+index, Size-index);
    std::memcpy(Start+index, &segment[segmentStart], insertSize);

    return segmentStart + insertSize;
}


/** prints node info **/
void SegmentNode::Print()
{
    std::cout << "SegmentNode " << this << std::endl;
    std::cout << "weight " << std::dec << Weight << " size " << Size << " height " << Height << std::endl;
    std::cout << "left " << Left << std::endl;
    std::cout << "B " << (unsigned long)Start << std::endl;
    std::cout << "E " << (unsigned long)Start+Size << std::endl;
    
    for (size_t i = 0; i < Size; i++)
    {
        std::cout << std::dec << (int)(*(Start+i)) << ", ";
    }
    std::cout << std::endl;

    std::cout << "right " << Right << std::endl;
    std::cout << std::endl;
}