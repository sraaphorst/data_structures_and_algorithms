/**
 * fractional_knapsack.h
 *
 * By Sebastian Raaphorst, 2018.
 */

#pragma once

#include <vector>
using std::vector;

double get_optimal_value(int capacity, const vector<int> &weights, const vector<int> &values);