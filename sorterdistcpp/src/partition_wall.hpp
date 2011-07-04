#ifndef st_partition_wall_hpp
#define st_partition_wall_hpp

#include <stack>

namespace SorterThreadedHelper {

  class PartitionWall {
    public:
      PartitionWall(const double& pivot, const bool &isEnd) :
        pivot_(pivot), isEnd_(isEnd){};
      bool operator < (const double& other) const {
        if (isEnd_) return false;
        else return pivot_ < other;
      }
    private:
      bool isEnd_;
      double pivot_;
      std::stack<double> bounded_;
  };

}

#endif
