#include "../include/MMU.hpp"

#include <cstdlib>
#include <stdlib.h> 
#include <iostream>

MMU::MMU()
{
    srand(time(nullptr)); 
    blockMap.clear(); 
}

void MMU::insertBlock(int blockId)
{
    blockMap.insert(blockId); 
}

void MMU::removeBlock(int blockId)
{
    blockMap.erase(blockId); 
}

bool MMU::findBlock(int blockId)
{
    return blockMap.find(blockId) != blockMap.end();
}

int MMU::generateBlockId()
{
    int upper_bound = 29, lower_bound = 0; 
    while(true)
    {
        int blockId = rand() % (upper_bound - lower_bound + 1) + lower_bound; 
        if(blockMap.find(blockId) == blockMap.end()) 
        {
            blockMap.insert(blockId); 
            return blockId;
        }
    }

    return -1; 
}

int MMU::getSpace(int blockId, Opcode& opcode)
{
    if((opcode != Opcode::GD && opcode != Opcode::SR) && spaceMap.count(blockId) == 0)
    {
        std::cerr << "Page Fault Error" << std::endl; 
        exit(1);
    }

    if(spaceMap.count(blockId) != 0) return spaceMap[blockId]; 
    while(true)
    {
        int newblockId = rand() % 30; 
        if(blockMap.find(newblockId) == blockMap.end()) 
        {
            spaceMap[blockId] = newblockId; 
            return spaceMap[blockId];
        }
    }

    return -1; 
}

void MMU::removeSpace()
{
    spaceMap.clear(); 
}
