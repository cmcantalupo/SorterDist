#ifndef st_pivot_vector
#define st_pivot_vector

#include "sorter_threaded.h"

namespace SorterThreadedHelper {
  template <class T>
  class PivotVector {
    private:
      std::vector<T>* pivots_;
    public:
      PivotVector(std::vector<T>::const_iterator begin, const std::vector<T>::const_iterator end, size_t numPivots);
      ~PivotVector();
      void iterators( std::vector<T>::const_iterator &begin, std::vector<T>::const_iterator &end);
      size_t size();
  }
}

#endif
