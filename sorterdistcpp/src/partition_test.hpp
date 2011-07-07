#ifndef partition_test_hpp
#define partition_test_hpp
#include <vector>
#include <set>

namespace SorterThreadedHelper {

  class PartitionTest {
    public:
      PartitionTest();     
      virtual int run() = 0;
    protected:
      std::vector<double> testVec_;
      std::set<double> testPivots_;
  };

  class Permute18Test : public PartitionTest{
    public:
      Permute18Test();
      int run();
  };
}

#endif
