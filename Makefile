
CXX=g++
CXX_FLAGS=-Wall -g -std=c++0x -I${INC_DIR} -I${SRC_DIR}

INC_DIR=./include/
SRC_DIR=./src/
TEST_DIR=./test/
TEST_SRC=$(wildcard ./test/test_*.cpp)
TEST_OBJ=$(patsubst %.cpp, %.o, $(TEST_SRC))

analytical1D : ${TEST_OBJ} ${SRC_DIR}AnaImage.o ${SRC_DIR}Image.o ${SRC_DIR}Trapezoid.o ${SRC_DIR}LineIntegral.o
	${CXX} ${CXX_FLAGS} $^ -o $@
	chmod +x $@
%.o : %.cpp
	${CXX} ${CXX_FLAGS} -c $< -o $@
${SRC_DIR}%.o : ${SRC_DIR}%.cpp
	${CXX} ${CXX_FLAGS} -c $< -o $@

.PHONY : clean
clean :
	rm ${SRC_DIR}*.o
	rm ${TEST_DIR}*.o
