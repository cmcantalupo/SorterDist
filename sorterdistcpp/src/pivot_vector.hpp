#ifndef st_pivot_vector
#define st_pivot_vector

#include "sorter_threaded.hpp"

namespace SorterThreadedHelper {

  class PivotVector {
    private:
      std::vector<double>* pivots_;
    public:
      PivotVector(std::vector<double>::const_iterator begin, const std::vector<double>::const_iterator end, size_t numPivots);
      ~PivotVector();
      void iterators( std::vector<double>::const_iterator &begin, std::vector<double>::const_iterator &end);
      size_t size();
  };
}

#endif
