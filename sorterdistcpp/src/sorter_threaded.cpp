// This is a work in progress.  
// C.M.Cantalupo 

#include "sorter_threaded.hpp"
#include "partition.hpp"
#include "splinter.hpp"
#include "sorter_threaded_exception.hpp"

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
    size_t numThreads = omp_get_max_num_threads();
  }

  numTasks = numThreads_ * taskFactor_;
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
  std::vector<Partition*> allPartitions(numThreads);
  std::vector<std::vector<double>::iterator> chunks;

  size_t i = 0;
  for (std::vector<Partition*>::iterator it = allPartitions.begin();
       it != allPartitions.end(); ++it, ++i) {
    *it = new Partition(pivots);
  }

  splinter.even(numThreads, chunks);

#pragma omp parallel default (none) private (none) shared (allPartitions, splinter, chunks)
{
  int my threadID = omp_get_thread_num();
  allPartitions[threadID]->fill(chunks[myThreadID], chunks[myThreadID+1]);  
  omp_barrier();
  std::vector<size_t> mySizes;
  allPartitions[threadID]->taskSizes(mySizes);

  for (size_t i = 0; i < numThreads; ++i) {
    if (i == threadID) {
      splinter.addSizes(mySizes);
    }
    omp_barrier();
  }

  for (size_t i = 0; i < numThreads; ++i) {
    if (i == threadID) {
      getOffsets(mySizes, offsets);
    }
    omp_barrier();
  }
  
  for (size_t i = 0; i < numTasks; ++i) {
    allPartitions[threadID]->popTask(offsets[i], offsets[i+1]);
  }

  if (threadID == numThreads-1) {
    taskOffsets = offsets;
  }

#pragma omp parallel for schedule (dynamic)
  for (i = 0; i < numTasks; ++i) {
    std::sort(taskOffsets[i], taskOffsets[i+1]);
  }
#endif
}

SorterThreaded::SorterThreaded(size_t taskFactor, size_t numThreads) :
  taskFactor_(taskFactor), 
  numThreads_(numThreads) {}


                                


