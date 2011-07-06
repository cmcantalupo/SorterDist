// This is a work in progress.  
// C.M.Cantalupo 

#include "sorter_threaded.hpp"
#include "partition_gang.hpp"
#include "sorter_threaded_exception.hpp"


void SorterThreaded::sort(std::vector<double>::iterator begin, 
                          std::vector<double>::iterator end) {
  // To achieve parallelism here we will choose a set of pivots from 
  // the list to be sorted.  Here we will just choose the first elements
  // in the vector.  The number of pivots will determine the number of 
  // tasks to be done: one more task than the number of pivots. 
  //
  // For simplicity here we will choose the number of tasks to be 
  // a factor of the number of threads.  This will be determined 
  // by the class attribute taskFactor_.  
  //
  // We need to break down the main scaling dimension of the problem,
  // the length of the input vector.  The first thing that we want to
  // do with the input is to partition it into intervals bounded by
  // the pivots.  This can be done with the std::set.upper_bound() to
  // partition the input vector.  In the end we want taskFactor_ times
  // the number of threads jobs and we need one fewer pivot than that
  // to do so.  Bundle up the pivots with a stack and put them in a
  // std::set along with a dummy pivot for the end.  We will
  // call this class "PartitionWall." The set provides a upper_bound
  // bound function so we need to overload less than.
  // 

  try {
    SorterThreadedHelper::PartitionGang gang(begin, end, numThreads_, taskFactor_);
    gang.fill();
    gang.pop();
    gang.sort();

  }
  catch (SorterThreadedException& e) {
    if(e.error == SorterThreadedException::TooFewPivots ||
       e.error == SorterThreadedException::NoOpenMP)
      std::sort(begin, end);
    else
      throw(e);
  }
}

SorterThreaded::SorterThreaded(size_t taskFactor, size_t numThreads) :
  taskFactor_(taskFactor), 
  numThreads_(numThreads) {}


                                


