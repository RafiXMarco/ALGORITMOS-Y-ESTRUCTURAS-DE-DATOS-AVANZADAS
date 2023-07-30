// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Autor: Marco Napierski
#include <iostream>

#include "dFunction.h"

#ifndef EFUNCTION
#define EFUNCTION

template<class Key>
class ExplorationFunction {
 public:
  virtual unsigned operator()(const Key&,  unsigned) const = 0;
};

template<class Key>
class feLineal : public ExplorationFunction<Key> {
 public:
  unsigned operator()(const Key& k, unsigned i) const override { return i; }
};

template<class Key>
class feQuadratic : public ExplorationFunction<Key> {
 public:
  unsigned operator()(const Key& k, unsigned i) const override { return i * i; }
};

template<class Key>
class feDoubleDispersion : public ExplorationFunction<Key> {
 public:
  feDoubleDispersion(DispersionFunction<Key>* fd, unsigned size) {
    fd_ = fd;
    tableSize_ = size;
  }
  unsigned operator()(const Key& k, unsigned i) const override {
    DispersionFunction<Key>* aux = new fdPseudoRand<Key>(tableSize_);
    return i * aux->operator()(k);
  }
 private:
  unsigned tableSize_;
  DispersionFunction<Key>* fd_;
};

template<class Key>
class feRedispersion : public ExplorationFunction<Key> {
 public:
  feRedispersion(unsigned size) {
    tableSize_ = size;
  }
  unsigned operator()(const Key& k, unsigned i) const override { 
    for (unsigned j = 0; j < i - 1; ++j) srand(k);
    return rand() % tableSize_;
  }
 private:
  unsigned tableSize_;
};

#endif