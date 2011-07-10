#ifdef _OPENMP
#include "sorter_threaded.hpp"
#include <algorithm>
#include <assert.h>
#include <string>
#include <sstream>
#include <iostream>
#include "M3_profile.h"
#include "omp.h"

int main(int argc, char **argv) {
  M3_ProfileInit("sorter_threaded");

  size_t testSize = 1000000;
  SorterThreaded st;
  
  if (argc > 1) {
    testSize = atoi(argv[1]);
  }
  if (argc > 2) {
    st.setTaskFactor(atoi(argv[2]));
  }
  std::vector<double> unsortedVector(testSize);

  for (size_t i = 0; i < testSize; i++) {
    unsortedVector[i] = static_cast<double>(i);
  }
  std::random_shuffle(unsortedVector.begin(), unsortedVector.end());

  std::vector<double> testVector(unsortedVector);

  int numThreads = omp_get_max_threads();
  std::stringstream profileStream;

  for (int i = 1; i <= numThreads; i++) {
    st.setMaxThreads(i);
    profileStream.str("");
    profileStream << "num threads = " << i;
    M3_ProfileStart(i, profileStream.str().c_str());
    st.sort(testVector.begin(), testVector.end());
    M3_ProfileStop(i);
    testVector = unsortedVector;
  }

  M3_ProfileFinalize();    
}
#endif
