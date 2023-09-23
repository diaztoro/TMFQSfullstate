#include "tmfqsfs.h"
#include <stdlib.h>
#include <iostream>


using namespace std;

//TMFQS
int main(int argc, char *argv[]){

	if(argc != 3){
		//cout << "./applyHadamard <Number of Qubits> <qubit> <init state>" << endl;
		cout << "./applyHadamard <Number of Qubits> <qubit>" << endl;
		return 1;
	}
   else{
		int i, j;
		unsigned int numQubits = 0, qubit, initState = 0;
		numQubits = atoi(argv[1]);
		qubit = atoi(argv[2]);
		initState = atoi(argv[3]);

		//QuantumRegister qreg(numQubits, initState);
		QuantumRegister qreg(numQubits, true);
		qreg.printStatesVector();
		std::cout << std::endl;
		qreg.Hadamard(qubit);
		/*
		for(int i=0; i<numQubits; i++){
			qreg.Hadamard(i);
		}
		*/
		qreg.printStatesVector();
		//qreg.ControlledPhaseShift(controlQubit, targetQubit, theta);
		//qreg.printStatesVector();


		return 0;
	}
}
