#ifndef st_partition_hpp
#define st_partition_hpp

#include "sorter_threaded.hpp"

namespace SorterThreadedHelper {

  template <class T>
  class Partition {
    private:
      std::vector<T>::iterator chunkBegin_;
      std::vector<T>::iterator chunkEnd_;
      std::set<PartitionWall<T>> *partition_;
    public:
    Partition(const PivotVector &pivots, 
              std::vector<T>::const_iterator chunkBegin, 
              std::vector<T>::const_iterator chunkEnd); 
    void fillPartition(); //single threaded
  };

}

#endif
