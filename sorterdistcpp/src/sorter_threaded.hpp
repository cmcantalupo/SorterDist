#ifndef st_sorter_threaded_hpp
#define st_sorter_threaded_hpp
#include <string>
#include <vector>


// The direct use of the STL template of templated containers is not allowed.
// This needs to be fixed.  


template <class kind>
class SorterThreaded {
  public:
    SorterThreaded(size_t taskFactor=8, size_t numThreads=-1);
    void sort(std::vector<kind>::iterator begin, 
              std::vector<kind>::iterator end);
    void setTaskFactor(size_t taskFactor);
    void setNumThreads(size_t numThreads);
  private:
    size_t taskFactor_;
    // If numThreads_ == -1 then omp_max_num_threads will be used
    size_t numThreads_;
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
