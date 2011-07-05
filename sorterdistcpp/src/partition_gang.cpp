#include "sorter_threaded.hpp"
#include "partition_gang.hpp"
#include "partition.hpp"

namespace SorterThreadedHelper {

  PartitionGang::PartitionGang(std::vector<double>::iterator begin, 
                               std::vector<double>::iterator end, 
			       size_t numThreads, size_t taskFactor) :
    resultBegin_(begin),
    resultEnd_(end),
    numThreads_(numThreads),
    taskFactor_(taskFactor), 
    numTasks_(numThreads*taskFactor) {
    std::vector<double>::iterator chunkBegin;
    std::vector<double>::iterator chunkEnd;

    // Create a set of pivots by going through the vector    
    for (std::vector<double>::iterator it = begin;
         it != end && pivots_.size() < numThreads_*taskFactor_ - 1;
         ++it) {
      pivots_.insert(*it);
    }
    // Check that there were as many unique values as we need
    if (pivots_.size() < numThreads_*taskFactor_ - 1) {
      throw(SorterThreadedException::TooFewPivots);
    }      

    // Now create partition with empty stacks for each thread
    allPartitions_.resize(numThreads);
    size_t i = 0;
    for (std::vector<Partition*>::iterator it = allPartitions_.begin();  
         it != allPartitions_.end(); ++it, ++i) {
      chunk(numThreads, i, chunkBegin, chunkEnd);
      *it = new Partition(pivots_, chunkBegin, chunkEnd);
    }
  }
  PartitionGang::~PartitionGang() {
    // delete each of the partitions.  
    for (std::vector<Partition*>::iterator it = allPartitions_.begin();
         it < allPartitions_.end(); ++it) {
      delete *it;
    }
  }

  void PartitionGang::fillPartitions() {    
    reducedSizes_.resize(numThreads_); 
    for (std::vector<size_t>::iterator it = reducedSizes_.begin();
         it != reducedSizes_.end(); ++it) {
      *it = 0;
    }
#pragma omp parallel default (none) private (none) shared (allPartitions_, reducedSizes_) 
{
    std::vector<size_t> mySizes(numThreads_);
    int myThreadID = 0; //omp_get_thread_num();

    allPartitions_[myThreadID]->fillPartition();
    for (size_t i = 0; i < numThreads_; ++i) {
      if (i == myThreadID) {
        for (size_t j = 0; j < numTasks_; ++j) {
          reducedSizes_[j] += mySizes[j];
        }
      }
      //omp_barrier();
    }
} // end omp parallel
    for (size_t j = 1; j < numTasks_; ++j) {
      reducedSizes_[j] += reducedSizes_[j-1];
    }
  }

  void PartitionGang::fillOutput() {
#pragma omp parallel default (none) private (none) shared (allPartitions_, reducedSizes_) 
{
    size_t task;
    int threadID = 0; //omp_get_thread_num();
    for (size_t i = 0; i < taskFactor_; ++i) {
      task = i * numThreads_ + threadID;
      allPartitions_[threadID]->popTask(resultBegin_ + reducedSizes_[task] - mySizes[task]);
      reducedSizes_[task] -= mySizes[task];
      //omp_barrier();
    }
}  
  }

}
