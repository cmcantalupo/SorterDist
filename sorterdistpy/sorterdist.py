class SorterArray(object):
    """
    Base class for storing data to be sorted.  
    """
    def __init__(self, data):
        pass
    def set_data(self, data):
        pass
    def append_data(self, data):
        pass
    def get_data(self):
        pass
    def get_range(self, beginIdx, endIdx):
        pass
    def del_data(self):
        pass
    def del_range(self, beginIndex, endIndex):
        pass
    def del_indexed(self, index)
        pass


class Sorter(SorterArray): 
    """ 
    Class that defines the basic functionality of SorterDist for
    serial sorting.
    """
    def __init__(self, data=None, comp=None):
        pass
    def set_comp(self, comp):
        pass
    def get_sorted(self):
        pass
    def get_sequence(self, beginEl, endEl):
        pass
    def get_sequence_fixed(self, beginEl, numEl):
        pass
    def get_sequence_multi(self, rangeList):
        pass
    def return_permutation(self, doIt=True):
        pass
    def store_permuation(self, doIt=True):
        pass
    def sort_in_place(self, doIt=True):
        pass

class Compare(object):
    """
    Abstract base class for determining how to compare two objects.
    This object will facilitate the use of native comparisons in C++
    for Python objects.  The implementation of this class depends on
    how BOOST integrates C++ and Python

    NumPy's array sorter gives a working model for complex objects.
    """
    pass

class SorterThread(Sorter):
    """
    Shared memory sorting for Python users through binding to C++
    library.  
    """
    def __init__(self, data=None, comp=None, numThr=1):
        pass
    def set_num_threads(self):
        pass
    def get_sorted(self):
        pass
    def get_sequence(self, beginEl, endEl):
        pass
    def get_sequence_multi(self, rangeList):
        pass
    def get_sequence_fixed(self, beginEl, numEl):
        pass


class SorterDist(Sorter):
    """
    Abstract base class for distributed memory sorting
    """
    def init_session(self, comm, sessionID):
        pass
    def kill_session(self, comm, sessionID):
        pass
    def get_sorted(self):
        pass
    def get_sequence(self, beginEl, endEl)
        pass
    def get_sequence_multi(self, rangeList):
        pass
    def get_sequence_fixed(self, beginEl, numEl):
        pass

class SorterDistMPI(SorterDist):
    """
    MPI parallel sorter will be implemented in C++ for tightly coupled
    applications.
    """
    pass

class SorterDistAMQP(SorterDist):
    """
    Python class for loosely coupled distributed computing with AMQP
    library.
    """
    pass

class SorterDistCURL(SorterDist):
    """
    Python class for loosely coupled distributed computing with cURL
    """
    pass

class SorterDistNice(SorterDist):
    """
    Python class for doing sort in background in anticipation of
    needing the result in the future.  The class will stage result on
    local disk and use network only as it becomes available.
    """
