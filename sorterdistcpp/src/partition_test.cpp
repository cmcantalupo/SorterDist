#include "partition.hpp"
#include "sorter_threaded_exception.hpp"
#include <iostream>
#include <assert.h>

using namespace SorterThreadedHelper;

int main(int argc, char **argv) {
  const double testArr[18] = {7, 15, 13, 17, 2, 10, 12, 3, 14, 9, 0, 8, 1, 11, 16, 6, 5, 4};
  std::vector<double> test(18);
  for (int i = 0; i < 18; i++) {
    test[i] = testArr[i];
  }
  std::set<double> pivots;
  pivots.insert(6);
  pivots.insert(12);
  

  Partition part(pivots);
  part.fill(test.begin(), test.end());

  size_t numTasks = part.numTasks();
  std::vector<size_t> taskSizes(numTasks);
  part.taskSizes(taskSizes);

  std::vector<double> task(6);

  for (int i = 0; i < numTasks; ++i) {
    assert(i == part.curTask());
    assert(taskSizes[i] == 6);
    part.popTask(task.begin(), task.end());
    for (int j = 0; j < taskSizes[i]; j++ ) {
      if (i == 0) assert(task[j] < 6);
      if (i == 1) assert(6 <= task[j] && task[j] < 12);
      if (i == 2) assert(12 <= task[j]);
    }
  }

}
