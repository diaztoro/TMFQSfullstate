#ifndef QUANTUM_INCLUDE
#define QUANTUM_INCLUDE

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <algorithm>
#include "types.h"
#include "quantumGate.h"

using namespace std;

class QuantumRegister {

	public:
		unsigned int numQubits;
		AmplitudesVector amplitudes;
		StatesVector states;

		//Constructors ###################################
		QuantumRegister();
		QuantumRegister(unsigned int n);
		QuantumRegister(const QuantumRegister&);

		int getSize();

		//Accessors ######################################
		//

		//Get the element i-th
		Amplitude getElement(unsigned int);

		//Get the Magnitud or Modulus of the element i-th
		double probability(unsigned int state);

		//Get the sum of magnitudes of the statesVector
		double magnitudSumatory();


		//Get the amplitude of specific state
		Amplitude amplitude(unsigned int state);

		static StatesVector allStates();

		//Set methods ####################################
		//
		void setSize(unsigned int);

		// Fill the states vector ramdonly
		void fillStatesVector();

		//Miscelaneous methods ###########################
		//Print states vector
		void printStatesVector();
		friend std::ostream &operator << (std::ostream &os, QuantumRegister &reg);
		string getNthBit(unsigned int state, unsigned int qubit);
		int findState(unsigned int state);

		//Destructor #####################################
		~QuantumRegister();


		//Quantum Gates operations
		void applyGate(QuantumGate g, IntegerVector v);
		void Hadamard(unsigned int qubit);
		void ControlledPhaseShift(unsigned int controlQubit, unsigned int targetQubit, double theta);
};

#endif
