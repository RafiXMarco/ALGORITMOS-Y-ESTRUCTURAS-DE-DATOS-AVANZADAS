// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Autor: Marco Napierski
#include <iostream>

#ifndef DFUNCTION
#define DFUNCTION

template<class Key>
class DispersionFunction {
 public:
  virtual unsigned operator()(const Key&) const = 0;
};

template<class Key>
class fdModule : public DispersionFunction<Key> {
 public:
  fdModule(const unsigned n) : tableSize_(n) {}
  unsigned operator()(const Key& k) const override { return k % tableSize_; }
 private:
  unsigned tableSize_;
};

template<class Key>
class fdSum : public DispersionFunction<Key> {
 public:
  fdSum(const unsigned n) : tableSize_(n) {}
  unsigned operator()(const Key& k) const override { 
    unsigned sum{0};
    unsigned iterator{k};
    unsigned aux;
    while (iterator > 0) {
      aux = iterator % 10;
      sum += aux;
      iterator /= 10;
    }
    return sum % tableSize_;
  }
 private:
  unsigned tableSize_;
};

template<class Key>
class fdPseudoRand : public DispersionFunction<Key> {
 public:
  fdPseudoRand(const unsigned n) : tableSize_(n) {}
  unsigned operator()(const Key& k) const override { 
    srand(k);
    return rand() % tableSize_;
  }
 private:
  unsigned tableSize_;
};

#endif