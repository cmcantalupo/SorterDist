template <class T>
class SorterThread {
  public:
    void sort(std::vector<T>::iterator begin, 
              std::vector<T>::iterator end);
  private:
    const int TASK_FACTOR_ = 8;
    void chunk(std::vector<T>::iterator begin,
	       std::vector<T>::iterator end,
	       size_t numChunk, size_t chunkIndex,
	       std::vector<T>::iterator& chunkBegin,
	       std::vector<T>::iterator& chunkEnd);
};
