#include "partition_wall.hpp"

namespace SorterThreadedHelper {

  PartitionWall::PartitionWall(const double& pivot, const bool &isEnd) :
    pivot_(pivot), isEnd_(isEnd) {}

  PartitionWall::PartitionWall() :
    pivot_(), isEnd_(true) {}

  bool operator< (const PartitionWall& l, const PartitionWall& r) {
    if (l.isEnd_) return false;
    if (r.isEnd_) return true;
    else return l.pivot_ < r.pivot_;     
  }

  void PartitionWall::set(const double &pivot, const bool &isEnd) {
    pivot_ = pivot;
    isEnd_ = isEnd;
  }

}
