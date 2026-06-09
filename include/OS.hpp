#pragma once

struct PCB
{
    int jobId;
    int TTL; 
    int TLL; 

    int TTC;
    int LLC; 
}; 

class OS
{
    private: 
        PCB pcb;
    public: 
        OS(); 
        void setId(int id); 
        void setTTL(int limt); 
        void setTLL(int limit); 
        void incTTC(); 
        void incLLC(); 
        void reset(); 
};
