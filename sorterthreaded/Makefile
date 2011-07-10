CC=g++
LD=g++
CPPFLAGS=-O3 -fpic -fopenmp -DSTL_SORT_THREAD_SAFE
LDFLAGS=-fopenmp

all : partition_wall_test partition_test splinter_test quick_sort_test sorter_threaded_test 

profile : profile_sort M3_profile.o

clean :
	rm -f partition_wall_test partition_wall_test.o partition_test partition_test.o splinter_test splinter_test.o quick_sort_test quick_sort_test.o sorter_threaded_test sorter_threaded_test.o M3_profile.o profile_sort.o profile_sort 

partition_wall_test : src/partition_wall.hpp src/partition_wall_test.cpp
	${CC} ${CPPFLAGS} src/partition_wall_test.cpp -o partition_wall_test
	./partition_wall_test

partition_test : src/partition.hpp src/partition_test.cpp
	${CC} ${CPPFLAGS} src/partition_test.cpp -o partition_test
	./partition_test

splinter_test : src/splinter.hpp src/splinter_test.cpp 
	${CC} ${CPPFLAGS} src/splinter_test.cpp -o splinter_test
	./splinter_test
quick_sort_test : src/quick_sort.hpp
	${CC} ${CPPFLAGS} src/quick_sort_test.cpp -o quick_sort_test
	./quick_sort_test
sorter_threaded_test : src/sorter_threaded.hpp src/sorter_threaded_test.cpp
	${CC} ${CPPFLAGS} src/sorter_threaded_test.cpp -o sorter_threaded_test
	./sorter_threaded_test
M3_profile.o : src/M3_profile.c src/M3_profile.h
	${CC} ${CPPFLAGS} -c src/M3_profile.c
profile_sort : M3_profile.o
	${CC} ${CPPFLAGS} src/profile_sort.cpp M3_profile.o -o profile_sort 
	./profile_sort

#