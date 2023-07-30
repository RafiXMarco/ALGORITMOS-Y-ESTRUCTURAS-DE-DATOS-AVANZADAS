// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Autor: Marco Napierski

#include <iostream>

#include "HashTable.h"
//#include "persona.h"

int main() {
  int tableSize;
  int blockSize{0};
  int blockSizea{0};
  int op_fd, op_fe, op_fea , op_seq;
  DispersionFunction<long>* fd;
  ExplorationFunction<long>* fe = NULL;
  std::cout << "tamaño de la tabla: ";
  std::cin >> tableSize;

  std::cout << "tipo de dispersión: ";
  std::cout << "\n1 Dispersión Abierta (Lista)";
  std::cout << "\n2 Dispersión Cerrada (Bloque)";
  std::cout << std::endl;
  std::cin >> op_seq; 


  std::cout << "función de dispersión: ";
  std::cout << "\n1 Módulo";
  std::cout << "\n2 Basada en la Suma";
  std::cout << "\n3 Pseudoaleatoria";
  std::cout << std::endl;
  std::cin >> op_fd;
  switch(op_fd) {
    case 1:
      fd = new fdModule<long>(tableSize);
      break;
    case 2:
      fd = new fdSum<long>(tableSize);
      break;
    case 3:
      fd = new fdPseudoRand<long>(tableSize);
      break;
    default:
      std::cerr << "Opción no válida. Terminando el programa.\n";
      return 1;
  }

  if (op_seq == 2) {
    std::cout << "tamaño del bloque: ";
    std::cin >> blockSize;
    std::cout << "función de exploración: ";
    std::cout << "\n1 Lineal";
    std::cout << "\n2 Cuadrática";
    std::cout << "\n3 Doble Dispersión";
    std::cout << "\n4 Redispersión";
    std::cout << std::endl;
    std::cin >> op_fe;
    switch(op_fe) {
      case 1:
        fe = new feLineal<long>();
        break;
      case 2:
        fe = new feQuadratic<long>();
        break;
      case 3:
        fe = new feDoubleDispersion<long>(fd, tableSize);
        break;
      case 4:
        fe = new feRedispersion<long>(tableSize);
        break;
      default:
        std::cerr << "Opción no válida. Terminando el programa.\n";
        return 1;
    }
  }
  HashTable<long> table(tableSize, fd, fe, blockSize);
  std::cout << "Operaciones con la tabla Hash";
  int op_hash;
  while (true) {
    long element;
    std::cout << "\n0 Salir del programa";
    std::cout << "\n1 Insertar elemento";
    std::cout << "\n2 Buscar elemento";
    std::cout << std::endl;
    std::cin >> op_hash;
    if (op_hash == 0) break;
    if (op_hash == 1) {
      std::cout << "insertar: ";
      std::cin >> element;
      if (table.insert(element)) {
        std::cout << "Elemento " << element << " INSERTADO.";
        std::cout << std::endl;
      } else {
        std::cout << "El elemento ya estaba insertado o la tabla Hash esta llena.";
        std::cout << std::endl;
      }
    } else if (op_hash == 2) {
      std::cout << "buscar: ";
      std::cin >> element;
      if (!table.search(element)) {
        std::cout << "El elemento " << element << " NO ENCONTRADO";
      } else {
        std::cout << "Elemento encontrado.";
        std::cout << std::endl;
      }
    } else {
      std::cerr << "Opción no válida.";
      std::cout << std::endl;
    }
    //table.print();
    std::cout << "\n--------------------------------------\n";
  }

  return 0;
}