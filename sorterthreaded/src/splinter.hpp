#ifndef splinter_hpp
#define splinter_hpp
#include <vector>
#include "sorter_threaded_exception.hpp"

namespace SorterThreadedHelper {
  template <class type>
   class Splinter {
     public:
       Splinter(typename std::vector<type>::iterator begin, 
		typename std::vector<type>::iterator end, int numTasks);
       void even(size_t num, typename std::vector<typename std::vector<type>::iterator>& chunks);
       void addSizes(const std::vector<size_t>& sizes);
       void getOffsets(const std::vector<size_t>& sizes, 
		       std::vector<typename std::vector<type>::iterator> &chunks);
     private:
       bool switchedOff_;
       typename std::vector<type>::iterator begin_;
       typename std::vector<type>::iterator end_;
       std::vector<size_t> partitionEnds_;
   };

  template <class type>
  Splinter<type>::Splinter(typename std::vector<type>::iterator begin, 
                           typename std::vector<type>::iterator end, int numTasks) :
    switchedOff_(false),
    begin_(begin),
    end_(end),
    partitionEnds_(numTasks) {
    for (std::vector<size_t>::iterator it = partitionEnds_.begin();
         it != partitionEnds_.end(); ++it) {
      *it = 0;
    }
  }

  template <class type>
  void Splinter<type>::addSizes(const std::vector<size_t>& sizes) {
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
  
  template <class type>
  void Splinter<type>::getOffsets(const std::vector<size_t>& sizes, 
                                  std::vector<typename std::vector<type>::iterator>& chunks) {
    if (sizes.size() != partitionEnds_.size()) {
      throw(SorterThreadedException::SplinterSize);
    }

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
  
  template <class type>
  void Splinter<type>::even(size_t num, std::vector<typename std::vector<type>::iterator>& chunks) {
    chunks.resize(num + 1);
    size_t chunkSize = distance(begin_, end_) / num + 1;
    size_t slop = distance(begin_, end_) % num;

    typename std::vector<type>::iterator it = begin_;
    for (size_t i = 0; i <= num; ++i) {
      if (i == slop) {
        --chunkSize;
      }
      chunks[i] = it;
      it += chunkSize;
    }
  }
}

#endif
