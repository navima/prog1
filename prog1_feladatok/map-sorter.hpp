#pragma once

#include <map>
#include <iostream>
#include <vector>
#include <algorithm>


template <typename T>
void valueSort(std::map<T, T>& map);

template <typename First, typename Second>
std::vector<std::pair<First, Second>> sort_map(const std::map<First, Second>& rank);

template <typename First, typename Second>
void print(std::map<First, Second>& map);

void test();