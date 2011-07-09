#include "sorter_threaded.hpp"
#include <assert.h>


int main(int argc, char **argv) {
  size_t testSize = 1000000;
  std::vector<double> orderedVector(testSize);
  SorterThreaded st;
  
  for (size_t i = 0; i < testSize; i++) {
    orderedVector[i] = static_cast<double>(i);
  }
  std::vector<double> testVector(orderedVector);

  random_shuffle(testVector.begin(), testVector.end());
  
  st.sort(testVector.begin(), testVector.end());

  assert(testVector == orderedVector);
    
}
