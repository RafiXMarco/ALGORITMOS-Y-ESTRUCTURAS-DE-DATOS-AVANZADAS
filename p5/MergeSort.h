// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Autor: Marco Napierski
#ifndef MERGESORT_H_
#define MERGESORT_H_

#include "Ordenacion.h"

template <class Key>
class MergeSort : public SortMethod<Key> {
  public:
    void Sort();
};
/**
 * @brief merge sort
 * 
 * @param vec 
 * @param left 
 * @param mid 
 * @param right 
 */
void merge(vector<int>& vec, int left, int mid, int right) {
    std::cout << std::endl;
    for (auto a : vec ) std::cout << a << " ";
    std::cout << std::endl;
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1);
    vector<int> R(n2);

    for (i = 0; i < n1; i++)
        L[i] = vec[left + i];
    for (j = 0; j < n2; j++)
        R[j] = vec[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vec[k] = L[i];
            i++;
        }
        else {
            vec[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        vec[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        vec[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& vec, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);

        merge(vec, left, mid, right);
    }
}


template <class Key>
void MergeSort<Key>::Sort() {
  std::vector<Key> v = this->seq;
  mergeSort(v, 0, v.size() - 1);
  std::cout << "\nRESULTADO:\n";
  for (unsigned i = 0;  i < v.size(); i++) {
    std::cout << v[i] << " ";
  }
}


#endif  // MERGESORT_H_