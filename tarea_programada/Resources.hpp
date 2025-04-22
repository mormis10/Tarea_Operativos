// Copyright [2025] Diego Cerdas, Enrique Bermudez

#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <vector>

typedef struct {
  int value;
  bool attended;
} data_t;

void sort_array(std::vector<int>& values);
void sort_mayor_menor(std::vector<int>& values);
void init_data(data_t data[], std::vector<int>& values);

#endif
