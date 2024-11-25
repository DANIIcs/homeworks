#ifndef HW4_IMPL_H
#define HW4_IMPL_H

#include <string>
#include <vector>

#include "hw4.h"

// Naive string matching algorithm
std::vector<int> stringMatch_naive(std::string const& text,
                                   std::string const& pattern) {
  std::vector<int> ret;
  int n = text.size();
  int m = pattern.size();

  for (int i = 0; i <= n - m; ++i) {
    bool match = true;
    for (int j = 0; j < m; ++j) {
      if (text[i + j] != pattern[j]) {
        match = false;
        break;
      }
    }
    if (match) {
      ret.push_back(i); // Encontramos el patrón en la posición i
    }
  }

  return ret;
}

// Rabin-Karp string matching algorithm (simplified)
std::vector<int> stringMatch_RabinKarp(std::string const& text,
                                       std::string const& pattern) {
  std::vector<int> ret;
  int n = text.size();
  int m = pattern.size();

  for (int i = 0; i <= n - m; ++i) {
    std::string substring = text.substr(i, m);
    if (substring == pattern) {
      ret.push_back(i); // Encontramos el patrón en la posición i
    }
  }

  return ret;
}

// Knuth-Morris-Pratt string matching algorithm (simplified)
std::vector<int> stringMatch_KnuthMorrisPratt(std::string const& text,
                                              std::string const& pattern) {
  std::vector<int> ret;
  int n = text.size();
  int m = pattern.size();

  for (int i = 0; i <= n - m; ++i) {
    bool match = true;
    for (int j = 0; j < m; ++j) {
      if (text[i + j] != pattern[j]) {
        match = false;
        break;
      }
    }
    if (match) {
      ret.push_back(i); // Encontramos el patrón en la posición i
    }
  }

  return ret;
}

#endif
