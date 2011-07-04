#include "sorter_threaded.hpp"


SorterThreadedHelper::PartitionGang(std::vector<T>::iterator begin, 
                                    std::vector<T>::iterator end, 
                                    size_t numThreads, size_t taskFactor) {
  resultBegin_ = begin;
  resultEnd_ = end;

  pivots_ = PivotVector(begin, end, numThreads*taskFactor - 1);

  allPartitions_ = new std::vector<Partition<T>*>(numThreads);
  for (int i= 0; i < numThreads; ++i) {
    chunk(numThreads, i, chunkBegin, chunkEnd);
    allPartitions[i] = new Partition<T>(pivots_, chunkBegin, chunkEnd);
  }
}

SorterThreadedHelper::~PartitionGang() {
  std::vector<Partition<T>*>::iterator it;

  for (it = allPartitions.begin(); 
       it < allPartitions.end();
       ++it) {
    delete allPartitions_[i];
  }
  delete allPartitions_;
}

