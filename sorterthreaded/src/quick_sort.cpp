#include "quick_sort.hpp"

namespace SorterThreadedHelper {

  std::vector<double>::iterator part(std::vector<double>::iterator begin, 
                                     std::vector<double>::iterator end, double value) {
    // cribbed from the explaination of STL partition
    while (true) {
      while (begin != end && *begin < value) ++begin;
      if (begin == end--) break;
      while (begin != end && !(*end < value)) --end;
      if (begin == end) break;
      std::swap(*begin++, *end);
    }
    return begin;
  }

  // not sure if STL copy is thread safe
  void ts_copy(std::vector<double>::iterator begin, 
               std::vector<double>::iterator end,
               std::vector<double>::iterator result) {
    while (begin != end) {
      *result = *begin;
      ++result;
      ++begin;
    }
  }

  // STL sort is not thread safe, so we need to roll our own
  void quick_sort(std::vector<double>::iterator begin, 
                  std::vector<double>::iterator end) {
    // Recursive implementation of the quick sort algorithm
    // If the vector has less than two elements return
    if (distance(begin, end) < 2){
      return;
    }
    std::vector<double>::iterator bound;
    double beginVal = *begin;
    bound = part(begin+1, end, beginVal);
    ts_copy(begin + 1, bound, begin);
    *(bound-1) = beginVal;
    quick_sort(begin, bound-1);
    quick_sort(bound, end);
  }
}
