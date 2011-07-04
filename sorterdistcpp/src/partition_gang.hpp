#ifndef st_partition_gang_hpp
#define st_partition_gang_hpp

#include "sorter_threaded.h"

namespace SorterThreadedHelper {

  template <class T>
  class PartitionGang {
    private:
      PivotVector pivots_;
      std::vector<T>::iterator resultBegin_;
      std::vector<T>::iterator resultEnd_;
      std::vector<Partition<T>*>* allPartitions; // we need a partition for each thread.
      void chunk(size_t numChunk, size_t chunkIndex,
	         std::vector<T>::iterator& chunkBegin,
	         std::vector<T>::iterator& chunkEnd);
    public:
      PartitionGang(std::vector<T>::iterator begin, std::vector<T>::iterator end, 
                    size_t numThread, size_t threadFactor);
      ~PartitionGang();

      // fills the stacks of each thread's partition 
      void fillPartitions(); //spawns threads
      // Refills the input vector with the values partitioned 
      // between the pivots by popping all the stacks.  
      void fillOutput(); // spawns threads 
      // sort the output once it has been filled with the partitions.  
      void sortOutput(); // spawns threads
  };  

}

#endif
