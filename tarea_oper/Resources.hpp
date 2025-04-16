#include <vector>

typedef struct{
int value;
bool attended;
}data_t;

static void sort_array(std::vector<int>& values){
    
    int min = 0;
    int index = 0;
    int pivot = 0;
    for(int i = 0; i<values.size(); i++){
        index = i;
        min = values[i];
        for(int j = i+1; j<values.size(); j++){
            if(values[j] < min){
                min = values[j];
                index = j;
            }
        }
        pivot = values[i];
        values[i] = values[index];
        values[index] = pivot;
    }
}
