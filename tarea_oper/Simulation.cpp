#include "Simulation.hpp"
#include <cstring>   
#include <cstdlib> 


Simulation::Simulation(){

}

void Simulation::set_values(int argc,char*argv[]){
   FILE* file;
   const char* files[3] = {"entrada1.txt","entrada2.txt","entrada3.txt"};
   if(argc >= 2){
    int index = std::atoi(argv[1]);
    file = fopen(files[index],"r");   
   }else{
    file = fopen(files[0],"r");
    printf("Entra aquí siuu\n");
   }
   this->performance.resize(6);
   char c;
   int number;
   while(fscanf(file, " %d%c",&number,&c)==2){
    this->values.push_back(number);
    if(c == '|'){
      break;
    }
   }
   
char temp_alg[32];
char temp_orden[8];

    fscanf(file, " %[^|]|", temp_alg);

    fscanf(file, " Head:%d |", &this->head);

    fscanf(file, " %s", temp_orden);
    this->algorithim = strdup(temp_alg);
    this->orden = strdup(temp_orden);


    fclose(file);
}

void Simulation::menu(){
  char* entry = this->algorithim;
  printf("Entra aquí ojito %s \n",algorithim);
  int cliniders = 0;
   printf("Entra aquí\n");
   if(entry == "FCFS"){
    cliniders = this->calc_FCFS(this->values);
   printf("El algoritmo de FCFS visitó: %i cilindros",cliniders);
   this->performance[0] = cliniders;
   }else if(entry == "SSTF"){

   }else if(entry == ""){

   }else if(entry == ""){

   }else if(entry == ""){

   }else if(entry == ""){

   }
}

int Simulation::calc_FCFS(std::vector<int> valuesc){
    int cilinders = 0;
    int pointer = head;
    for(int i = 0; i<valuesc.size(); i++){
        if(pointer > valuesc[i]){
            cilinders+= pointer - valuesc[i];
        }else if(pointer < valuesc[i]){
            cilinders+= valuesc[i] - pointer;
        }
        pointer = valuesc[i];
    }
    return cilinders;
}

int Simulation::calc_SSTF(data_t* valuesc, int size){
    int min = 0;
    int pointer = this->head;
    int cilinders = 0;
    int rounds = 0;
    int index = 0;
    for(int i = 0; i<size; i++){
        min = INT_MAX;
        for(int j = 0; j<size; j++){
            if(valuesc[j].attended == false){
                if(valuesc[j].value > pointer){
                    rounds = valuesc[j].value - pointer;
                }else if(valuesc[j].value < pointer){
                    rounds = pointer - valuesc[j].value;
                }
                if(rounds < min){
                    min = rounds;
                    index = j;
                }
            }
        }
         cilinders+= min;
         pointer = valuesc[index].value;
         valuesc[index].attended = true;
    }
    return cilinders;
}


void Simulation::add_value(int value){
    this->values.push_back(value);
}

void Simulation::set_head(int fhead){
    this->head = fhead;
}

void Simulation::add_performance(int data){
    this->performance.push_back(data);
}


