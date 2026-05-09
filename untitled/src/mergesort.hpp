#ifndef MERGESORT_HPP
#define MERGESORT_HPP

#include <vector>
#include "solicitud.hpp"

void mergeSort(std::vector<Solicitud>& arr, int izq, int der);

void merge(std::vector<Solicitud>& arr, int izq, int medio, int der);

#endif