#include "quantumRegister.h"
#include "quantumGate.h"
#include <stdlib.h>
#include <mpi.h>
#include <zfp.h>
#include <zfp/array2.hpp>
#include "array2d.h"
#include <iostream>


using namespace std;

//TMFQS
int main(int argc, char *argv[]){

	if(argc != 3){
		cout << "./applyHadamard <Number of Qubits> <qubit>" << endl;
		return 1;
	}
   else{
		int i, j;
		unsigned int numberOfQubits, qubit;
		numberOfQubits = atoi(argv[1]);
		qubit = atoi(argv[2]);

		QuantumRegister qreg(numberOfQubits);
		for(int i=0; i<numberOfQubits; i++){
			qreg.Hadamard(i);
		}
		qreg.printStatesVector();
		//qreg.Hadamard(qubit);
		//qreg.printStatesVector();


		return 0;
	}
}
