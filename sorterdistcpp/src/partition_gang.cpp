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
    taskFactor_(taskFactor) {
    std::vector<double>::iterator chunkBegin;
    std::vector<double>::iterator chunkEnd;
    
    for (std::vector<double>::iterator it = begin;
         it != end && pivots_.size() < numThreads_*taskFactor_ - 1;
         ++it) {
      pivots_.insert(*it);
    }
    if (pivots_.size() < numThreads_*taskFactor_ - 1) {
      throw(SorterThreadedException::TooFewPivots);
    }      

    allPartitions_ = new std::vector<Partition*>(numThreads);
    size_t i = 0;
    for (std::vector<Partition*>::iterator it = allPartitions_->begin();  
         it != allPartitions_->end(); ++it, ++i) {
      chunk(numThreads, i, chunkBegin, chunkEnd);
      *it = new Partition(pivots_.begin(), pivots_.end(), 
                          chunkBegin, chunkEnd);
    }
  }

  PartitionGang::~PartitionGang() {
    std::vector<Partition*>::iterator it;
    for (it = allPartitions_->begin(); 
         it < allPartitions_->end();
         ++it) {
      delete *it;
    }
    delete allPartitions_;
  }

}
