// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Autor: Marco Napierski
#ifndef RADIXSORT_H_ 
#define RADIXSORT_H_

#include "Ordenacion.h"

template <class Key>
class Radixsort : public SortMethod<Key> {
  public:
    void Sort();
};


// Función para obtener el dígito en la posición d
int getDigit(int num, int d) {
    int div = pow(10, d-1);
    return (num / div) % 10;
}

// Función que implementa el algoritmo de ordenamiento radix sort
void rs(vector<int>& arr) {
    // Obtener el número máximo del vector
    int maxNum = *max_element(arr.begin(), arr.end());
    
    // Contar el número de dígitos del número máximo
    int numDigits = log10(maxNum) + 1;
    
    // Ordenar el vector por cada dígito, comenzando desde el dígito menos significativo
    for (int d = 1; d <= numDigits; d++) {
        // Crear un vector de contadores para cada posible valor del dígito
        vector<int> count(10);
        
        // Contar el número de elementos con cada valor del dígito actual
        for (int i = 0; i < arr.size(); i++) {
            int digit = getDigit(arr[i], d);
            count[digit]++;
        }
        
        // Calcular las posiciones finales de los elementos en el vector ordenado
        for (int i = 1; i < 10; i++) {
            count[i] += count[i-1];
        }
        
        // Crear un vector temporal para almacenar el vector ordenado por el dígito actual
        vector<int> temp(arr.size());
        
        // Ordenar el vector por el dígito actual
        for (int i = arr.size()-1; i >= 0; i--) {
            int digit = getDigit(arr[i], d);
            int pos = count[digit] - 1;
            temp[pos] = arr[i];
            count[digit]--;
        }
        
        // Actualizar el vector original con el vector temporal ordenado por el dígito actual
        for (int i = 0; i < arr.size(); i++) {
            arr[i] = temp[i];
        }
        std::cout << std::endl;
        for (auto a : arr ) std::cout << a << " ";
        std::cout << std::endl;
    }
}

template <class Key>
void Radixsort<Key>::Sort() {
  std::vector<Key> v = this->seq;
  rs(v);
  std::cout << "\nRESULTADO:\n";
  for (unsigned i = 0;  i < v.size(); i++) {
    std::cout << v[i] << " ";
  }
}

#endif // RADIXSORT_H_