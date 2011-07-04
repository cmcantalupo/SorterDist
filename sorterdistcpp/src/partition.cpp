#include "partition.hpp"

namespace SorterThreadedHelper {
 
  Partition::Partition(const std::set<double>::iterator pivotsBegin,
                       const std::set<double>::iterator pivotsEnd,
                       const std::vector<double>::iterator chunkBegin,
                       const std::vector<double>::iterator chunkEnd) :
    chunkBegin_(chunkBegin), chunkEnd_(chunkEnd) {
  
    for (std::set<double>::iterator it = pivotsBegin; it != pivotsEnd; ++it) { 
      partition_.insert(new PartitionWall(*it, false));
    }
    partition_.insert(new PartitionWall(*pivotsBegin, true));
  }
  Partition::~Partition() {
    for (std::set<PartitionWall*>::iterator it = partition_.begin(); 
         it != partition_.end(); ++it) {
      delete *it;
    }
  }


}
                                




