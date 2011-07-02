// This is a work in progress.  
// C.M.Cantalupo 

// The pivot's that will be put into a set.  
// These need to cary an index of the partition bin and a value 
// for comparison.  
namespace SorterDist {
  template <class T>
  class Pivot {
    public:
      T value;
      size_t index;
      bool operator < ( const T& other) const {
        return value < other.value;
    }
  };

  // We need to break the input vector into nearly equal size chunks
  // for sorting.  Since we need to sort the result, it needs to be in
  // a random access iterator.  We also know the size of the chunks a
  // priori since we are evenly dividing the input.  These vectors
  // need to be OpenMP private variables so that each thread can sort
  // simultaniously.  For this reason we have to make a copy of the
  // input.
  template <class T>
  class WorkUnit {
    public:
      std::vector<T> chunk; // Thread private vector to be sorted
      std::vector<T>::iterator resultBegin; // Once it is sorted these
      std::vector<T>::iterator resultEnd;   // tell where to insert back.  
  };

    

  
}

void SorterThread::sort(std::vector<T>::iterator begin, 
                        std::vector<T>::iterator end) {
  // To achieve parallelism here we will choose a set of pivots from 
  // the list to be sorterd.  Here we will just choose the first elements
  // in the vector.  The number of pivots will determine the number of 
  // tasks to be done: one more task than the number of pivots. 
  //
  // For simplicity here we will choose the number of tasks to be 
  // a factor of the number of threads.  This will be determined 
  // by the class attribute taskFactor_.  
  //
  // We need to break down the main scaling dimesion of the problem, 
  // the length of the input vector.  The first thing that we want to 
  // do with the input is to partition it into intervals bounded by 
  // the pivots.  This can be done with the std::set.upper_bound() 
  // values to
  // partition the input vector.  In the end we want taskFactor_ times
  // the number of threads jobs and we need one fewer pivot than that
  // to do so.  Bundle up the pivots with an index and put them in a
  // std::set.  We will call this class "SorterPivot." The set
  // provides a upper_bound bound function so we need to overload less
  // than.
  // 

  // Sorry for the procedural mess below.  Need to rethink algorithm 
  // in terms of objects.  

omp_get_max_num_threads
  int numThreads = omp_get_max_num_threads();
#pragma omp parallel default (none) private () firstprivate() shared (sharedPartition) {
  size_t threadID = omp_get_thread_num();
  size_t numTasks = numThreads*TASK_FACTOR_;
  size_t numPivots = numTasks - 1;
  size_t vecLen = std::distance(begin, end);



  std::vector<T>::iterator pivotsEnd = begin + numPivots;
  std::vector<SorterThread> bundled(numPivots);
  for (itIn = begin, i = 0;
       itIn < pivotsEnd; ++itIn, ++i) {
    bundled[i].value = *itIn;
  }
  sort(bundled);
  for (i = 0; i < bundled.size(); i++) {
    bundled[i].index = i;
  }

  // Put the bundled pivots in a set
  std::set<T> pivots(bundled.begin(), bundled.end());

  // Break up the input vector into number of threads chunks
  std::vector<T>::iterator chunkBegin;
  std::vector<T>::iterator chunkEnd;
  
  SorterThread::chunk(pastPivots, end, numThreads, threadID, chunkBegin, chunkEnd);  
  std::vector<std::stack<T>> partition(numTasks);

  // Partition the input into private stacks
  for (it = chunkBegin; it < chunkEnd; ++it) {
    partition[pivots.lower_bound(*it).index].push(*it);
  }

  std::vector<std::vector<T>> sharedPartition(numThreads);
  
  // Combine the private stacks into shared memory
  for (i = 0; i < TASK_FACTOR_; i++) {
    for (j = 0; j < numThreads; j++) {
      outBin = i * TASK_FACTOR_ + (j + threadID) % numThreads;
      while (!partition[outBin].empty()) {
        sharedPartition[outBin].push(partition[outBin].pop());
      }
      omp_barrier();
    }
  }
  
  // Farm out the shared stacks to local threads 
  myWork
  for (i = 0; i < numTasks; i++) {  
    std::vector<T> myWork(sharedPartition[i]);
    sort(myWork);
  }
    

  // Recombine the sorted chunks

  if (threadID == 0) {
    for (pivotIt = pivots.begin(), resultIt = begin; 
         pivotIt < pivots.end(); ++pivotIt, ++resultIt) {
      *resultIt = *pivotIt;

  for (i = 0; i < numThreads; i++) {
    if (i == threadID) {
      for (workIt = myWork.begin(); workIt < myWork.end(); ++workIt, ++resultIt)
	*resultIt = *workIt;
    }
  }  
}
}

void SorterThread::chunk(std::vector<T>::iterator begin,
			 std::vector<T>::iterator end,
			 size_t numChunk, size_t chunkIndex,
			 std::vector<T>::iterator chunkBegin,
			 std::vector<T>::iterator chunkEnd)
{
  size_t chunkSize = (vecLen - numPivots) / numThreads;
  int slop = (vecLen - numThreads - 1) % numThreads;
  if ( threadID < slop ) {
    myChunkBegin = pastPivots + threadID * (chunkSize + 1);
  }
  else {
    myChunkBegin = pastPivots + slop * (chunkSize + 1);
    myChunkBegin += (threadID - slop) * (chunkSize);
  }
  if ( threadID < slop ) {
    myChunkEnd = 
  }
  else {
    myChunkBegin = pastPivots + slop * (chunkSize + 1);
    myChunkBegin += (threadID - slop) * (chunkSize);
  }



  int slop = vecLen % numThreads;
  std::vector<std::vector<T>::iterator>::chunks(numThreads);
  for ( std::vector<T>::iterator inputIt = pastPivots, i = 0
	  i < numThreads; inputIt += chunkSize, ++i) {
    if (i == slop) {
      --chunkSize
    }
    chunks[i] = inputIt;
  }
  
  
    
    
  }

  
  // 

  }
}



