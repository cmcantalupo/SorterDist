#ifndef st_pivot_vector
#define st_pivot_vector

#include "sorter_threaded.hpp"

namespace SorterThreadedHelper {

  class PivotVector {
    public:
      PivotVector(const std::vector<double>::iterator begin, 
                  const std::vector<double>::iterator end, size_t numPivots);
      ~PivotVector();
      void iterators( std::vector<double>::iterator &begin, std::vector<double>::iterator &end);
      size_t size();
    private:
      std::vector<double>* pivots_;

  };

}

#endif
