#ifndef st_partition_hpp
#define st_partition_hpp

#include <set>
#include <vector>
#include <map>
#include "partition_wall.hpp"

namespace SorterThreadedHelper {
  // Each thread will have a partition and the members will
  // be single threaded functions.  
  class Partition {
    public:
      // A partition is created with a set of pivots.  There are
      // pivots.size() + 1 tasks. Each task is a stack of values less
      // than the pivot for the first tasks, and the last task is a
      // stack of values larger than any of the pivots.
      Partition(const std::set<double>& pivots);
      Partition(const Partition& other);
      ~Partition();

      // Pushes all of the values in a chunk onto the partition
      // stacks.
      void fillPartition(std::vector<double>::const_iterator begin,
                         std::vector<double>::const_iterator end);

      // Returns all of the values in the current task.  
      void popTask(std::vector<double>::iterator begin,
                   std::vector<double>::iterator end);

      // Returns the number of tasks (the size of the original pivot
      // set plus one).
      size_t numTasks();

      // Returns the index of the next task that will be popped by 
      // popTask().  
      size_t curTask();

      // Returns the size of the next task that will be popped by 
      // popTask().
      size_t curSize();

      // Returns the sizes of all of the tasks.  
      void taskSizes(std::vector<size_t>::iterator begin, 
                     std::vector<size_t>::iterator end);

    private:
      size_t numTasks_;
      size_t curTask_;
      std::map<PartitionWall,std::stack<double>*> partition_;
      std::map<PartitionWall,std::stack<double>*>::iterator curTaskIt_;
  };
}

#endif
  
