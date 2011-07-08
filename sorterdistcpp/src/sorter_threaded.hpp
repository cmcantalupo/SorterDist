#ifndef st_sorter_threaded_hpp
#define st_sorter_threaded_hpp

#include <string>
#include <vector>

class SorterThreaded {
  public:
    SorterThreaded(int taskFactor=8, int numThreads=-1);
    void sort(std::vector<double>::iterator begin, 
              std::vector<double>::iterator end);
    void setTaskFactor(size_t taskFactor);
    void setNumThreads(size_t numThreads);
  private:
    int taskFactor_;
    // If numThreads_ == -1 then omp_max_num_threads will be used
    int maxThreads_;
};


  // We need to break the input vector into nearly equal size chunks
  // for partitioning.  One chunk for each thread. 
  //
  // We can builid up a Partition from an array of non-repeating 
  // values (pivots) from the input vector.  
  //
  // Each thread will have and make its own Partition.  These will be
  // OpenMP private.  Each partition has a stack for each thread and
  // each task.  This implies that the total number of stacks over all
  // threads is numThreads^3 * taskFactor_.
  //
  // The threads will be managed by the PartitionGang.  This class
  // will hold all of the Partitions and will be the class to 
  // spawn threads.  
  //

#endif
