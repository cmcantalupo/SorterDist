#include "splinter.hpp"
#include "assert.h"

using namespace SorterThreadedHelper;

int main(int argc, char **argv) {
  size_t numChunk= 3;
  size_t testSize = numChunk*6;
  std::vector<double> testVec(testSize);
  for (int i = 0; i < testSize; ++i) {
    testVec[i] = i;
  }
  
  Splinter sp(testVec.begin(), testVec.end());
  std::vector<std::vector<double>::iterator> chunks;
  sp.even(numChunk, chunks);
  assert(chunks.size() == numChunk + 1);
  
  for (int i = 0; i < numChunk; ++i) {
    assert(distance(chunks[i],chunks[i+1]) == testSize/numChunk);
  }
}
