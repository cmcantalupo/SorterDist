#include "partition.hpp"
#include "partition_wall.hpp"

namespace SorterThreadedHelper {
 
  Partition::Partition(const std::set<double>& pivots,
                       const std::vector<double>::iterator chunkBegin,
                       const std::vector<double>::iterator chunkEnd) :
    chunkBegin_(chunkBegin), chunkEnd_(chunkEnd) {
  
    std::pair<PartitionWall,std::stack<double>*> pp;
    for (std::set<double>::iterator it = pivots.begin(); it != pivots.end(); ++it) {
      pp.first = PartitionWall::PartitionWall(*it,false);
      pp.second = new std::stack<double>;
      partition_.insert(pp);
    }
    pp.first = PartitionWall::PartitionWall(*pivots.begin(), true);
    pp.second = new std::stack<double>;
    partition_.insert(pp);

    taskIt_ = partition_.begin();
  }
  Partition::~Partition() {
    for (std::map<PartitionWall,std::stack<double>*>::iterator it = partition_.begin(); it != partition_.end(); ++it) {
      delete it->second;
    }
  }
     

  void Partition::fillPartition() {
    std::map<PartitionWall,std::stack<double>*>::iterator ub;
    for (std::vector<double>::iterator it = chunkBegin_;
         it != chunkEnd_; ++it) {
      ub = partition_.upper_bound(PartitionWall::PartitionWall(*it,false));
      if (ub == partition_.end()) --ub;
      ub->second->push(*it);
    }
  }

  void Partition::popTask(std::vector<double>::iterator resultBegin) {
    while (!taskIt_->second->empty()) {
      *resultBegin = taskIt_->second->top();
      taskIt_->second->pop();
      ++resultBegin;
    }
    ++taskIt_;
  }

  void Partition::stackSizes(std::vector<size_t>::iterator begin, 
                             std::vector<size_t>::iterator end) {
  }

}
                                




