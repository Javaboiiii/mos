#pragma once 

#include "Instructions.hpp"

#include <unordered_set>
#include <unordered_map>

class MMU
{
    private: 
        std::unordered_set<int> blockMap;
        std::unordered_map<int, int> spaceMap; 
    public:
        MMU(); 
        void insertBlock(int blockId); 
        void removeBlock(int blockId); 
        bool findBlock(int  blockId); 
        int generateBlockId(); 
        int getSpace(int blockId, Opcode& opcode); 
        void removeSpace(); 
}; 
