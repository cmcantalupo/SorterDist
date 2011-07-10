CC=g++
LD=g++
CPPFLAGS=-O3 -fpic -fopenmp -DSTL_SORT_THREAD_SAFE
LDFLAGS=-fopenmp


all : partition.o partition_wall.o splinter.o sorter_threaded.o

clean :
	rm -f partition.o partition_wall.o partition_wall_test.o partition_wall_test partition_test.o partition_test splinter.o splinter_test.o splinter_test quick_sort.o quick_sort_test.o quick_sort_test sorter_threaded.o sorter_threaded_test.o sorter_threaded_test 

partition_wall.o : src/partition_wall.cpp src/partition_wall.hpp src/sorter_threaded_exception.hpp src/partition_wall_test.cpp
	${CC} ${CPPFLAGS} -c src/partition_wall.cpp
	${CC} ${CPPFLAGS} -c src/partition_wall_test.cpp 
	${LD} ${LDFLAGS} partition_wall_test.o partition_wall.o -o partition_wall_test
	./partition_wall_test

partition.o : partition_wall.o src/partition.cpp src/partition.hpp src/sorter_threaded_exception.hpp src/partition_test.cpp
	${CC} ${CPPFLAGS} -c src/partition.cpp 
	${CC} ${CPPFLAGS} -c src/partition_test.cpp
	${LD} ${LDFLAGS} partition_test.o partition_wall.o partition.o -o partition_test
	./partition_test

splinter.o : src/splinter.cpp src/splinter.hpp src/sorter_threaded_exception.hpp src/splinter_test.cpp 
	${CC} ${CPPFLAGS} -c src/splinter.cpp 
	${CC} ${CPPFLAGS} -c src/splinter_test.cpp
	${LD} ${LDFLAGS} splinter_test.o splinter.o -o splinter_test 
	./splinter_test
quick_sort.o : src/quick_sort.cpp src/quick_sort.hpp
	${CC} ${CPPFLAGS} -c src/quick_sort.cpp
	${CC} ${CPPFLAGS} -c src/quick_sort_test.cpp
	${LD} ${LDFLAGS} quick_sort_test.o quick_sort.o -o quick_sort_test
	./quick_sort_test

sorter_threaded.o : partition.o partition_wall.o splinter.o quick_sort.o src/sorter_threaded.cpp src/sorter_threaded.hpp src/sorter_threaded_exception.hpp src/sorter_threaded_test.cpp
	${CC} ${CPPFLAGS} -c src/sorter_threaded.cpp
	${CC} ${CPPFLAGS} -c src/sorter_threaded_test.cpp
	${LD} ${LDFLAGS} sorter_threaded_test.o sorter_threaded.o splinter.o partition_wall.o partition.o quick_sort.o -o sorter_threaded_test
	./sorter_threaded_test


