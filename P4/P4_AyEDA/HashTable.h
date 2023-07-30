// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Autor: Marco Napierski
#ifndef HASHTABLE
#define HASHTABLE

#include "Sequence.h"
#include "dFunction.h"
#include "eFunction.h"

template<class Key>
class HashTable {
 public:
  HashTable();
  HashTable(int, DispersionFunction<Key>*, ExplorationFunction<Key>* = NULL, int = 0);
  ~HashTable();
  bool search(const Key&) const;
  bool insert(const Key&);
  void print();
 private:
  int tableSize_;
  Sequence<Key>** table_;
  DispersionFunction<Key>* fd_;
  int blockSize_;
  ExplorationFunction<Key>* fe_;
};

/**
 * @brief Construct a new Hash Table< Key>:: Hash Table object
 * 
 * @tparam Key 
 * @param tableSize 
 * @param fd 
 * @param fe 
 * @param blockSize 
 */
template<class Key>
HashTable<Key>::HashTable(int tableSize, DispersionFunction<Key>* fd, ExplorationFunction<Key>* fe, int blockSize) :  tableSize_(tableSize), fd_(fd), fe_(fe), blockSize_(blockSize) {
  table_ = new Sequence<Key>*[tableSize];
  if (fe_ == NULL) {
    for (int i = 0; i < tableSize_; ++i) table_[i] = new List<Key>();
  } else {
    for (int i = 0; i < tableSize_; ++i) table_[i] = new Block<Key>(blockSize_);
  }
}

/**
 * @brief Destroy the Hash Table< Key>:: Hash Table object
 * 
 * @tparam Key 
 */
template<class Key>
HashTable<Key>::~HashTable() {
  delete[] table_;
}

// template<class Key>
// void HashTable<Key>::print() {
//   for (int i  = 0; i < tableSize_;i++) {
//     for (int j = 0;j<blockSize_;j++) {
//       std::cout << table_[i]->blockElements_;
//     }
//   }
// }

/**
 * @brief search
 * 
 * @tparam Key 
 * @param k 
 * @return true 
 * @return false 
 */
template<class Key>
bool HashTable<Key>::search(const Key& k) const {
  int fd_index = fd_->operator()(k);
  if (blockSize_ == 0) {
    // std::cout << "IN" << "\n";
    // std::cout << fd_index << "\n";
    return table_[fd_index]->search(k);
  } else {
    if (!table_[fd_index]->search(k) || !table_[fd_index]->isFull()) {
      return false;
    } else if (table_[fd_index]->search(k)) {
      return true;
    } else {
      int fe_index = fe_->operator()(k, tableSize_);
      if (!table_[fe_index]->search(k) && table_[fe_index]->isFull()) {
        do {
          fe_index = fe_->operator()(k, fe_index);
          if(table_[fe_index]->search(k)) {
            return true;
          }
        } while (table_[fe_index]->isFull());
      } else {
        return true;
      }
    }
  }
}

/**
 * @brief Insert
 * 
 * @tparam Key 
 * @param k 
 * @return true 
 * @return false 
 */
template<class Key>
bool HashTable<Key>::insert(const Key& k) {
  int fd_index = fd_->operator()(k);
  if (blockSize_ == 0) {
    table_[fd_index]->insert(k);
  } else {
    if (!table_[fd_index]->isFull()) {
      table_[fd_index]->insert(k);
    } else {
      while (fd_index < tableSize_) {
        if (!table_[fd_index]->isFull()) {
          table_[fd_index]->insert(k);
          return true;
        } else {
          ++fd_index;
        }
      }
      return false;
    }
  }
}

#endif