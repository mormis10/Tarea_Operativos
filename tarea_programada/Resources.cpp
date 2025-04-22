// Copyright [2025] Diego Cerdas, Enrique Bermudez

#include <cstddef>

#include "Resources.hpp"

void sort_array(std::vector<int>& values) {
  int min = 0;
  int index = 0;
  int pivot = 0;
  for (size_t i = 0; i < values.size(); i++) {
    index = i;
    min = values[i];
    for (size_t j = i + 1; j < values.size(); j++) {
      if (values[j] < min) {
        min = values[j];
        index = j;
      }
    }
    pivot = values[i];
    values[i] = values[index];
    values[index] = pivot;
  }
}

void sort_mayor_menor(std::vector<int>& values) {
  int max = 0;
  int index = 0;
  int pivot = 0;
  for (size_t i = 0; i < values.size(); i++) {
    max = values[i];
    index = i;
    for (size_t j = i + 1; j < values.size(); j++) {
      if (values[j] > max) {
        max = values[j];
        index = j;
      }
    }
    pivot = values[i];
    values[i] = max;
    values[index] = pivot;
  }
}

void init_data(data_t data[], std::vector<int>& values) {
  for (size_t i = 0; i < values.size(); i++) {
    data[i].value = values[i];
    data[i].attended = false;
  }
}
