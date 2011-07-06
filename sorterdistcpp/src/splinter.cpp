

namespace SorterThreadedHelper {

  Splinter(std::vector<double>::iterator begin, std::vector<double>::iterator end) :
    switchedOff_(false),
    begin_(begin),
    end_(end) {}

  Splinter::addSizes(const std::vector<size_t>& sizes) {
    // throw if switchedOff_ == true
    if (paritionEnds_.size() == 0 || 
        partiionEnds_.size() != sizes.size()) {
      partitionEnds = sizes;
    }
    else {
      std::vector<size_t>::iterator sizeIt = sizes.begin();
      for(std::vector<size_t>::iterator partIt = partitionEnds_.begin();
          partIt != partitionEnds_.end();
          ++parIt, ++sizeIt) {
	*parIt += *sizeIt;
      }
    }
    
    Splinter::getOffsets(const std::vector<size_t>& sizes, 
                         vector<std::vector<double>::iterator> &chunks) {
      // throw if sizes chunks and partitionEnds_ are not all the same size
      if (switchedOff_ == false) {
        for (size_t i = 1; i < partitionEnds_.size(); ++i) {
          partitionEnds_[i] += partitionEnds_[i-1]; 
        }
        switchedOff_ = true;
      }

      size_t n = partitionEnds_.size();
      for (size_t i = 0; i < n; ++i) {
        partitionEnds_[i] -= sizes[i];
        chunks[i] = begin_ + partitionEnds_[i];
      }      
    }
  }
