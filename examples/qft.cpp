#include "tmfqsfs.h"
#include <stdlib.h>
#include <mpi.h>
#include <zfp.h>
#include <iostream>


using namespace std;

//TMFQS
int main(int argc, char *argv[]){

	if(argc != 2){
		cout << "./applyHadamard <Number of Qubits>" << endl;
		return 1;
	}
   else{
		int i, j;
		unsigned int numberOfQubits;
		numberOfQubits = atoi(argv[1]);

		QuantumRegister qureg(numberOfQubits);
		quatumFourierTransform(&qureg);
		qureg.printStatesVector();
	}
}
