#ifndef st_partition_hpp
#define st_partition_hpp

#include <set>
#include <vector>
#include <map>
#include "partition_wall.hpp"

namespace SorterThreadedHelper {

  class Partition {
    public:
      Partition(const std::set<double>& pivots,
                const std::vector<double>::iterator chunkBegin, 
                const std::vector<double>::iterator chunkEnd);
      ~Partition(); 
      void fillPartition(); //single threaded
      void popTask(std::vector<double>::iterator resultBegin);
      void stackSizes(std::vector<size_t>::iterator begin, 
                      std::vector<size_t>::iterator end);

    private:
      const std::vector<double>::iterator chunkBegin_;
      const std::vector<double>::iterator chunkEnd_;
      std::map<PartitionWall,std::stack<double>*> partition_;
      std::map<PartitionWall,std::stack<double>*>::iterator taskIt_;

  };



}

#endif
  
