#ifndef st_partition_hpp
#define st_partition_hpp

#include <set>
#include <vector>
#include "partition_wall.hpp"

namespace SorterThreadedHelper {

  class Partition {
    public:
      Partition(const std::set<double>& pivots,
                const std::vector<double>::iterator chunkBegin, 
                const std::vector<double>::iterator chunkEnd); 
      void fillPartition(); //single threaded

    private:
      const std::vector<double>::iterator chunkBegin_;
      const std::vector<double>::iterator chunkEnd_;
      std::set<PartitionWall> partition_;
  };

}

#endif
  
