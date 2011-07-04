#ifndef st_partition_wall_hpp
#define st_partition_wall_hpp

#include "sorter_threaded.hpp"

namespace SorterThreadedHelper {

  template <class T>
  class PartitionWall {
    public:
      PartitionWall(const T& pivot, const bool &isEnd);
      bool operator < (const T& other) const {
        if (isEnd) return false;
        else return pivot_ < other;
      }
    private:
      bool isEnd_;
      T pivot_;
      std::stack<T> bounded_
  };

}

#endif
