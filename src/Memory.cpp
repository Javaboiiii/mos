#include "../include/Memory.hpp" 

#include <iostream> 
#include <cstring>

Memory::Memory()
{
    memset(mem, ' ', sizeof(mem)); 
}

void Memory::clearBlock(int& blockStart)
{
    int blockCounter = blockStart; 
    for(int i = 0; i < 10; i ++)
    {
        for(int j = 0; j < 4; j ++)
        {
            mem[blockCounter].bytes[j] = ' '; 
        }
        blockCounter ++; 
    }
}

std::string Memory::readword(int address)
{
    if(address < 0 || address > 299)
    {
        std::cout << "Invalid Address" << std::endl; 
        return ""; 
    }
    std::string line = ""; 
    for(int i = 0; i < 4; i ++)
    {
        line += mem[address].bytes[i]; 
    }

    return line; 
}

std::string Memory::readBlock(int blockId)
{
    int row = blockId * 10; 
    std::string output = ""; 
    for(int i = row; i < row + 10; i ++)
    {
        for(int j = 0; j < 4; j ++)
        {
            output += mem[i].bytes[j]; 
        }
    }
    return output;
}

void Memory::loadIns(int blockId, std::string& line)
{
    int row = blockId * 10; 
    int lineIdx = 0; 
    int sz = line.size(); 
    for(int i = row; i < row + 10; i ++)
    {
        for(int j = 0; j < 4; j ++)
        {
            if(lineIdx >= sz) break; 
            if(line[lineIdx] == 'H') 
            {
                mem[i].bytes[0] = 'H';
                mem[i].bytes[1] = ' ';
                mem[i].bytes[2] = ' ';
                mem[i].bytes[3] = ' ';
                lineIdx ++; 
                break; 
            }

            mem[i].bytes[j] = line[lineIdx]; 
            std::cout << mem[i].bytes[j]; 
            lineIdx ++; 
        }
        std::cout << std::endl; 
        if(lineIdx >= sz) break; 
    }
}


void Memory::writeBlock(int blockId, std::string& line)
{
    int row = blockId * 10; 
    int lineIdx = 0; 
    int sz = line.size(); 
    for(int i = row; i < row + 10; i ++)
    {
        for(int j = 0; j < 4; j ++)
        {
            if(lineIdx >= sz) break; 

            mem[i].bytes[j] = line[lineIdx]; 
            lineIdx ++; 
        }

        if(lineIdx >= sz) break; 
    }
}

void Memory::writeWord(int address, Word& word)
{
    for(int i = 0; i < 4; i ++)
    {
        mem[address].bytes[i] = word.bytes[i]; 
    }
};

void Memory::writeWordString(int address, std::string& s)
{
    for(int i = 0; i < 4; i ++)
    {
        mem[address].bytes[i] = s[i]; 
    }
}

void Memory::clearMem()
{
    std::memset(mem, ' ', sizeof(mem));
}
