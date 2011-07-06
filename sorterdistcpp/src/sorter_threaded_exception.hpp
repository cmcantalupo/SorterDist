#ifndef sorter_threaded_exception_hpp
#define sorter_threaded_exception_hpp

struct SorterThreadedException : std::exception {
  enum Error {TooFewPivots = 1, 
              NoOpenMP = 2,
              PopEmptyPartition = 3, 
              TaskTooShort = 4, 
              TaskTooLong = 5, 
              StackSizeVectorTooShort = 6};
  inline SorterThreadedException(Error code) : error(code) {} 
  const Error error;
};

#endif
