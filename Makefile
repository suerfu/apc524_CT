CXX=g++
CXX_FLAGS=-Wall -g -std=c++0x 
INCLUDE= -I./include -I/usr/local/hdf5/include -I/usr/local/include
LINKER= -L /usr/local/hdf5/lib
LIBS= -lhdf5 -lhdf5_cpp -lhdf5_hl -lhdf5_hl_cpp

INC_DIR=./include/
SRC_DIR=./src/
TEST_DIR=./test/

.PHONY: test
test : testNumCurve testSBP testNumSurface 

test% : ./test/test%.cpp $(patsubst %.cpp, %.o, $(wildcard ./src/*.cpp))
	${CXX} ${CXX_FLAGS} ${INCLUDE} $^ ${LINKER} ${LIBS} -o $@
	chmod +x $@

#testSBP : ./test/testSBP.cpp $(patsubst %.cpp, %.o, $(wildcard ./src/*.cpp))
#	${CXX} ${CXX_FLAGS} $^ -o $@
#	chmod +x $@

%.o : %.cpp
	${CXX} ${CXX_FLAGS} ${INCLUDE} -c $< -o $@

${SRC_DIR}%.o : ${SRC_DIR}%.cpp
	${CXX} ${CXX_FLAGS} ${INCLUDE} -c $< -o $@

.PHONY : clean
clean :
	rm ${SRC_DIR}*.o
	rm ${TEST_DIR}*.o
