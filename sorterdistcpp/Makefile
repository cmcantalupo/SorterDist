CC=g++
AR=ar
RANLIB=ranlib
CFLAGS=-O3 -fpic

all : partition.o partition_wall.o splinter.o sorter_threaded.o

clean :
	rm -f partition.o partition_wall.o partition_wall_test.o partition_wall_test partition_test.o partition_test splinter.o splinter_test.o splinter_test sorter_threaded.o sorter_threaded_test.o sorter_threaded_test 

partition_wall.o : src/partition_wall.cpp src/partition_wall.hpp src/sorter_threaded_exception.hpp src/partition_wall_test.cpp
	${CC} ${CFLAGS} -c src/partition_wall.cpp
	${CC} ${CFLAGS} -c src/partition_wall_test.cpp 
	${CC} ${CFLAGS} partition_wall_test.o partition_wall.o -o partition_wall_test
	./partition_wall_test

partition.o : partition_wall.o src/partition.cpp src/partition.hpp src/sorter_threaded_exception.hpp src/partition_test.cpp
	${CC} ${CFLAGS} -c src/partition.cpp 
	${CC} ${CFLAGS} -c src/partition_test.cpp
	${CC} ${CFLAGS} partition_test.o partition_wall.o partition.o -o partition_test
	./partition_test

splinter.o : src/splinter.cpp src/splinter.hpp src/sorter_threaded_exception.hpp src/splinter_test.cpp 
	${CC} ${CFLAGS} -c src/splinter.cpp 
	${CC} ${CFLAGS} -c src/splinter_test.cpp
	${CC} ${CFLAGS} splinter_test.o splinter.o -o splinter_test 
	./splinter_test

sorter_threaded.o : partition.o partition_wall.o splinter.o src/sorter_threaded.cpp src/sorter_threaded.hpp src/sorter_threaded_exception.hpp src/sorter_threaded_test.cpp
	${CC} ${CFLAGS} -c src/sorter_threaded.cpp -D _OPENMP
	${CC} ${CFLAGS} -c src/sorter_threaded_test.cpp
	${CC} ${CFLAGS} sorter_threaded_test.o sorter_threaded.o splinter.o partition_wall.o partition.o -o sorter_threaded_test
	./sorter_threaded_test


