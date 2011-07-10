#ifndef quick_sort_hpp
#define quick_sort_hpp
#include <vector>

namespace SorterThreadedHelper {

  void quick_sort(std::vector<double>::iterator begin, 
                  std::vector<double>::iterator end);

  std::vector<double>::iterator part(std::vector<double>::iterator begin, 
                                     std::vector<double>::iterator end, double value);

  void ts_copy(std::vector<double>::iterator begin, 
               std::vector<double>::iterator end,
               std::vector<double>::iterator result);
}
#endif
