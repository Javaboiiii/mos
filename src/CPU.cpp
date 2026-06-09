#include "../include/CPU.hpp"

#include <fstream>
#include <iostream>
#include <cstring>

CPU::CPU(Memory& memory)
    : mem(memory)
{
    bt = 0; 
    SI = 0; 
};

void CPU::loadIR(std::string& ins)
{
    for(int i = 0; i < 4; i ++)
    {
        IR.bytes[i] = ins[i]; 
    }
}

Opcode CPU::decodeOpcode(std::string& op) 
{
    if(op == "GD") return Opcode::GD;
    if(op == "PD") return Opcode::PD;
    if(op == "LR") return Opcode::LR;
    if(op == "SR") return Opcode::SR;
    if(op == "CR") return Opcode::CR;
    if(op == "BT") return Opcode::BT;
    if(op == "H ")  return Opcode::H;

    return Opcode::INVALID;
}

void CPU::execIns(Opcode& opcode, int blockId, int offset, std::string& data, int& insCounter, int& blockStart)
{
    int loc = (blockId * 10) + offset; 
    switch(opcode)
    {
        case Opcode::GD:
            {
                SI = 1; 
                std::cout << "Executing GD" << std::endl; 
                mem.writeBlock(blockId, data); 
                SI = 0; 
                break; 
            }
        case Opcode::PD:
            {
                SI = 2; 
                std::cout << "Executing PD" << std::endl; 
                std::fstream file("data/output.txt", std::ios::app);
                std::string input = mem.readBlock(blockId); 
                std::cout << input << std::endl; 
                file << input << '\n'; 
                file.close();
                SI = 0; 
                break; 
            }
        case Opcode::H:
            {
                // clearing instructions
                SI = 3;
                std::cout << "Exiting the Code" << std::endl; 
                mem.clearBlock(blockStart); 
                SI = 0; 
                break; 
            }
        case Opcode::LR:
            {
                std::cout << "Executing LR" << std::endl; 
                std::string content = mem.readword(loc); 
                for(int i = 0; i < 4; i ++)
                {
                    GPR.bytes[i] = content[i]; 
                }
                break; 
            }
        case Opcode::SR:
            {
                std::cout << "Executing SR" << std::endl; 
                mem.writeWord(loc, GPR); 
                break; 
            }
        case Opcode::CR:
            {
                std::cout << "Executing CR" << std::endl; 
                std::string c1 = "";
                for(int i = 0; i < 4; i ++)
                {
                    c1 += GPR.bytes[i]; 
                }
                std::string c2 = mem.readword(loc); 
                if(c1 == c2) bt = 1; 
                else bt = 0; 
                break; 
            }
        case Opcode::BT:
            {
                std::cout << "Executing BT" << std::endl; 
                if(bt)
                {
                    insCounter /= 10;  
                    insCounter = (insCounter * 10) + offset - 1; 
                }
                break; 
            }
        case Opcode::INVALID:
            {
                std::cout << "Invalid Instruction" << std::endl; 
                exit(1); 
                break; 
            }
    }
}

void CPU::clearRegister()
{
    std::memset(GPR.bytes, ' ', sizeof(GPR)); 
    std::memset(IR.bytes, ' ', sizeof(IR)); 
    bt = 0; 
    SI = 0; 
}
