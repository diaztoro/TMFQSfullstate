#include "quantumRegister.h"
#include "utils.h"

// Quantum Register class implementation
//
//Constructors ###################################
QuantumRegister::QuantumRegister() {
}

QuantumRegister::QuantumRegister(unsigned int numQubits) {
	this->numQubits = numQubits;
	this->numStates = pow(2,this->numQubits);
	this->amplitudes.resize(this->numStates*2, 0.0);
	this->amplitudes[0] = 1.0;
	/*
	int i;
	this->states.push_back(0);
	this->amplitudes.push_back(1.0);
	this->amplitudes.push_back(0.0);
	for(i=1; i<pow(2,n); i++){
		this->states.push_back(i);
		this->amplitudes.push_back(0.0);
		this->amplitudes.push_back(0.0);
	}
	*/
}

//Constructor by copy
QuantumRegister::QuantumRegister(const QuantumRegister& qreg) {
	/*
	int i, j;
	numQubits = qreg.numQubits;
	amplitudes.resize(pow(2,this->numQubits), 2);
	for(i=0; i < numQubits; i++){
		for(j=0; j < 2; j++){
			amplitudes(i,j) = qreg.amplitudes(i,j);
		}
	}
	*/
	this->amplitudes = qreg.amplitudes;
}

int QuantumRegister::getSize(){
	return this->amplitudes.size();
}

//Get methods ####################################
//
//Get the element i-th of linearized amplitudes vector
Amplitude QuantumRegister::getElement(unsigned int element){
	Amplitude amp;
	amp.real = this->amplitudes[element*2];
	amp.imag = this->amplitudes[element*2 + 1];
	return amp;
}


Amplitude QuantumRegister::amplitude(unsigned int state){
	Amplitude amp;
	int index;
	StatesVector::iterator i = find(this->states.begin(), this->states.end(), state);
	if (i != this->states.end()) {
		index = i - this->states.begin();
		amp.real = this->amplitudes[index];
		amp.imag = this->amplitudes[index + 1];
	}
	else {
		amp.real = -1.0;
		amp.imag = -1.0;
   }
	return amp;
}


//Get the Magnitud or Modulus of the element i-th
double QuantumRegister::probability(unsigned int state){
	Amplitude amp = amplitude(state);
	return sqrt(pow(amp.real, 2) + pow(amp.imag, 2));
}

//Get the sum of magnitudes of the amplitudes
double QuantumRegister::probabilitySumatory(){
	int i;
	double sum = 0.0;
	for(i=0; i<this->numStates; i++){
		sum += pow(this->amplitudes[i*2], 2) + pow(this->amplitudes[i*2 + 1], 2);
	}
	return sum;
}


//Set methods ####################################
void QuantumRegister::setSize(unsigned int numQubits){
	this->numQubits = numQubits;
	this->states.resize(pow(2,numQubits), 0);
	this->amplitudes.resize(pow(2,numQubits)*2, 0.0);
}


// Fill the states vector ramdonly
void QuantumRegister::fillStatesVector(){
	int i, j;
	if ( this->states.size() < this->numQubits ){
		this->setSize(this->numQubits);
	}
	for (i=0; i < pow(2, this->numQubits); i++){
		this->states[i] = i;
		this->amplitudes[i*2] = i;
		this->amplitudes[i*2 + 1] = i;
	}
}

//Miscelaneous methods ###########################
//Print states vector
std::ostream &operator << (std::ostream &os, QuantumRegister &reg) {
	int i, j;
	for(i=0; i<reg.numStates; i++){
		cout << i << ": ";
		cout << reg.amplitudes[i*2] << " " << reg.amplitudes[i*2 + 1] << endl;
	}
	return os;
}

void QuantumRegister::printStatesVector(){
	cout << *this;
}


//Destructor #####################################
QuantumRegister::~QuantumRegister(){
}



//Quantum Gates operations
//
// Method to copy amplitudes vector
AmplitudesVector copyAmplitudes(AmplitudesVector amps){
	AmplitudesVector amps2;
	amps2 = amps;
	/*
	int i, j;

	amps2.resize(amps.size(), 2);
	for(i=0; i < amps.size(); i++){
		for(j=0; j < 2; j++){
			amps2(i,j) = amps(i,j);
		}
	}
	*/
	return amps2;
}

//Get all states according the number of qubits
StatesVector getAllStates(unsigned int qubits){
	StatesVector v;
	int i;

	for(i=0; i < (1 << qubits); i++){
		v.push_back(i);
	}
	return v;
}


string QuantumRegister::getNthBit(unsigned int state, unsigned int qubit){
	unsigned int pos, bit;
	pos = this->numQubits - qubit - 1;   
	bit = (state >> pos) & 1;
	return to_string(bit);
}

int QuantumRegister::findState(unsigned int state){
	int index;
	auto it = std::find(this->states.begin(), this->states.end(), state); 
	if (it != this->states.end()) {
		index = it - this->states.begin();
	}
	else {
		index = -1;
	}
	return index;
}



double QuantumRegister::getProbability(unsigned int state){
	Amplitude amp;
	amp.real = this->amplitudes[state];
	amp.imag = this->amplitudes[state+1];
	return absoluteValue(amp);
}



// Method to apply a quantum gate to quantum register
void QuantumRegister::applyGate(QuantumGate gate, IntegerVector qubits){

	if (gate.dimension != (unsigned int)(1 << qubits.size())) { // 1 << qubits.size is pow(2, qubits.size())
		printf("Unitary matrix dimension is not correct to be applied to the inputs qubits\n");
		return; 
	}

	unsigned int state, newState, pos, tempBit;
	unsigned int stateIndex, newStateIndex;
	string s;
	unsigned int r, saux;
	int i, j, l;
	StatesVector tempStates;
	AmplitudesVector oldAmplitudes;
	Amplitude c, auxAmp1, auxAmp2, auxAmp3;
	
	// Copy the current states
	oldAmplitudes = this->amplitudes;

	tempStates = getAllStates(qubits.size());


	// For all state do
	for( state = 0; state < this->numStates; state++ ){

		//std::cout << "State = " << state << std::endl;
		s = "";

		// Get a string containing the n-th bit of the state according the qubits vector
		for (unsigned int qubit : qubits){
			s += getNthBit(state, qubit);
		}
		// Find which number basis element s corresponds to.
		r = binaryToDecimal(s);
		//std::cout << " s =  " <<  s << " r = " << r << " #############" << std::endl;

		//states[state] -= (1.0 - u[r][r]) * old[state];
		auxAmp1.real = 1.0 - gate[r][r].real;
		auxAmp1.imag =  0.0 - gate[r][r].imag;
		auxAmp2.real = oldAmplitudes[state*2];
		auxAmp2.imag = oldAmplitudes[state*2 + 1];
		// auxAmp2.real = this->amplitudes[state*2];
		// auxAmp2.imag = this->amplitudes[state*2 + 1];
		auxAmp3.real = 0.0;
		auxAmp3.imag = 0.0;
		auxAmp3 = amplitudeMult(auxAmp1, auxAmp2);
		this->amplitudes[state*2] = this->amplitudes[state*2] - auxAmp3.real;
		this->amplitudes[state*2+1] = this->amplitudes[state*2+1] - auxAmp3.imag;
		//std::cout << "Amplitud[" << state << "] = " << this->amplitudes[state*2] << " " << this->amplitudes[state*2+1] << std::endl;
		//std::cout << "oldAmplitud[" << state << "] = " << oldAmplitudes[state*2] << " " << oldAmplitudes[state*2+1] << std::endl;
		j = 0;
		for(int k : tempStates){
			if (j != r) {
				newState = state;
				// COPY ALL BITS FROM k TO newState AT POSITION pos WHICH CORRESPOND TO THE QUBIT WHERE TO APPLY THE GATE
				// qubits.size() IS THE NUMBER OF BITS OF k (BITS TO COPY)
				// For all bits of k
				// l Iterates backward over the bits of k (the most significative bits is on the right)
				// And i iterates forward over qubits vector
				for(l = qubits.size() - 1, i = 0; l >= 0, i < qubits.size(); l--, i++){ 
					// std::cout << "l = " << l << std::endl;
					// get the i-th bit
					tempBit = (k >> l)&1; 
					// std::cout << "k[" << l << "] = " << tempBit << std::endl;
					// std::cout << "qbits[" << i << "] = " << qubits[i] << std::endl;
					pos = this->numQubits - qubits[i] - 1;
					newState = copyBits(newState, tempBit, pos, 1);
				}
				//c = u[j][r] * old[state];
				c.real = gate[j][r].real * oldAmplitudes[state*2];
				c.imag = gate[j][r].imag * oldAmplitudes[state*2+1];
				// c.real = gate[j][r].real * this->amplitudes[state*2];
				// c.imag = gate[j][r].imag * this->amplitudes[state*2+1];
				this->amplitudes[newState*2] += c.real;
				this->amplitudes[newState*2+1] += c.imag;
			}
			j++;
		}
	}
}



// Method to apply a Hadamard gate to specific qubit of a quantum register
void QuantumRegister::Hadamard(unsigned int qubit){
	IntegerVector v;
	v.push_back(qubit);
	applyGate(QuantumGate::Hadamard(), v);
}


// Method to apply a ControlledPhaseShift gate to specific qubit of a quantum register
void QuantumRegister::ControlledPhaseShift(unsigned int controlQubit, unsigned int targetQubit, double theta){
	IntegerVector v;
	v.push_back(controlQubit);
	v.push_back(targetQubit);
	applyGate(QuantumGate::ControlledPhaseShift(theta), v);
}


void QuantumRegister::ControlledNot(unsigned int controlQubit, unsigned int targetQubit) {
	IntegerVector v; v.push_back(controlQubit); v.push_back(targetQubit);
	applyGate(QuantumGate::ControlledNot(), v);
}


void QuantumRegister::Swap(unsigned int qubit1, unsigned int qubit2) {
	ControlledNot(qubit1, qubit2);
	ControlledNot(qubit2, qubit1);
	ControlledNot(qubit1, qubit2);
}
