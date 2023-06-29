CC  =   icpx
CFLAGS  = -std=c++17 -I /usr/local/zfp/include -L /usr/local/zfp/lib64 -lzfp
OTHERFLAGS = -c
DEBUG_FLAGS = -g
CXXFLAGS  = -c
INCS  = -I /usr/local/zfp/include

LIBS = -L /usr/local/zfp/lib64 -lzfp -lstdc++

all: applyHadamard applyControlledPhaseShift applyControlledNot testQregQgate qft

SIMULATOR_SRCS = quantumRegister.cpp quantumGate.cpp quantumAlgorithms.cpp utils.cpp 
SIMULATOR_OBJS=$(subst .cpp,.o,$(SIMULATOR_SRCS))



#LINK MAIN PROGRAMS
applyHadamard: $(SIMULATOR_OBJS) applyHadamard.o
	$(CC) $(LIBS) $(CFLAGS) $(DEBUG_FLAGS) $(SIMULATOR_OBJS) applyHadamard.o -o applyHadamard

applyControlledPhaseShift: $(SIMULATOR_OBJS) applyControlledPhaseShift.o
	$(CC) $(LIBS) $(CFLAGS) $(DEBUG_FLAGS) $(SIMULATOR_OBJS) applyControlledPhaseShift.o -o applyControlledPhaseShift

applyControlledNot: $(SIMULATOR_OBJS) applyControlledNot.o
	$(CC) $(LIBS) $(CFLAGS) $(DEBUG_FLAGS) $(SIMULATOR_OBJS) applyControlledNot.o -o applyControlledNot

testQregQgate: $(SIMULATOR_OBJS) testQregQgate.o
	$(CC) $(LIBS) $(CFLAGS) $(DEBUG_FLAGS) $(SIMULATOR_OBJS) testQregQgate.o -o testQregQgate

qft: $(SIMULATOR_OBJS) qft.o
	$(CC) $(LIBS) $(CFLAGS) $(DEBUG_FLAGS) $(SIMULATOR_OBJS) qft.o -o qft



#COMPILE SOURCE MAIN PROGRAMS
applyHadamard.o: applyHadamard.cpp
	$(CC) $(INCS) $(CXXFLAGS) $(DEBUG_FLAG) applyHadamard.cpp

applyControlledPhaseShift.o: applyControlledPhaseShift.cpp
	$(CC) $(INCS) $(CXXFLAGS) $(DEBUG_FLAG) applyControlledPhaseShift.cpp

applyControlledNot.o: applyControlledNot.cpp
	$(CC) $(INCS) $(CXXFLAGS) $(DEBUG_FLAG) applyControlledNot.cpp

testQregQgate.o: testQregQgate.cpp
	$(CC) $(INCS) $(CXXFLAGS) $(DEBUG_FLAG) testQregQgate.cpp

qft.o: qft.cpp
	$(CC) $(INCS) $(CXXFLAGS) $(DEBUG_FLAG) qft.cpp



#COMPILE SIMULATOR SOURCE FILES
quantumRegister.o : quantumRegister.cpp
	$(CC) $(INCS) $(CXXFLAGS) $(DEBUG_FLAG) quantumRegister.cpp

quantumGate.o : quantumGate.cpp
	$(CC) $(INCS) $(CXXFLAGS) $(DEBUG_FLAG) quantumGate.cpp

quantumAlgorithms.o : quantumAlgorithms.cpp
	$(CC) $(INCS) $(CXXFLAGS) $(DEBUG_FLAG) quantumAlgorithms.cpp

utils.o : utils.cpp
	$(CC) $(INCS) $(CXXFLAGS) $(DEBUG_FLAG) utils.cpp




#CLEAN BINARIES
clean: 
	rm -f *.o test



