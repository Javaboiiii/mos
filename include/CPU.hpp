#pragma once 

#include "Instructions.hpp"
#include "Memory.hpp"

class CPU
{
    private: 
        Memory mem;
        Word GPR;
        Word IR; 
        int SI;
        int bt; 
    public: 
        CPU(Memory& memory); 
        Opcode decodeOpcode(std::string& op);
        void loadIR(std::string& ins); 
        void execIns(Opcode& opcode, int blockId, int offset, std::string& data, int& insCounter, int& blockStart); 
        void clearRegister(); 
}; 
