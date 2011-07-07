CC=g++
AR=ar
RANLIB=ranlib
CFLAGS=-O3 -fpic

all : partition.o partition_wall.o partition_test.o partition_test splinter.o splinter_test sorter_threaded.o sorter_threaded_test

clean :
	rm -f partition.o partition_wall.o partition_test.o partition_test splinter.o splinter_test sorter_threaded.o sorter_threaded_test

partition_wall.o : src/partition_wall.cpp src/partition_wall.hpp src/sorter_threaded_exception.hpp
	${CC} ${CFLAGS} -c src/partition_wall.cpp

partition.o : src/partition.cpp src/partition.hpp src/sorter_threaded_exception.hpp
	${CC} ${CFLAGS} -c src/partition.cpp 
partition_test.o : src/partition_test.cpp src/partition.hpp src/partition_wall.hpp src/sorter_threaded_exception.hpp
	${CC} ${CFLAGS} -c src/partition_test.cpp 
partition_test : partition_test.o partition_wall.o partition.o
	${CC} ${CFLAGS} partition_test.o partition_wall.o partition.o -o partition_test
	./partition_test

splinter.o : src/splinter.cpp src/splinter.hpp
	${CC} ${CFLAGS} -c src/splinter.cpp 

splinter_test : splinter.o 
	${CC} ${CFLAGS} -c src/splinter_test.cpp
	${CC} ${CFLAGS} splinter.o splinter_test.o -o splinter_test 
	./splinter_test

sorter_threaded.o : src/sorter_threaded.cpp src/sorter_threaded.hpp src/sorter_threaded_exception.hpp
	${CC} ${CFLAGS} -c src/sorter_threaded.cpp -D _OPENMP

sorter_threaded_test : src/sorter_threaded.cpp src/sorter_threaded.hpp sorter_threaded.o splinter.o partition_wall.o partition.o 
	${CC} ${CFLAGS} -c src/sorter_threaded_test.cpp 
	${CC} ${CFLAGS} sorter_threaded_test.o sorter_threaded.o splinter.o partition_wall.o partition.o -o sorter_threaded_test
	./sorter_threaded_test


