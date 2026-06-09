#pragma once 
#include <string> 

struct Word
{
    char bytes[4]; 
}; 

class Memory
{
    private: 
        Word mem[300]; 
    public: 
        Memory(); 
        void clearBlock(int& blockStart);
        std::string readword(int address); 
        std::string readBlock(int blockId); 
        void writeBlock(int blockId, std::string& line); 
        void writeWord(int address, Word& word);
        void loadIns(int address, std::string& line);  
        void writeWordString(int address, std::string& s); 
        void clearMem(); 
};
