CC=g++
AR=ar
RANLIB=ranlib
CFLAGS=-O3 -fpic

all : partition.o partition_wall.o partition_test.o partition_test

clean :
	rm -f partition.o partition_wall.o partition_test.o partition_test
partition_wall.o : src/partition_wall.cpp src/partition_wall.hpp src/sorter_threaded_exception.hpp
	${CC} ${CFLAGS} -c src/partition_wall.cpp
partition.o : src/partition.cpp src/partition.hpp src/sorter_threaded_exception.hpp
	${CC} ${CFLAGS} -c src/partition.cpp 
partition_test.o : src/partition_test.cpp src/partition.hpp src/partition_wall.hpp src/sorter_threaded_exception.hpp
	${CC} ${CFLAGS} -c src/partition_test.cpp 
partition_test : partition_test.o partition_wall.o partition.o
	${CC} ${CFLAGS} partition_test.o partition_wall.o partition.o -o partition_test
	./partition_test
