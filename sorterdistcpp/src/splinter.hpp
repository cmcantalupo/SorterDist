#ifndef splinter_hpp
#define splinter_hpp
#include <vector>

namespace SorterThreadedHelper {
  class Splinter {
    public:
      Splinter(std::vector<double>::iterator begin, 
               std::vector<double>::iterator end);
      void even(size_t num, std::vector<std::vector<double>::iterator>& chunks);
      void addSizes(const std::vector<size_t>& sizes);
      void getOffsets(const std::vector<size_t>& sizes, 
                      std::vector<std::vector<double>::iterator> &chunks);
    private:
      bool switchedOff_;
      std::vector<double>::iterator begin_;
      std::vector<double>::iterator end_;
      std::vector<size_t> partitionEnds_;
  };

}

#endif
