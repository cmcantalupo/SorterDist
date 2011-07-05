#ifndef st_partition_hpp
#define st_partition_hpp

#include <set>
#include <vector>

namespace SorterThreadedHelper {

  class Partition {
    public:
      Partition(const std::set<double>& pivots,
                const std::vector<double>::iterator chunkBegin, 
                const std::vector<double>::iterator chunkEnd); 
      void fillPartition(); //single threaded

    private:
      const std::vector<double>::iterator chunkBegin_;
      const std::vector<double>::iterator chunkEnd_;
      std::set<double> pivots_;
      std::map<std::set<double>::iterator,std::stack<double>*> partition_;
  };



}

#endif
  
