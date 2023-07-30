
// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Autor: Marco Napierski
#ifndef HEAPSORT_H_
#define HEAPSORT_H_

#include "Ordenacion.h"

template <class Key>
class Heapsort : public SortMethod<Key> {
  public:
    void Sort();
};

/**
 * @brief max heapify
 * 
 * @tparam Key 
 * @param arr 
 * @param i 
 * @param size_ 
 */
template <class Key>
void max_heapify(std::vector<Key>& arr, int i, int size_)
{
    int largest, l = (2*i) + 1, r = l + 1;

    if(l < size_ && arr[l] > arr[i])
        largest = l;
    else
        largest = i;

    if(r < size_ && arr[r] > arr[largest])
        largest = r;

    if(largest != i)
    {
        std::swap(arr[i], arr[largest]);
        max_heapify(arr, largest, size_);
        std::cout << std::endl;
        for (auto a : arr ) std::cout << a << " ";
        std::cout << std::endl;
    }
}
/**
 * @brief biuld max heap
 * 
 * @tparam Key 
 * @param arr 
 */
template <class Key>
void build_max_heap(std::vector<Key>& arr)
{
    for(int i = (arr.size() / 2); i >= 0; i--)
    max_heapify(arr, i, arr.size());
}

/**
 * @brief heapsort
 * 
 * @tparam Key 
 * @param arr 
 */
template <class Key>
void heap_sort(std::vector<Key>& arr)
{
   build_max_heap(arr);
   int sz = arr.size();
   for(int i = arr.size() - 1; i > 0; i--)
   {
        std::swap(arr[0], arr[i]);
        std::cout << std::endl;
        for (auto a : arr ) std::cout << a << " ";
        std::cout << std::endl;
        sz--;
        max_heapify(arr, 0, sz);
    }
}



template <class Key>
void Heapsort<Key>::Sort() {
  std::vector<Key> v = this->seq;
  heap_sort(v);
  std::cout << "\nRESULTADO:\n";
  for (unsigned i = 0;  i < v.size(); i++) {
    std::cout << v[i] << " ";
  }
}





#endif  // HEAPSORT_H_