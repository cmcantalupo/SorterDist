#ifndef st_partition_hpp
#define st_partition_hpp

#include <set>
#include "sorter_threaded.hpp"
#include "pivot_vector.hpp"
#include "partition_wall.hpp"

namespace SorterThreadedHelper {

  class Partition {
    public:
      Partition(const std::set<double> &pivots, 
                std::vector<double>::iterator chunkBegin, 
                std::vector<double>::iterator chunkEnd); 
      void fillPartition(); //single threaded

    private:
      std::vector<double>::iterator chunkBegin_;
      std::vector<double>::iterator chunkEnd_;
      std::set<PartitionWall> *partition_;
  };

}

#endif
  
