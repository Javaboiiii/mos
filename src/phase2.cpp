#include "../include/CPU.hpp"
#include "../include/MMU.hpp"
#include "../include/OS.hpp"

#include <fstream>
#include <iostream>
#include <string> 

class MOS
{
    private:
        Memory memory; 
        MMU mmu; 
        CPU cpu; 
        OS os; 
        int pageTable; 
        int pageEntryNo; 
    public:
        MOS()
            :cpu(memory)
        {
            pageTable = -1; 
            pageEntryNo = 0; 
        }



        void init()
        {
            // deciding the place for the page table 
            std::cout << "Loading Instructions" << std::endl; 
            pageTable = mmu.generateBlockId(); 
            std::string ip; 
            while(std::cin >> ip)
            {
                if(ip.starts_with("$AMJ"))
                {
                    os.setId(stoi(ip.substr(4, 4))); 
                    os.setTTL(stoi(ip.substr(8, 4))); 
                    os.setTLL(stoi(ip.substr(12, 4))); 
                }
                else if(ip.starts_with("$DTA")) break;
                else
                {
                    // we have here a program card 
                    // assuming that every line is a program card
                    int sz = ip.size();
                    if(sz > 40) 
                    {
                        std::cout << "Invalid Program size" << std::endl; 
                        exit(1); 
                    }

                    int blockId = mmu.generateBlockId(); 
                    int pageEntryLoc = (pageTable * 10) + pageEntryNo; 

                    std::string pageTableEntry = "**"; 
                    bool isSingle = blockId / 10 == 0; 
                    pageTableEntry = isSingle ? pageTableEntry + "0" + std::to_string(blockId) : pageTableEntry + std::to_string(blockId); 

                    memory.writeWordString(pageEntryLoc, pageTableEntry);
                    pageEntryNo ++; 
                    memory.loadIns(blockId, ip); 
                }
            }
        }


        void executePrograms()
        {
            std::cout << "Executing Instructions" << std::endl; 
            int pageTableEntryLoc = (pageTable * 10); 
            std::string entry = memory.readword(pageTableEntryLoc); 
            std::cout << entry << std::endl; 
            while(entry[0] == '*')
            {
                int blockId = ((entry[2] - '0') * 10) + (entry[3] - '0'); 
                int blockStart = blockId * 10; 
                int insCounter = blockStart; 
                std::string ins = memory.readword(insCounter);
                while(ins[0] != ' ' && insCounter < blockStart + 10)
                {
                   os.incTTC(); 

                   std::string op = {ins[0], ins[1]};  
                   Opcode opcode = cpu.decodeOpcode(op); 

                   if(opcode == Opcode::PD) os.incLLC(); 

                   int operand = ((ins[2] - '0') * 10) + (ins[3] - '0'); 
                   if(opcode != Opcode::H && (operand < 0 || operand > 299))
                   {
                       std::cerr << "Wrong operand" << std::endl;
                       exit(1); 
                   }

                   int logicalBlockId = -1;
                   if(opcode != Opcode::H && opcode != Opcode::BT) logicalBlockId = mmu.getSpace(operand / 10, opcode); 

                   // storing in the page table entry 
                   std::string key = std::to_string(operand / 10); 
                   std::string value = std::to_string(logicalBlockId);
                   value = value.size() == 1 ? "0" + value : value; 
                   key = key.size() == 1 ? "0" + key : key; 
                   std::string entry = key + value; 
                   memory.writeWordString((pageTable * 10) + pageEntryNo, entry);
                   pageEntryNo ++; 


                   int offset = operand % 10; 

                   std::string data = "";
                   if(opcode == Opcode::GD) 
                   {
                       std::cin >> data;
                       if(data == "$END")
                       {
                           std::cerr << "Data Out of Range" << std::endl; 
                           exit(1); 
                       }
                   }

                   cpu.loadIR(ins);
                   cpu.execIns(opcode, logicalBlockId, offset, data, insCounter, blockStart); 

                   if(opcode == Opcode::H) break; // end of current program

                   insCounter ++; 
                   ins = memory.readword(insCounter);
                }
                pageTableEntryLoc ++; 
                entry = memory.readword(pageTableEntryLoc); 
            }

            // clear memory for next program 
            memory.clearMem();
            cpu.clearRegister(); 
            os.reset(); 
            // look if there is another $AMJ 
            pageEntryNo = 0; 
            pageTable = -1; 
            init(); 
        }

};

int main() 
{
    MOS* os = new MOS(); 

    std::fstream file("data/output.txt", std::ios::out);
    file.close(); 
    os->init(); 
    os->executePrograms(); 

    return 0;
}
