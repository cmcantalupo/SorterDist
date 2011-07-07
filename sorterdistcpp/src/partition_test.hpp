#ifndef partition_test_hpp
#define partition_test_hpp
#include <vector>
#include <set>

namespace SorterThreadedHelper {

  class PartitionTest {
    public:
      PartitionTest(const std::vector<double>& test, const std::set<double>& pivots);
      virtual int run();
    protected:
      std::vector<double> testVec_;
      std::set<double> testPivots_;
  };

  class Permute18 {
    public:
      Permute18();
      std::vector<double> getVec();
      std::set<double> getPiv();
    private:
      std::vector<double> vec_;
      std::set<double> piv_;
  };

  class Permute18Test : public Permute18 , public PartitionTest {
    public:
      Permute18Test();
      int run();
  };
}

#endif
