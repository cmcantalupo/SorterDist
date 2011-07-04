#include "sorter_threaded.hpp"
#include "partition_gang.hpp"
#include "pivot_vector.hpp"
#include "partition.hpp"

namespace SorterThreadedHelper {

  PartitionGang::PartitionGang(std::vector<double>::iterator begin, 
                               std::vector<double>::iterator end, 
			       size_t numThreads, size_t taskFactor) :
    resultBegin_(begin),
    resultEnd_(end),
    numThreads_(numThreads),
    taskFactor_(taskFactor) {
    std::vector<double>::iterator chunkBegin;
    std::vector<double>::iterator chunkEnd;
    
    std::vector<double>::iterator it;
    for (it = begin;
         it != end && pivots_.size() < numThreads_*taskFactor_ - 1;
         ++it) {
      pivots_.insert(*it);
    }
    if (it == end && pivots_.size() < numThreads_*taskFactor_ - 1) {
      throw(SorterThreadedException::TooFewPivots);
    }      

    allPartitions_ = new std::vector<Partition*>(numThreads);
    for (int i = 0; i < numThreads; ++i) {
      chunk(numThreads, i, chunkBegin, chunkEnd);
      allPartitions_[i] = new Partition(pivots_, chunkBegin, chunkEnd);
    }
  }

  PartitionGang::~PartitionGang() {
    std::vector<Partition*>::iterator it;
    for (it = allPartitions_.begin(); 
         it < allPartitions_.end();
         ++it) {
      delete *it;
    }
    delete allPartitions_;
  }

}
