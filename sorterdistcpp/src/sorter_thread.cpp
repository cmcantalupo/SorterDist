// This is a work in progress.  
// C.M.Cantalupo 


template <class T>
class SortThreadBundle {
  public:
    T value;
    size_t index;
    bool operator < ( const T& other) {
      return value < other.value;
    }
};

void SorterThread::sort(std::vector<T>::iterator begin, 
                        std::vector<T>::iterator end) {
  int numThreads = omp_get_max_num_threads();
  std::vector<std::stack<T>> sharedPartition(numThreads);

#pragma omp parallel default (none) private () firstprivate() shared (sharedPartition) {
  size_t threadID = omp_get_thread_num();
  size_t numTasks = numThreads*TASK_FACTOR_;
  size_t numPivots = numTasks - 1;
  size_t vecLen = std::distance(begin, end);

  // Bundle up the pivots with an index
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
  std::vector<T> myWork(sharedPartition[threadID]);
  sort(myWork);

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



