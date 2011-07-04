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
      // This doesn't work, you can't manipulate the element of a set
      // Need to go back to original design where the stacks are in a
      // vector and the sets hold an index.
      //  
      // Alternatively we can insert and delete.  We would have to
      // store a pointer to the stack in the element inserted and
      // deleted rather than the stack itself.  This seems like a
      // better approach design wise, and the stacks for the
      // partitioning belong in the application heap anyway.
      // Duh.  We need a map.  
      bucket->pushBounded(*it);
    }
  }

}
                                




