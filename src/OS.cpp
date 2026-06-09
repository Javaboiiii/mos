#include "../include/OS.hpp"

#include <iostream>

OS::OS()
{
    std::cout << "Started OS" << std::endl;
}

void OS::setId(int id)
{
    pcb.jobId = id; 
}

void OS::setTTL(int limit)
{
    pcb.TTL = limit; 
}

void OS::setTLL(int limit)
{
    pcb.TLL = limit; 
}

void OS::incTTC()
{
    pcb.TTC ++; 
    if(pcb.TTC > pcb.TTL)
    {
        std::cout << "Total Time exceeded" << std::endl; 
        exit(1); 
    }
}

void OS::incLLC()
{
    pcb.LLC ++;
    if(pcb.LLC > pcb.TLL) 
    {
        std::cerr << "Line Limit Exceeded" << std::endl; 
        exit(1); 
    }
}

void OS::reset()
{
    pcb.jobId = 0;
    pcb.TTL = 0; 
    pcb.TLL = 0; 
    pcb.TTC = 0; 
    pcb.LLC = 0; 
}
