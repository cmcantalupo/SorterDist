#include "sorter_threaded.hpp"
#include <algorithm>
#include <assert.h>
#ifdef PROFILE_STT
#include "M3_profile.h"
#endif 

int main(int argc, char **argv) {
#ifdef PROFILE_STT
  M3_ProfileInit("sorter_threaded_test");
#endif

  size_t testSize = 1000000;
  std::vector<double> orderedVector(testSize);
  SorterThreaded st;
  
  for (size_t i = 0; i < testSize; i++) {
    orderedVector[i] = static_cast<double>(i);
  }
  std::vector<double> testVector(orderedVector);

  random_shuffle(testVector.begin(), testVector.end());

#ifdef PROFILE_STT
  M3_ProfileStart(0, "sort 1 million");
#endif 

  st.sort(testVector.begin(), testVector.end());

#ifdef PROFILE_STT
  M3_ProfileStop(0);
#endif

  assert(testVector == orderedVector);

#ifdef PROFILE_STT
  M3_ProfileFinalize();
#endif

    
}
