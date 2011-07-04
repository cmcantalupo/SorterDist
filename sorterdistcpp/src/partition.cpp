#include "partition.hpp"

namespace SorterThreadedHelper {
 
  Partition::Partition(const std::set<double>& pivots,
                       const std::vector<double>::iterator chunkBegin,
                       const std::vector<double>::iterator chunkEnd) :
    chunkBegin_(chunkBegin), chunkEnd_(chunkEnd) {
  
    for (std::set<double>::iterator it = pivots.begin(); it != pivots.end(); ++it) {
      partition_.insert(PartitionWall(*it, false));
    }
    partition_.insert(PartitionWall(*pivots.begin(), true));
  }


  void Partition::fillPartition() {
    std::set<PartitionWall>::iterator bucket;
    for (std::vector<double>::iterator it = chunkBegin_;
         it != chunkEnd_; ++it) {
      bucket = partition_.upper_bound(PartitionWall(*it,false));
      bucket->pushBounded(*it);
    }
  }

}
                                




