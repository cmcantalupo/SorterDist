#ifndef sorter_threaded_exception_hpp
#define sorter_threaded_exception_hpp

struct SorterThreadedException : std::exception {
  enum Error {TooFewPivots = 1, 
              NoOpenMP = 2, 
              SplinterOrder = 3,
              SplinterSize = 4};
  inline SorterThreadedException(Error code) : error(code) {} 
  const Error error;
};

#endif
