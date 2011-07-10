#ifndef st_sorter_threaded_hpp
#define st_sorter_threaded_hpp

#include <string>
#include <vector>
#include <algorithm>
#ifdef _OPENMP
#include <omp.h>
#include <iostream>
#endif
#include "sorter_threaded.hpp"
#include "partition.hpp"
#include "splinter.hpp"
#ifndef STL_SORT_THREAD_SAFE
#include "quick_sort.hpp"
#endif

template <class type>
class SorterThreaded {
  public:
    SorterThreaded(int taskFactor=8, int maxThreads=-1);
    void sort(typename std::vector<type>::iterator begin, 
              typename std::vector<type>::iterator end);
    void setTaskFactor(int taskFactor);
    void setMaxThreads(int maxThreads);
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

template <class type>
void SorterThreaded<type>::sort(typename std::vector<type>::iterator begin, 
                          typename std::vector<type>::iterator end) {
  // To achieve parallelism here we will choose a set of pivots from 
  // the list to be sorted.  Here we will just choose the first elements
  // in the vector.  The number of pivots will determine the number of 
  // tasks to be done: one more task than the number of pivots. 
  //
  // For simplicity here we will choose the number of tasks to be 
  // a factor of the number of threads.  This will be determined 
  // by the class attribute taskFactor_.  
  //
  // We need to break down the main scaling dimension of the problem,
  // the length of the input vector.  The first thing that we want to
  // do with the input is to partition it into intervals bounded by
  // the pivots.  This can be done with the std::set.upper_bound() to
  // partition the input vector.  In the end we want taskFactor_ times
  // the number of threads jobs and we need one fewer pivot than that
  // to do so.  Bundle up the pivots with a stack and put them in a
  // std::set along with a dummy pivot for the end.  We will
  // call this class "PartitionWall." The set provides a upper_bound
  // bound function so we need to overload less than.
  // 

#ifndef _OPENMP
  std::sort(begin, end);
#else
  int numThreads = omp_get_max_threads();

  if (maxThreads_ != -1 && maxThreads_ < numThreads) {
    numThreads = maxThreads_;
  }

  if (numThreads == 1) {
    std::sort(begin,end);
    return;
  }

  int numTasks = numThreads * taskFactor_;

  std::set<type> pivots;
  // Create a set of pivots by going through the vector    
  for (typename std::vector<type>::iterator it = begin;
       it != end && pivots.size() < numThreads*taskFactor_ - 1;
       ++it) {
      pivots.insert(*it);
  }
  // Check that there were as many unique values as we need
  if (pivots.size() < numThreads * taskFactor_ - 1) {
    std::sort(begin, end);
    return;
  }
  
  SorterThreadedHelper::Splinter<type> splinter(begin, end, numTasks);
  std::vector<typename std::vector<type>::iterator> chunks;

  splinter.even(numThreads, chunks);

  std::vector<typename std::vector<type>::iterator> taskOffsets(numTasks);
#pragma omp parallel default (shared) num_threads (numThreads)
{
  int threadID = omp_get_thread_num();
  SorterThreadedHelper::Partition<type> partition(pivots);
  partition.fill(chunks[threadID], chunks[threadID+1]);
  std::vector<size_t> mySizes;
  partition.taskSizes(mySizes);

  for (int i = 0; i < numThreads; ++i) {
    if (i == threadID) {
      splinter.addSizes(mySizes);
    }
#pragma omp barrier
  }

  std::vector<typename std::vector<type>::iterator> offsets;
  for (int i = 0; i < numThreads; ++i) {
    if (i == threadID) {
      splinter.getOffsets(mySizes, offsets);
    }
#pragma omp barrier
  }
  
  for (int i = 0; i < numTasks; ++i) {
    partition.popTask(offsets[i]);
  }

  if (threadID == numThreads - 1) {
    std::copy(offsets.begin(), offsets.end(), taskOffsets.begin());
  }
}

#pragma omp parallel for schedule (dynamic) num_threads(numThreads) default(shared)
  for (int i = 0; i < numTasks; ++i) {
    if (i != numTasks - 1) {
#ifdef STL_SORT_THREAD_SAFE
      std::sort(taskOffsets[i], taskOffsets[i+1]);
#else
      SorterThreadedHelper::quick_sort<type>(taskOffsets[i], taskOffsets[i+1]);
#endif
    }
    else {
#ifdef STL_SORT_THREAD_SAFE
      std::sort(taskOffsets[numTasks - 1], end);
#else
      SorterThreadedHelper::quick_sort<type>(taskOffsets[numTasks - 1], end);
#endif
    }
  }
#endif //end of #ifdef _OPENMP
}

template <class type>
SorterThreaded<type>::SorterThreaded(int taskFactor, int maxThreads) :
  taskFactor_(taskFactor), 
  maxThreads_(maxThreads) {}

template <class type>
void SorterThreaded<type>::setMaxThreads(int maxThreads) {
  maxThreads_ = maxThreads;
}

template <class type>
void SorterThreaded<type>::setTaskFactor(int taskFactor) {
  taskFactor_ = taskFactor;
}

#endif
