#include "sorter_threaded.hpp"
#include "partition_wall.hpp"

namespace SorterThreadedHelper {

  PartitionWall::PartitionWall(const double& pivot, const bool &isEnd) :
    pivot_(pivot), isEnd_(isEnd) {}

  bool operator< (const PartitionWall& l, const PartitionWall& r) {
    if (l.isEnd_) return false;
    else return l.pivot_ < r.pivot_;     
  }

  void PartitionWall::pushBounded(const double& boundedEl) {
    bounded_.push(boundedEl);
  }

  double PartitionWall::popBounded() {
    double top = bounded_.top();
    bounded_.pop();
    return top;
  }

}
