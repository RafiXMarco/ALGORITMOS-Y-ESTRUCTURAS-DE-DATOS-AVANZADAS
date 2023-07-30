// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Autor: Marco Napierski
#include <stdlib.h>

#include <iostream>

#include "HeapSort.h"
#include "Ordenacion.h"
#include "MergeSort.h"
#include "Insercion.h"
#include "ShellSort.h"
#include "RadixSort.h"

int main() {
  system("clear");
  contador = 0;
  int size;
  int opcion;
  std::cout << "Algoritmos a elegir:\n";
  std::cout << "1. Insercion\n";
  std::cout << "2. MergeSort\n";
  std::cout << "3. ShellSort\n";
  std::cout << "4. HeapSort\n";
  std::cout << "5. RadixSort\n";
  std::cout << "Introduzca una opción (entre el 1 y el 5): ";
  std::cin >> opcion;
  system("clear");
  SortMethod<int>* ordenacion;
  switch (opcion) {
    case 1:
      ordenacion = new Insercion<int>();
      break;
    case 2:
      ordenacion = new MergeSort<int>();
      break;
    case 3:
      std::cout << "Introduzca el valor de alfa (valor entre 0 y 1): ";
      std::cin >> ALFA;
      ordenacion = new ShellSort<int>();
      break;
    case 4:
      ordenacion = new Heapsort<int>();
      break;
    case 5:
      ordenacion = new Radixsort<int>();
      break;
    default:
      break;
  }
  std::cout << "Introduzca el numero de elementos: ";
  std::cin >> size;
  std::vector<int> numeros;
  system("clear");
  // Random generator

  std::cout << "0. introducir los elementos\n";
  std::cout << "1. aleatoriamente\n";
  std::cin >> opcion;
  system("clear");
  switch (opcion) {
    case 0:
      std::cout << "Introduce " << size
                << " valores, intercalados por espacios\n";
      for (int i{0}; i < size; i++) {
        int valor;
        std::cin >> valor;
        numeros.push_back(valor);
      }
      break;
    case 1:
      std::cout << "Elementos seleccionados aleatoriamente\n\n";
      for (int i{0}; i < size; ++i) {
        int num;
        num = 1 + rand() % (10000 - 1000);
        numeros.push_back(num);
      }
      break;
  }

  system("clear");
  // Ejecuto el algoritmo de odenar
  std::cout << "NUMEROS SELECCIONADOS:\n";
  for (auto a : numeros ) std::cout << a << " ";
  std::cout << "\n\n SORT: \n";
  ordenacion->set_seq(numeros);
  ordenacion->Sort();
  //ordenacion->print();


  return 0;
}