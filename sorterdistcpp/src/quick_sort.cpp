#include "quick_sort.hpp"


std::vector<double>::iterator part(std::vector<double>::iterator begin, 
                                   std::vector<double>::iterator end, double value) {
  // cribbed from the explaination of STL partition
  while (true) {
    while (begin != end && *begin < value) ++begin;
    if (begin == end--) break;
    while (begin != end && !(*begin < value)) --end;
    if (begin == end) break;
    std::swap(*begin++, *end);
  }
  return begin;
}

void mquick_sort(std::vector<double>::iterator begin, 
                std::vector<double>::iterator end) {
  // Recursive implementation of the quick sort algorithm
  // If the vector has less than two elements return
  if ( distance(begin, end) < 2 ){
    return;
  }

  std::vector<double>::iterator bound;
  double beginVal = *begin;
  bound = part(begin+1, end, beginVal);
  copy(begin+1, bound, begin);
  *bound = beginVal;
  mquick_sort(begin, bound);
  mquick_sort(bound+1, end);
}
