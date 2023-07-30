
// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Autor: Marco Napierski
#ifndef INSERCION_H_
#define INSERCION_H_

#include "Ordenacion.h"
#include <iostream>

template <class Key>
class Insercion : public SortMethod<Key> {
  private:
    int contador_;
  public:
    int get_moves() {return contador_;}
    void Sort();
};

/**
 * @brief ordenacion de insercion
 * 
 * @param v 
 */
void ordenarInsercion(vector<int>& v) {
  int n = v.size();
  for (int i = 1; i < n; i++) {
    int j = i;
    while (j > 0 && v[j - 1] > v[j]) {
      swap(v[j], v[j - 1]);
      j--;
        std::cout << std::endl;
        for (auto a : v ) std::cout << a << " ";
        contador++;
        std::cout << std::endl;
    }
  }
}


template <class Key>
void Insercion<Key>::Sort() {
  std::vector<Key> v = this->seq;
  ordenarInsercion(v);
  this->contador_ = contador;
  std::cout << "\nRESULTADO:\n";
  for (unsigned i = 0;  i < v.size(); i++) {
    std::cout << v[i] << " ";
  }



    std::cout << "\n CONTADOR:";
    std::cout << this->get_moves();
    std::cout << "\n ";
}


#endif // INSERCION_H_