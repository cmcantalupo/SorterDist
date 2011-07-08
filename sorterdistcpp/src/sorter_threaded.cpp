// This is a work in progress.  
// C.M.Cantalupo 

#include <algorithm>
#ifdef _OPENMP
#include "omp.h"
#endif
#include "sorter_threaded.hpp"
#include "partition.hpp"
#include "splinter.hpp"
#include "sorter_threaded_exception.hpp"

using namespace SorterThreadedHelper;

void SorterThreaded::sort(std::vector<double>::iterator begin, 
                          std::vector<double>::iterator end) {
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
  if (numThreads_ == -1) {
    numThreads_ = omp_get_max_threads();
  }

  size_t numTasks = numThreads_ * taskFactor_;
  std::vector<double>::iterator chunkBegin;
  std::vector<double>::iterator chunkEnd;
  std::set<double> pivots;

  // Create a set of pivots by going through the vector    
  for (std::vector<double>::iterator it = begin;
       it != end && pivots.size() < numThreads_*taskFactor_ - 1;
       ++it) {
      pivots.insert(*it);
  }
  // Check that there were as many unique values as we need
  if (pivots.size() < numThreads_ * taskFactor_ - 1) {
    std::sort(begin, end);
    return;
  }
  
  Splinter splinter(begin, end);
  std::vector<std::vector<double>::iterator> chunks;

  splinter.even(numThreads_, chunks);

  std::vector<std::vector<double>::iterator> taskOffsets;
#pragma omp parallel default (none) private (none) shared (splinter, chunks, taskOffsets)
{
  int threadID = omp_get_thread_num();
  Partition partition(pivots);
  partition.fill(chunks[threadID], chunks[threadID+1]);
#pragma  omp barrier;
  std::vector<size_t> mySizes;
  partition.taskSizes(mySizes);

  for (size_t i = 0; i < numThreads_; ++i) {
    if (i == threadID) {
      splinter.addSizes(mySizes);
    }
#pragma omp barrier
  }

  std::vector<std::vector<double>::iterator> offsets;
  for (size_t i = 0; i < numThreads_; ++i) {
    if (i == threadID) {
      splinter.getOffsets(mySizes, offsets);
    }
#pragma omp barrier
  }
  
  for (size_t i = 0; i < numTasks; ++i) {
    partition.popTask(offsets[i]);
  }

  if (threadID == numThreads_ - 1) {
    taskOffsets = offsets;
  }

#pragma omp parallel for schedule (dynamic)
  for (size_t i = 0; i < numTasks - 1; ++i) {
    std::sort(taskOffsets[i], taskOffsets[i+1]);
  }
#pragma omp critical
{
  std::sort(taskOffsets[numTasks - 1], end);
} //end omp critical region
} //end omp parallel region
#endif
}

SorterThreaded::SorterThreaded(int taskFactor, int numThreads) :
  taskFactor_(taskFactor), 
  numThreads_(numThreads) {}


                                


