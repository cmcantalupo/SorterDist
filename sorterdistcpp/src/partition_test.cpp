#include <iostream>
#include <assert.h>
#include "partition.hpp"
#include "partition_test.hpp"

using namespace SorterThreadedHelper;

PartitionTest::PartitionTest(const std::vector<double>& test, const std::set<double>& pivots) : 
  testVec_(test),
  testPivots_(pivots) {}

Permute18::Permute18() {
  const int testArr[] = {7, 15, 13, 17, 2, 10, 12, 3, 14, 
                           9, 0, 8, 1, 11, 16, 6, 5, 4};
  const int pivotsArr[] = {6, 12};
  size_t arrLen = sizeof(testArr) / sizeof(testArr[0]);
  vec_.resize(arrLen);
  for (size_t i = 0; i < arrLen; ++i) {
    vec_[i] = testArr[i];
  }

  size_t pivLen = sizeof(pivotsArr) / sizeof(pivotsArr[0]);
  for (size_t i = 0; i < pivLen; ++i) {
    piv_.insert(pivotsArr[i]);
  }
  assert(piv_.size() == pivLen);
}

std::vector<double> Permute18::getVec() {
  return vec_;
}
std::set<double> Permute18::getPiv() {
  return piv_;
}


Permute18Test::Permute18Test() : Permute18(), PartitionTest(getVec(), getPiv()) {}

int Permute18Test::run() {
  Partition part(testPivots_);
  part.fill(testVec_.begin(), testVec_.end());
  size_t numTasks = part.numTasks();
  if(numTasks != 3) {
    std::cerr << "FAILED:  PartitionTest numTasks = " << numTasks << "\n";
    return 1;
  }
  std::vector<size_t> taskSizes(numTasks);
  part.taskSizes(taskSizes);

  std::vector<double> task(6);

  for (int i = 0; i < numTasks; ++i) {
    assert(i == part.curTask());
    assert(taskSizes[i] == 6);
    part.popTask(task.begin(), task.end());
    for (int j = 0; j < taskSizes[i]; j++ ) {
      if (i == 0 && !(task[j] < 6)) {
	std::cerr << "FAILED: Permute18Test first partition fail\n";
        return 2;
      }
      if (i == 1 && !(6 <= task[j] && task[j] < 12)) {
	std::cerr << "FAILED: Permute18Test second partition fail\n";
        return 3;
      }
      if (i == 2 && !(12 <= task[j])) {
	std::cerr << "FAILED: Permute18Test third parition fail\n";
	return 4;
      }
    }
  }
}

int main(int argc, char **argv) {
  Permute18Test p18;
  p18.run();
}
