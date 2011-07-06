#ifndef st_partition_gang_hpp
#define st_partition_gang_hpp

#include "partition.hpp"

namespace SorterThreadedHelper {

  class PartitionGang {
    public:
      PartitionGang(std::vector<double>::iterator begin, 
                    std::vector<double>::iterator end, 
                    size_t numThread=-1, size_t taskFactor=8);
      ~PartitionGang();

      // fills the stacks of each thread's partition 
      // * Spawns Threads *
      void fill();
      // Refills the input vector with the values partitioned 
      // between the pivots by popping all the stacks. 
      // * Spawns Threads *
      void pop();
      // sort the output once it has been filled with the partitions.  
      // * Spawns Threads *
      void sort();
      
    private:
      size_t numThreads_;
      size_t taskFactor_;
      size_t numTasks_;
      std::vector<vector<double>::iterator> taskEnd_;
      std::vector<double>::iterator resultBegin_;
      std::vector<double>::iterator resultEnd_;
      std::vector<Partition*> allPartitions_; // we need a partition for each thread.
      void chunk(size_t numChunk, size_t chunkIndex,
	         std::vector<double>::iterator& chunkBegin,
	         std::vector<double>::iterator& chunkEnd);
      void popTaskBundle(); // spawns threads 

  };

}

#endif
