// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Autor: Marco Napierski
#ifndef ORDENACION_H_
#define ORDENACION_H_

using namespace std;

#include <vector>
#include <iostream>
#include <math.h>
#include <algorithm>

double ALFA;
int contador;

template <class Key>
class SortMethod {
  protected:
    unsigned size;
    std::vector<Key> seq;
  public:
    void set_seq(std::vector<Key>v) {seq = v; size = v.size();}
    // void print() {
    //   std::cout << "--------*--------\n";
    //   for (unsigned i = 0; i < seq.size();i++) {
    //     std::cout << seq[i] << " ";
    //   }
    //   std::cout << "--------^--------\n";
    // }
    virtual void Sort( ) = 0;
};

#endif // ORDENACION_H_