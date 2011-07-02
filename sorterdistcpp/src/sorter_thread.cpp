// This is a work in progress.  
// C.M.Cantalupo 

template <class T>
void SorterThread::sort(std::vector<T>::iterator begin, 
                        std::vector<T>::iterator end) {
  int numThreads = omp_get_max_num_threads();
  std::vector<std::stack<T>> sharedPartition(numThreads);

#pragma omp parallel default (none) private () firstprivate() shared (sharedStack) {
  size_t threadID = omp_get_thread_num();
  size_t numTasks = numThreads*_TASK_FACTOR;
  size_t numPivots = numTasks - 1;
  size_t vecLen = std::distance(begin, end);
  struct bundle {T value, size_t index};

  // Pick number of tasks - 1 pivots and put them in a set
  std::vector<T>::iterator pastPivots = begin + numPivots;
  std::vector<T>
  std::set<T> pivots(begin, pastPivots);
  

  // Break up the input vector into number of threads chunks
  std::vector<T>::iterator chunkBegin;
  std::vector<T>::iterator chunkEnd;
  
  SorterThread::chunk(pastPivots, end, numThreads, threadID, chunkBegin, chunkEnd);  
  std::vector<std::stack<T>> partition(numTasks);

  for (it = chunkBegin; it < chunkEnd; ++it) {
    partition[pivots.lower_bound(*it)[1]].push(*it);
  }

  for (i = 0; i < numThreads; i++) {
  {
    outBin = (i + threadID) % numThreads;
    while (!partition[outBin].empty()) {
      sharedPartition[outBin].push(partition[outBin].pop());
    }
    omp_barrier();
  }
  
  std::vector<T> myWork(sharedPartition[threadID]);
  sort(myWork);

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
			 std::vector<T>::iterator chunkEegin)
{
  size_t chunkSize = (vecLen - numPivots) / numThreads;
  int slop = (vecLen - numThreads - 1) % numThreads;
  if ( threadID < slop ) {
    myChunkBegin q= pastPivots + threadID * (chunkSize + 1);
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



