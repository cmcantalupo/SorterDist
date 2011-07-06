

namespace SorterThreadedHelper {
  
  class Splinter {
    public:
      Splinter(std::vector<double>::iterator begin, std::vector<double>::iterator end);
      void even(size_t num, vector<std::vector<double>::iterator> &chunks);
      void addSizes(const vector<size_t>& sizes);
      void getOffsets(vector<std::vector<double>::iterator> &chunks) 
      
    private:
      bool switchedOff;
      std::vector<double>::iterator begin_;
      std::vector<double>::iterator end_;
      std::vector<size_t>::partitionEnds_;
  }

}
