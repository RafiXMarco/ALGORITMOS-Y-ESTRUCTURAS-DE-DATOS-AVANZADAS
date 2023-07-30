// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Autor: Marco Napierski
#ifndef SHELLSORT_H_ 
#define SHELLSORT_H_

#include "Ordenacion.h"
template <class Key>
class ShellSort : public SortMethod<Key> {
  public:
    void Sort();
};

/**
 * @brief shellsort
 * 
 * @param nums 
 * @param alfa 
 */
void shellsort(vector<int>& nums, double alfa) {
    int n = nums.size();   
    int gap = n/2;
    while (gap > 0) {
        for (int i = gap; i < n; i++) {
            int temp = nums[i];
            int j = i;
            while (j >= gap && nums[j - gap] > temp) {
                nums[j] = nums[j - gap];
                j -= gap;
            }
            nums[j] = temp;
        }
        gap = static_cast<int>(alfa * gap);
        std::cout << std::endl;
        for (auto a : nums ) std::cout << a << " ";
        std::cout << std::endl;
    }
}

template <class Key>
void ShellSort<Key>::Sort() {
  std::vector<Key> v = this->seq;
  shellsort(v, ALFA);
  std::cout << "\nRESULTADO:\n";
  for (unsigned i = 0;  i < v.size(); i++) {
    std::cout << v[i] << " ";
  }
}


#endif // SHELLSORT_H_