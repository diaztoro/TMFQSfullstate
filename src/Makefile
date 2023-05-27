CC  =   icpx
CFLAGS  = -std=c++17 -I /usr/local/zfp/include -L /usr/local/zfp/lib64 -lzfp
OTHERFLAGS = -c
DEBUG_FLAGS = -g
CXXFLAGS  = -c
INCS  = -I /usr/local/zfp/include

LIBS = -L /usr/local/zfp/lib64 -lzfp -lstdc++

all: applyHadamard applyControlledPhaseShift testQregQgate

SIMULATOR_SRCS = quantumRegister.cpp quantumGate.cpp utils.cpp 
SIMULATOR_OBJS=$(subst .cpp,.o,$(SIMULATOR_SRCS))



#LINK MAIN PROGRAMS
applyHadamard: $(SIMULATOR_OBJS) applyHadamard.o
	$(CC) $(LIBS) $(CFLAGS) $(DEBUG_FLAGS) $(SIMULATOR_OBJS) applyHadamard.o -o applyHadamard

applyControlledPhaseShift: $(SIMULATOR_OBJS) applyControlledPhaseShift.o
	$(CC) $(LIBS) $(CFLAGS) $(DEBUG_FLAGS) $(SIMULATOR_OBJS) applyControlledPhaseShift.o -o applyControlledPhaseShift

testQregQgate: $(SIMULATOR_OBJS) testQregQgate.o
	$(CC) $(LIBS) $(CFLAGS) $(DEBUG_FLAGS) $(SIMULATOR_OBJS) testQregQgate.o -o testQregQgate



#COMPILE SOURCE MAIN PROGRAMS
applyHadamard.o: applyHadamard.cpp
	$(CC) $(INCS) $(CXXFLAGS) $(DEBUG_FLAG) applyHadamard.cpp

applyControlledPhaseShift.o: applyControlledPhaseShift.cpp
	$(CC) $(INCS) $(CXXFLAGS) $(DEBUG_FLAG) applyControlledPhaseShift.cpp

testQregQgate.o: testQregQgate.cpp
	$(CC) $(INCS) $(CXXFLAGS) $(DEBUG_FLAG) testQregQgate.cpp



#COMPILE SIMULATOR SOURCE FILES
quantumRegister.o : quantumRegister.cpp
	$(CC) $(INCS) $(CXXFLAGS) $(DEBUG_FLAG) quantumRegister.cpp

quantumGate.o : quantumGate.cpp
	$(CC) $(INCS) $(CXXFLAGS) $(DEBUG_FLAG) quantumGate.cpp

utils.o : utils.cpp
	$(CC) $(INCS) $(CXXFLAGS) $(DEBUG_FLAG) utils.cpp




#CLEAN BINARIES
clean: 
	rm -f *.o test



