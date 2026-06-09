#include <iostream> 
#include <fstream>
#include <string> 
#include <cstring> 

using namespace std; 

class OS
{
    private:
        char GPR[4]; 
        char IR[4]; 
        char mem[100][4]; 
        int id, ttl, tll;
        int ic = 0, bt = 0, si = 0; 
        void GD(int loc)
        {
            string data; 
            getline(cin, data); 
            if(data == "$END")
            {
                cout << "Request for Data is not Fulfilled" << endl; 
                exit(1);  
            }
            
            int j = (loc / 10) * 10; // block number 
            int org_j = j; 
            int i = 0; // offset 
            for(char& c: data)
            {
                mem[j][i] = c; 
                i ++; 
                if(i % 4 == 0)
                {
                    i = 0; 
                    j ++; 
                }

                if(j > org_j + 9)
                {
                    cout << "No more data can fit in" << endl; 
                    return ; 
                }
            }

            si = 0; 
        }


        string PD(int loc)
        {
            string op = ""; 
            cout << "Printing the block" << endl; 
            int rem = loc % 10; 
            int j = loc - rem; 
            int org_j = j; 

            while(j < org_j + 10)
            {
                for(int k = 0; k < 4; k ++)
                {
                    op += mem[j][k]; 
                    cout << mem[j][k];
                }
                cout << "\n"; 
                j ++; 
            }

            si = 0; 

            return op; 
        }

        void LR(int operand)
        {
            memcpy(GPR, mem[operand], 4); 
        }

        void SR(int operand)
        {
            memcpy(mem[operand], GPR, 4); 
        }

        void CR(int operand)
        {
            if(strncmp(GPR, mem[operand], 4) == 0) bt = 1; 
            else bt = 0; 
        }

        void BT(int operand, int& ic)
        {
            if(bt == 1) ic = operand - 1; 
        }

    public:


        void init()
        {
            string ip; 
            int j = 0; 
            int mem_loc = 0; 
            while(cin >> ip)
            {
                if(ip.starts_with("$AMJ"))
                {
                    // storing the initial limits 
                    id = stoi(ip.substr(4, 4)); 
                    ttl = stoi(ip.substr(8, 4)); 
                    tll = stoi(ip.substr(12, 4)); 
                }
                else if(ip.starts_with("$DTA")) 
                {
                    cin.ignore(); 
                    break; 
                }
                else
                {
                    // we have instructions now need to load into memory 
                    int i = 0; 
                    int s = ip.size(); 
                    while(j < 20 && i < s)
                    {
                        if(ip[i] == 'H')
                        {
                            mem[j][0]= 'H'; 
                            i ++; 
                        }
                        else
                        {
                            for(int k = 0; k < 4; k ++)
                            {
                                mem[j][k] = ip[i + k]; 
                            }
                            i += 4; 
                        }

                        j ++; 

                    }
                }
            }
            cout << "Loaded instructions into memmory" << endl; 
            for(int i = 0; i < 10; i ++)
            {
                for(int k = 0; k < 4; k ++)
                {
                    cout << mem[i][k]; 
                }

                cout << endl; 
            }
        }

        void execute_instructions()
        {
            fstream outFile("output.txt", ios::out); 
            while(ic < 100)
            {
                memcpy(IR, mem[ic], 4); 
                if(( IR[0] == 'G' && IR[1] == 'D' ) || ( IR[0] == 'P' && IR[1] == 'D' ) || IR[0] == 'H')
                {
                    // need to set the system interrupt 
                    if(IR[0] == 'G' && IR[1] == 'D')
                    {
                        int location = ( IR[2] - '0' ) * 10 + ( IR[3] - '0' ); 
                        si = 1; 

                        GD(location); 
                    }
                    else if(IR[0] == 'P' && IR[1] == 'D')
                    {
                        int location = ( IR[2] - '0' ) * 10 + ( IR[3] - '0' ); 
                        si = 2; 

                        outFile << PD(location); 
                        outFile << "\n"; 
                    }
                    else if(IR[0] == 'H')
                    {
                        si = 3;
                        cout << "Ending of the Program" << endl; 
                        break; 
                    }
                }
                else
                {
                    // no need of the system interrupt
                    int operand = ( IR[2] - '0' ) * 10 + ( IR[3] - '0' ); 
                    string opcode = { IR[0], IR[1] }; 
                    if(opcode == "LR")
                    {
                        LR(operand); 
                    }
                    else if(opcode == "SR")
                    {
                        SR(operand); 
                    }
                    else if(opcode == "CR")
                    {
                        CR(operand); 
                    }
                    else if(opcode == "BT")
                    {
                        BT(operand, ic); 
                    }
                }
                ic ++; 
            }

            outFile.close();
        }

        OS()
        {
            memset(GPR, ' ', sizeof(GPR)); 
            memset(mem, ' ', sizeof(mem)); 
        }

}; 


int main()
{

    OS* os = new OS();
    os->init(); 
    os->execute_instructions(); 
    delete os; 

    return 0; 
}
