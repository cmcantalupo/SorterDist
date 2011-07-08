#include "splinter.hpp"
#include "sorter_threaded_exception.hpp"

namespace SorterThreadedHelper {

  Splinter::Splinter(std::vector<double>::iterator begin, std::vector<double>::iterator end, int numTasks) :
    switchedOff_(false),
    begin_(begin),
    end_(end),
    partitionEnds_(numTasks) {
    for (std::vector<size_t>::iterator it = partitionEnds_.begin();
         it != partitionEnds_.end(); ++it) {
      *it = 0;
    }
  }

  void Splinter::addSizes(const std::vector<size_t>& sizes) {
    if (switchedOff_ == true) {
      throw(SorterThreadedException::SplinterOrder);
    }
    if (sizes.size() != partitionEnds_.size()) {
      throw(SorterThreadedException::SplinterSize);
    }

    std::vector<size_t>::const_iterator sizeIt = sizes.begin();
    for(std::vector<size_t>::iterator partIt = partitionEnds_.begin();
	partIt != partitionEnds_.end(); ++partIt, ++sizeIt) {
      *partIt += *sizeIt;
    }
  }
    
  void Splinter::getOffsets(const std::vector<size_t>& sizes, 
                            std::vector<std::vector<double>::iterator>& chunks) {
    // throw if sizes chunks and partitionEnds_ are not all the same size
    if (switchedOff_ == false) {
      for (size_t i = 1; i < partitionEnds_.size(); ++i) {
	partitionEnds_[i] += partitionEnds_[i-1];
      }
      switchedOff_ = true;
    }

    size_t n = partitionEnds_.size();
    chunks.resize(n);
    for (size_t i = 0; i < n; ++i) {
      partitionEnds_[i] -= sizes[i];
      chunks[i] = begin_ + partitionEnds_[i];
    }
  }
  
  void Splinter::even(size_t num, std::vector<std::vector<double>::iterator>& chunks) {
    chunks.resize(num + 1);
    size_t chunkSize = distance(begin_, end_) / num + 1;
    size_t slop = distance(begin_, end_) % num;

    std::vector<double>::iterator it = begin_;
    for (size_t i = 0; i <= num; ++i) {
      if (i == slop) {
        --chunkSize;
      }
      chunks[i] = it;
      it += chunkSize;
    }
  }
}
