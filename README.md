# CCI-0122 Sistemas Operativos

## Tarea Programada I: HDD Scheduling

Integrantes:
- Diego Cerdas *carnet*
- Enrique Bermúdez B81083

### Instrucciones
Para esta tarea, debe trabajar en un programa que reciba una cadena de solicitudes de
acceso a bloques de un disco, el algoritmo a utilizar, la posición en la que se encuentra la cabeza de
lectura y la dirección en la que va leyendo. Tome en cuenta que la cadena de solicitudes y el algoritmo
son parámetros obligatorios, mientras que los siguientes dos parámetros podrían no indicarse,
por lo que su programa debe tener la capacidad de asumir valores por defecto para estos dos.

En este caso, los algoritmos, cuya funcionalidad debe programar, son:

- FCFS
- SSTF
- Scan
- C-Scan
- Look
- C-Look

Entonces, asuma que su programa puede recibir una entrada como la siguiente:

    98, 183, 37, 122, 14, 124, 65, 67 | FCFS | Head:53 | ASC

Su programa debe dar como resultado la cantidad de cilindros
que fueron recorridos para lograr suplir todas las necesidades, 
como se muestra a continuación:

    “Total del recorrido: 640”

## Compilación y Ejecución

  - Asegurarse de estar en la siguiente ruta:
  ci-0123-proyecto-integrador-de-redes-y-sistemas-operativos/Primera-etapa/Simulacion

1. Para compilar, escriba los comandos:
    
            g++ main.cpp Simulation.cpp -o simulation

2. Para ejecutar:
    
            ./simulation

## Compilación para Pruebas

// TO DO