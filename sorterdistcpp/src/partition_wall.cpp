#include "sorter_threaded.hpp"
#include "partition_wall.hpp"

namespace SorterThreadedHelper {

  PartitionWall::PartitionWall(const double& pivot, const bool &isEnd) :
    pivot_(pivot), isEnd_(isEnd) {}

  bool operator< (const PartitionWall& l, const PartitionWall& r) {
    if (l.isEnd_) return false;
    else return l.pivot_ < r.pivot_;     
  }

  void pushBounded(const double& boundedEl) const {
    bounded_.push(boundedEl);
  }

  double popBounded() const {
    return bounded_.pop();
  }

}
