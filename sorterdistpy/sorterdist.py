class Sorter(list): 
    """ 
    Class that defines the basic functionality of SorterDist for
    serial sorting.  We are deriving from list so sort() is built
    in.  
    """
    def __init__(self, data=None, comp=None):
        list.__init__(self, data)
        self._comp = comp
    def sorted(self):
        return sorted(self)
    def sorted_permutation(self):
        return sorted(range(len(self)), key = self.__getitem__)
    def sorted_sequence(self, bounds):
        ss = self.sorted()
        if type(bounds[0]) == list or type(bounds[0]) == tuple:
            result = [ss[ss.index(bb[0]) : ss.index(bb[1]) + 1] for bb in bounds]
            return result
        return ss[ss.index(bounds[0]) : ss.index(bounds[1]) + 1]
    def sorted_sequence_permutation(self, range):
        raise NotImplementedError()
    def set_comp(self, comp):
        raise NotImplementedError()


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
    def sort(self):
        pass
    def sorted(self):
        pass
    def sorted_permutation(self):
        pass
    def sorted_sequence(self, bounds):
        pass
    def sorted_sequence_permutation(self, bounds):
        pass

class SorterDistSession(object):
    """
    Distributed sort will require setting up a communicator
    of some kind.  
    """
    def init_session(self, comm, sessionID):
        pass
    def kill_session(self, comm, sessionID):
        pass
    def attach_sorter(self, sorter):
        pass

class SorterDistMPI(Sorter):
    """
    MPI parallel sorter will be implemented in C++ for tightly coupled
    applications.
    """
    pass

class SorterDistAMQP(Sorter):
    """
    Python class for loosely coupled distributed computing with AMQP
    library.
    """
    pass

class SorterDistCURL(Sorter):
    """
    Python class for loosely coupled distributed computing with cURL
    """
    pass

class SorterDistNice(Sorter):
    """
    Python class for doing sort in background in anticipation of
    needing the result in the future.  The class will stage result on
    local disk and use network only as it becomes available.
    """
    pass

if __name__ == '__main__':
    import random
    dd = range(10)
    random.shuffle(dd)
    dd = Sorter(dd)
    print dd
    ss = dd.sorted()
    print ss
    ii = dd.sorted_permutation()
    print ii
    print [dd[i] for i in ii]
    bounds = [0,3]
    print bounds
    ii = dd.sorted_sequence(bounds)
    print ii
    bounds = [[0,3],[7,9]]
    print bounds
    ii = dd.sorted_sequence(bounds)
    print ii

