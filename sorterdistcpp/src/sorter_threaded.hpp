template <class T>
class SorterThreaded {
  public:
    SorterThreaded(size_t taskFactor=8, size_t numThreads=-1);
    void sort(std::vector<T>::iterator begin, 
              std::vector<T>::iterator end);
    void setTaskFactor(size_t taskFactor);
    void setNumThreads(size_t numThreads);
  private:
    size_t taskFactor_;
    // If numThreads_ == -1 then omp_max_num_threads will be used
    size_t numThreads_;
};

namespace SorterThreadedHelper {

  // We need to break the input vector into nearly equal size chunks
  // for partitioning.  One chunk for each thread. 
  //
  // We can builid up a Partition from an array of non-repeating 
  // values (pivots) from the input vector.  
  //
  // Each thread will have and make its own Partition.  These will be
  // OpenMP private.  Each partition has a stack for each thread and
  // each task.  This implies that the total number of stacks over all
  // threads is numThreads^3 * taskFactor_.
  //
  // The threads will be managed by the PartitionGang.  This class
  // will hold all of the Partitions and will be the class to 
  // spawn threads.  
  //

  template <class T>
  class PartitionWall {
    public:
      PartitionWall(const T& pivot, const bool &isEnd);
      bool operator < (const T& other) const {
        if (isEnd) return false;
        else return pivot_ < other;
      }
    private:
      bool isEnd;
      T pivot_;
      std::stack<T> bounded_
  };

  template <class T>
  class Partition {
    private:
      std::vector<T>::iterator chunkBegin_;
      std::vector<T>::iterator chunkEnd_;
      std::set<PartitionWall<T>> *partition_;
    public:
    Partition(PivotVector pivots, 
              std::vector<T>::iterator chunkBegin, 
              std::vector<T>::iterator chunkEnd); 
    void fillPartition(); //single threaded
  };

  template <class T>
  class PivotVector {
    private:
      std::vector<T>* pivots_;
    public:
      PivotVector(std::vector<T>::iterator begin, std::vector<T>::iterator end, size_t numPivots);
      ~PivotVector();
      void iterators( std::vector<T>::iterator &begin, std::vector<T>::iterator &end);
      size_t size();
  }

  template <class T>
  class PartitionGang {
    private:
      PivotVector pivots_;
      std::vector<T>::iterator resultBegin_;
      std::vector<T>::iterator resultEnd_;
      std::vector<Partition<T>*>* allPartitions; // we need a partition for each thread.
      void chunk(size_t numChunk, size_t chunkIndex,
	         std::vector<T>::iterator& chunkBegin,
	         std::vector<T>::iterator& chunkEnd);
    public:
      PartitionGang(std::vector<T>::iterator begin, std::vector<T>::iterator end, 
                    size_t numThread, size_t threadFactor);
      ~PartitionGang();

      // fills the stacks of each thread's partition 
      void fillPartitions(); //spawns threads
      // Refills the input vector with the values partitioned 
      // between the pivots by popping all the stacks.  
      void fillOutput(); // spawns threads 
      // sort the output once it has been filled with the partitions.  
      void sortOutput(); // spawns threads
  };  
}

