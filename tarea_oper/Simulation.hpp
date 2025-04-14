#include <iostream>
#include <limits.h>
#include <string>
#include <vector>

#include "Resources.hpp"

class Simulation{
    public:
    Simulation();
    void menu();
    int calc_SSTF(data_t* valuesc, int size);
    int calc_FCFS(std::vector<int> values);
    void add_value(int value);
    void set_head(int fhead);
    void add_performance(int data);
    void set_values(int argc,char*argv[]);
    private:
    int head;
    char* orden;
    std::vector<int> values;
    std::vector<int> performance;
    const char* algorithms[6] = {"FCFS","SSTF","SCAN","C-SCAN","LOOK","C-LOOK"};
    char* algorithim;
};