#include "quick_sort.hpp"

void quick_sort(std::vector<double>::iterator begin, 
                std::vector<double>::iterator end) {
  // Recursive implementation of the quick sort algorithm
  std::vector<double>::iterator it;
  double beginValue;
  long int smallCount = 0;
  long int bigCount = 0;
  long int totalCount = std::distance(begin, end);
  long int smallIndex = 0;
  long int bigIndex = 0;

  // If the vector has less than two elements return
  if ( totalCount < 2 ){
    return;
  }

  // Iterate through the list and count the number of elements 
  // smaller than the first element
  beginValue = *begin;
  it = begin;
  ++it;
  for (; it < end; ++it){
    if (*it < beginValue) {
      ++smallCount;
    }
  }
  bigCount = totalCount - smallCount - 1;
  it = begin;
  ++it;
  
  // Create two new vectors to hold the values smaller and larger 
  // than the first element
  std::vector<double> smallVec(smallCount);
  std::vector<double> bigVec(bigCount);


  // Fill the new vectors
  it = begin;
  ++it;
  for (; it < end; ++it) {
    if (*it < beginValue) {
      smallVec[smallIndex] = *it;
      ++smallIndex;
    }
    else {
      bigVec[bigIndex] = *it;
      ++bigIndex;
    }
  }
  
  // If the small vector has more than one element recursively call 
  // quickSort on it
  if (smallCount > 1) {
    quick_sort(smallVec.begin(), smallVec.end());
  }
  // If the large vector has more than one element recursively call 
  // quickSort on it
  if (bigCount > 1) {
    quick_sort(bigVec.begin(), bigVec.end());
  }
  
  // Now that the big and small list are sorted fill the input with 
  // the results
  it = begin;
  for (smallIndex = 0; smallIndex < smallCount; ++smallIndex, ++it) {
    *it = smallVec[smallIndex];
  }
  *it = beginValue;
  ++it;
  for (bigIndex = 0; bigIndex < bigCount; ++bigIndex, ++it) {
    *it = bigVec[bigIndex];
  }
}
