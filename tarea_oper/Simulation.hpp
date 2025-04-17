#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
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
        int calc_Scan(std::vector<int> values, int disk_size);
        int calc_CScan(std::vector<int> values, int disk_size);
        int calc_Look(std::vector<int> values);
        int calc_CLook(std::vector<int> values);
        void add_value(int value);
        void set_head(int fhead);
        void add_performance(int data);
        void read_file(int argc, char*argv[]);
        void set_values(const std::string& line);
        int calc_performance();

        std::string trim(const std::string& str);

    private:
        std::vector<int> values;
        const std::string algorithms[6] = {"FCFS","SSTF","SCAN","C-SCAN","LOOK","C-LOOK"};
        std::string algorithm;
        int head = 0;
        std::string orden = "ASC";
        std::vector<int> performance;
};
#endif // SIMULATION_HPP
