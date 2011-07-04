#ifndef st_partition_hpp
#define st_partition_hpp

#include <set>
#include "sorter_threaded.hpp"
#include "pivot_vector.hpp"

namespace SorterThreadedHelper {

  class Partition {
    private:
      std::vector<double>::iterator chunkBegin_;
      std::vector<double>::iterator chunkEnd_;
      std::set<PartitionWall> *partition_;
    public:
    Partition(const PivotVector &pivots, 
              std::vector<double>::const_iterator chunkBegin, 
              std::vector<double>::const_iterator chunkEnd); 
    void fillPartition(); //single threaded
  };

}

#endif
