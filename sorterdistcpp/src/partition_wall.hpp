#ifndef st_partition_wall_hpp
#define st_partition_wall_hpp

#include <stack>

namespace SorterThreadedHelper {

  class PartitionWall {
    public:
      PartitionWall(const double& pivot, const bool &isEnd);
      void stackBounded(const double& boundedEl);
      friend bool operator< (const PartitionWall& l, const PartitionWall& r);
    private:
      bool isEnd_;
      double pivot_;
      std::stack<double> bounded_;
  };

}

#endif
