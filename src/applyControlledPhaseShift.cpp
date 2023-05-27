#include "quantumRegister.h"
#include "quantumGate.h"
#include <stdlib.h>
#include <mpi.h>
#include <zfp.h>
#include <zfp/array2.hpp>
#include "array2d.h"
#include <iostream>


using namespace std;

int main(int argc, char *argv[]){

	if(argc != 5){
		cout << "./applyHadamard <Number of Qubits> <controlQubit> <targetQubit> <theta>" << endl;
		return 1;
	}
   else{
		int i, j;
		unsigned int numberOfQubits, controlQubit, targetQubit;
		double theta;
		numberOfQubits = atoi(argv[1]);
		controlQubit = atoi(argv[2]);
		targetQubit = atoi(argv[3]);
		theta = atof(argv[4]);

		/*
		QuantumGate g1(4), g2(4);
		g2 = g1.ControlledPhaseShift(theta);
		g2.printQuantumGate();
		*/

		QuantumRegister qreg(numberOfQubits);
		for(int i=0; i<numberOfQubits; i++)
			qreg.Hadamard(i);
		//qreg.printStatesVector();
		cout << "Applying Controlled Phase Shift" << endl << endl;
		qreg.ControlledPhaseShift(controlQubit, targetQubit, theta);
		qreg.printStatesVector();


		return 0;
	}
}
