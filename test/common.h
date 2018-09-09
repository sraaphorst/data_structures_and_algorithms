/**
 * common.h
 *
 * By Sebastian Raaphorst, 2018.
 */

#pragma once

#include <cmath>
#include <type_traits>

#define NUM_TRIALS 2000
#define RUN_TRIALS(x) {for (size_t i = 0; i < NUM_TRIALS; ++i) { (x); }}

template <typename T = double> constexpr T tolerance = 1e-5;

template<typename T>
std::enable_if_t<std::is_arithmetic_v<T>, bool>
ALMOST_EQUALS(T first, T second) {
    return abs(first - second) < tolerance<T>;
}