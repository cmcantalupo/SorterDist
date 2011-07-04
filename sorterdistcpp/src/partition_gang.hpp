#ifndef st_partition_gang_hpp
#define st_partition_gang_hpp

#include "sorter_threaded.hpp"
#include "partition.hpp"

namespace SorterThreadedHelper {

  class PartitionGang {
    private:
      size_t numThreads_; 
      size_t taskFactor_;
      std::set<double> pivots_;
      std::vector<double>::iterator resultBegin_;
      std::vector<double>::iterator resultEnd_;
      std::vector<Partition*>* allPartitions_; // we need a partition for each thread.
      void chunk(size_t numChunk, size_t chunkIndex,
	         std::vector<double>::iterator& chunkBegin,
	         std::vector<double>::iterator& chunkEnd);
    public:
      PartitionGang(std::vector<double>::iterator begin, std::vector<double>::iterator end, 
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
