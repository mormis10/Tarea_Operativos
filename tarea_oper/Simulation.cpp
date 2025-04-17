#include "Simulation.hpp"

Simulation::Simulation() {
}

void Simulation::read_file(int argc, char*argv[]) {
  std::string nombre = "entrada1.txt";
  if (argc > 1) {
    nombre = argv[1];
  }
  // Si usuario agrega archivo usarlo, sino default
  std::ifstream file(nombre);
  if (!file) {
    std::cerr << "No se pudo abrir el archivo: " << nombre << std::endl;
    return;
  }
  // Se analiza linea por linea el archivo
  std::string line;
  while (std::getline(file, line)) {
    if (!line.empty()) {
      set_values(line);
    }
  }
  return;
}

void Simulation::set_values(const std::string& line) {
  std::stringstream ss(line);
  std::string segment;

  // Guardar cilindros a revisar (hasta encontrar |)
  std::getline(ss, segment, '|');
  std::stringstream cilindros(segment);
  std::string num;

  while (std::getline(cilindros, num, ',')) {
    num.erase(std::remove_if(num.begin(), num.end(), ::isspace), num.end());
    if (!num.empty())
      values.push_back(std::stoi(num));
  }
 
 // esta es la cantidad de algortimos con los que vamos a trabajar
  this->performance.resize(6);
 
  // Obtener algoritmo a usar
  if (std::getline(ss, segment, '|')) {
    algorithm = trim(segment);
  }

  // Obtener posicion de cabeza de lectura
  if (std::getline(ss, segment, '|')) {
    segment = trim(segment);
    if (segment.find("Head:") != std::string::npos) {
      // Si lee cabeza, la usa, sino usa valor default (=0)
      try {
          this->head = std::stoi(segment.substr(segment.find(":") + 1));
      } catch (...) {}
    } else {
      // Si no hay cabeza, intente encontrar el orden
      this->orden = trim(segment);
      menu();
      return;
    }
  }
  // Si encontramos pos de cabeza, lea orden
  if (std::getline(ss, segment)) {
    this->orden = trim(segment);
  }
  menu();
  return;
}

// Funcion para remover todo lo que no sean letras (obtener tipo de algoritmo)
// Obtenido de stack overflow
std::string Simulation::trim(const std::string& str) {
  const auto begin = str.find_first_not_of(" \t");
  if (begin == std::string::npos) return "";
  const auto end = str.find_last_not_of(" \t");
  return str.substr(begin, end - begin + 1);
}

void Simulation::menu() {
  std::string entry = this->algorithm;
  std::cout << "Algoritmo es: " << entry << std::endl;
  std::cout << "Head es: " << this->head << std::endl;
  std::cout << "Orden es: " << this->orden << std::endl;
  int cilinders = 0;
  if(entry == "FCFS") {
  cilinders = this->calc_FCFS(this->values);
  printf("El algoritmo de FCFS visitó: %d cilindros", cilinders);
  this->performance[0] = cilinders;
  }else if(entry == "SSTF") {
    // Ocupamos de nuestro recurso para este 
    data_t requests[this->values.size()];
    init_data(requests,this->values);
    cilinders = this->calc_SSTF(requests,values.size());
    printf("El algoritmo de SSTF visitó: %d cilindros", cilinders);
    this->performance[0] = cilinders;
  }else if(entry == "SCAN") {
    // Para esta simulación vamos a suponer que tenemos un disco de 200
    cilinders = this->calc_Scan(this->values,200);
    printf("El algoritmo de SCAN vistió %i cilindros", cilinders);
    this->performance[2] = cilinders;
  }else if(entry == "CSCAN") {
    cilinders = this->calc_CScan(this->values,200);
    printf("El algoritmo de CSCAN vistió %i cilindros", cilinders);
    this->performance[2] = cilinders;
  }else if(entry == "LOOK") {
    cilinders = this->calc_Look(this->values);
    printf("El algoritmo de LOOK vistió %i cilindros", cilinders);
    this->performance[2] = cilinders;

  }else if(entry == "") {

  }
}

int Simulation::calc_FCFS(std::vector<int> values) {
  std::cout << "Iniciando FCFS:" << std::endl;
  int cilinders = 0;
  int pointer = head;
  for(int i = 0; i<values.size(); i++) {
      if(pointer > values[i]) {
          cilinders+= pointer - values[i];
      }else if(pointer < values[i]) {
          cilinders+= values[i] - pointer;
      }
      pointer = values[i];
  }
  return cilinders;
}

int Simulation::calc_SSTF(data_t* values, int size) {
  std::cout << "Iniciando SSTF:" << std::endl;
  int min = 0;
  int pointer = this->head;
  int cilinders = 0;
  int rounds = 0;
  int index = 0;
  for(int i = 0; i<size; i++) {
    min = INT_MAX;
    for(int j = 0; j<size; j++) {
      if(values[j].attended == false) {
        if(values[j].value > pointer) {
          rounds = values[j].value - pointer;
        }else if(values[j].value < pointer) {
          rounds = pointer - values[j].value;
        }
        if(rounds < min) {
          min = rounds;
          index = j;
        }
      }
  }
    cilinders+= min;
    pointer = values[index].value;
    values[index].attended = true;
  }
  return cilinders;
}


void Simulation::add_value(int value) {
    this->values.push_back(value);
}

void Simulation::set_head(int fhead) {
    this->head = fhead;
}

void Simulation::add_performance(int data) {
    this->performance.push_back(data);
}

int Simulation::calc_Scan(std::vector<int> values, int disk_size){
  std::vector<int> left;
  std::vector<int> right;
  right.push_back(disk_size);
  left.push_back(1);
  sort_array(values);
  for(int i = 0; i<values.size(); i++){
     if(values[i] > this->head){
        right.push_back(values[i]);
     }else{
      left.push_back(values[i]);
     }
  }
  int cilinders = 0;
  int pointer = this->head;

  // Vamos a calcular por la derecha

  for(int i = 0; i<right.size(); i++){
     cilinders+= right[i] - pointer;
     pointer = right[i];
  }

  // Ahora vamos pora la izquierda nachito
  for(int j = 0; j<left.size(); j++){
    cilinders+= pointer - left[j];
    pointer = left[j];
  }

  return cilinders;

}

int Simulation::calc_CScan(std::vector<int> values, int disk_size){

  std::vector<int> left;
  std::vector<int> right;
  right.push_back(disk_size);
  left.push_back(1);
  sort_array(values);
  for(int i = 0; i<values.size(); i++){
     if(values[i] > this->head){
        right.push_back(values[i]);
     }else{
      left.push_back(values[i]);
     }
  }
  int cilinders = 0;
  int pointer = this->head;

  // Vamos a calcular por la derecha

  for(int i = 0; i<right.size(); i++){
     cilinders+= right[i] - pointer;
     pointer = right[i];
  }

  // retornamos al inicio del disco

  cilinders+= pointer - 1;
  pointer = 1;
  // Ahora vamos pora la izquierda nachito
  for(int j = 0; j<left.size(); j++){
    cilinders+= left[j] - pointer;
    pointer = left[j];
  }

  return cilinders;
  
}
int Simulation::calc_Look(std::vector<int> values){
  std::vector<int> right;
  std::vector<int> left;

  sort_array(values);

  for(int i = 0; i<values.size(); i++){
    if(this->head < values[i]){
      right.push_back(values[i]);
    }else{
      left.push_back(values[i]);
    }
  }

  int cilinders = 0;
  // primero servimos la derecha
  int pointer = head;
  for(int i = 0; i<right.size(); i++){
    cilinders+= right[i] -pointer;
    pointer = right[i];
  }

  // tenemos que sortear el arreglo de los de la izquiera

  sort_mayor_menor(left);
  for(int i = 0; i<left.size(); i++){
    cilinders+= pointer - left[i];
    pointer = left[i];
  }

  return cilinders;

}


