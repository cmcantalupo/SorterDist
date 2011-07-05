#include "partition.hpp"
#include "partition_wall.hpp"

namespace SorterThreadedHelper {
 
  Partition::Partition(const std::set<double>& pivots,
                       const std::vector<double>::iterator chunkBegin,
                       const std::vector<double>::iterator chunkEnd) :
    chunkBegin_(chunkBegin), chunkEnd_(chunkEnd) {
  
    for (std::set<double>::iterator it = pivots.begin(); it != pivots.end(); ++it) {
      partition_.insert(std::pair<PartitionWall,std::stack<double>*>(PartitionWall(*it,false), new stack<double>));
    }
    partition_.insert(std::pair<PartitionWall,std::stack<double>*>(PartitionWall(*pivots.begin(), true), new stack<double>));
  }
  Partition::~Partition() {
    for (std::map<PartitionWall,std::stack<double>*>:iterator it = partition_.begin(); it != partition_.end(); ++it) {
      delete it.second();
    }
  }
     

  void Partition::fillPartition() {
    std::set<double>::iterator ub;
    for (std::vector<double>::iterator it = chunkBegin_;
         it != chunkEnd_; ++it) {
      ub = partition_.upper_bound(PartitionWall(*it, false));
      if (ub == partition_.end()) --ub;
      ub->second()->push(*it);
    }
  }

}
                                




