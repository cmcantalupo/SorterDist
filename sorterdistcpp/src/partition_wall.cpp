#include "sorter_threaded.hpp"
#include "partition_wall.hpp"

namespace SorterThreadedHelper {
PartitionWall::PartitionWall(const double& pivot, const bool &isEnd) :
  pivot_(pivot), isEnd_(isEnd) {}
}
