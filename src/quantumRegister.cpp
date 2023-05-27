#include "quantumRegister.h"
#include "utils.h"

// Quantum Register class implementation
//
//Constructors ###################################
QuantumRegister::QuantumRegister() {
}

QuantumRegister::QuantumRegister(unsigned int n) {
	this->numQubits = n;
	this->states.push_back(0);
	this->amplitudes.push_back(1.0);
	this->amplitudes.push_back(0.0);
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
double QuantumRegister::magnitudSumatory(){
	int i, sum=0;
	for(i=0; i<this->numQubits; i++){
		sum += pow(this->amplitudes[i*2], 2) + pow(this->amplitudes[i*2 + 1], 2);
	}
	return sum;
}


//Set methods ####################################
void QuantumRegister::setSize(unsigned int numQubits){
	this->numQubits = numQubits;
	this->amplitudes.resize(this->numQubits*2);
	this->states.resize(this->numQubits);
}


// Fill the states vector ramdonly
void QuantumRegister::fillStatesVector(){
	int i, j;
	if ( this->states.size() < this->numQubits ){
		this->amplitudes.resize(this->numQubits*2);
	}
	for (i=1; i < this->numQubits; i++){
		this->states.push_back(i);
		this->amplitudes.push_back(i);
		this->amplitudes.push_back(i);
	}
}

//Miscelaneous methods ###########################
//Print states vector
std::ostream &operator << (std::ostream &os, QuantumRegister &reg) {
	int i = 0, j;
	for(auto &element : reg.states){
		cout << element << ": ";
		cout << reg.amplitudes[i*2] << " " << reg.amplitudes[i*2 + 1] << endl;
		i++;
	}
	/*
	for(auto &amp : reg.amplitudes){
		cout << amp << endl;
	}
	*/
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

//Get all states accoding the number of qubits
StatesVector getAllStates(unsigned int qubits){
	StatesVector v;
	int i;

	for(i=0; i <= qubits; i++){
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

// Method to apply a quantum gate to quantum register
void QuantumRegister::applyGate(QuantumGate gate, IntegerVector qubits){

	if (gate.dimension != (unsigned int)(1 << qubits.size())) { // 1 << qubits.size is pow(2, qubits.size())
		printf("Unitary matrix dimension is not correct to be applied to the inputs qubits\n");
		return; 
	}

	unsigned int state, i, pos;
	int stateIndex, newStateIndex;
	string s;
	unsigned int r, j, saux; 
	StatesVector oldStates, tempStates;
	AmplitudesVector oldAmplitudes;
	Amplitude c, auxAmp1, auxAmp2, auxAmp3;
	
	//oldAmplitudes = copyAmplitudes(this->amplitudes);
	oldAmplitudes = this->amplitudes;
	oldStates = this->states;
	////std::cout << "qubits.size = " << qubits.size() << std::endl;
	tempStates = getAllStates(qubits.size());

	/*
	cout << "States vector" << endl;
	for (unsigned int i : states){
		cout << states[i] << endl;
	}
	cout << "Old States vector" << endl;
	for (unsigned int i : oldStates){
		cout << oldStates[i] << endl;
	}
	cout << "Temp States vector" << endl;
	for (unsigned int i : tempStates){
		cout << tempStates[i] << endl;
	}
	*/


	////std::cout  << "####### Applying  Gate on qubit: " << qubits[0] << " qubits size = " << qubits.size() << std::endl;
	//for (state_map::iterator i = old.begin(); i != old.end(); ++i) {
	for( i = 0; i < oldStates.size(); i++ ){
		//state = i->first; 
		state = oldStates[i];
		////std::cout << "State = " << state << std::endl;
		stateIndex = findState(state);
		s = "";

		//for (unsigned int q : qubits) s += state[q];
		for (unsigned int qubit : qubits){
			s += getNthBit(state, qubit);
			////std::cout << "qubit = " << qubit << "   s = " << s << " ################" << std::endl;
		}
		//r = binary_to_base10(s); // Find which number basis element s corresponds to.
		r = binaryToDecimal(s);

		////std::cout << " s =  " <<  s << " r = " << r << " #############" << std::endl;



	/*
		states[state] -= (1.0 - u[r][r]) * old[state];
	*/
		//std::cout << "State = " << state << "    Amplitud = " << this->amplitudes[stateIndex] << std::endl;
		//std::cout  << std::endl << std::endl;

		////std::cout << "Old State: " << oldAmplitudes[stateIndex*2] << " " << oldAmplitudes[stateIndex*2 + 1] << std::endl;
		////std::cout << "Gate: " <<  gate[r][r].real << " " << gate[r][r].imag << " r = " << r << std::endl;
		auxAmp1.real = 1.0 - gate[r][r].real;
		auxAmp1.imag =  0.0 - gate[r][r].imag;
		auxAmp2.real = oldAmplitudes[stateIndex*2];
		auxAmp2.imag = oldAmplitudes[stateIndex*2 + 1];
		auxAmp3.real = 0.0;
		auxAmp3.imag = 0.0;
		auxAmp3 = amplitudeMult(auxAmp1, auxAmp2);
		//std::cout << "amplitude1: " <<  auxAmp1.real << " " << auxAmp1.imag << std::endl;
		//std::cout << "amplitude2: " <<  auxAmp2.real << " " << auxAmp2.imag << std::endl;
		//std::cout << "amplitude3: " <<  auxAmp3.real << " " << auxAmp3.imag << std::endl;
		this->amplitudes[stateIndex*2] = this->amplitudes[stateIndex*2] - auxAmp3.real;
		this->amplitudes[stateIndex*2+1] = this->amplitudes[stateIndex*2+1] - auxAmp3.imag;
		////std::cout << "amplitudes[" << state << "] = " << this->amplitudes[stateIndex*2] << " " << this->amplitudes[stateIndex*2+1] << std::endl;
		////std::cout << *this << std::endl;

	
		/*
		// NOT YET CONSIDERED 
		// if (states[state] == 0.0) states.erase(state); // Get rid of it.
		if (probability(state) < 1e-16) states.erase(state); // zero beyond machine precision.
		*/

		/*
		j = 0;
		for(string k : temp_states) {
			if (j != r) {
				s = state;
				for (unsigned int l = 0; l < k.size(); l++) s[qubits[l]] = k[l];
				c = u[j][r] * old[state];
				if (check_state(s)) {
					states[s] += c;
					// if (states[s] == 0.0) states.erase(s);
					if (probability(s) < 1e-16) states.erase(s); // zero beyond machine precision.
				} else if(c != 0.0) states[s] = c;
			}
			j++;
		}
		*/
		j = 0;
		for(int k : tempStates){
			////std::cout << "j = " << j << " k = " << k << std::endl;
			if (j != r) {
				saux = state;
				// COPY ALL BITS FROM k TO saux AT POSITION pos WHICH CORRESPOND TO THE QUBIT WHERE TO APPLY THE GATE
				// qubits.size() IS THE NUMBER OF BITS OF k (BITS TO COPY)
				pos = this->numQubits - qubits.size() - qubits[0];
				saux = copyBits(saux, k, pos, qubits.size());
				////std::cout << "saux = " << saux << std::endl;
				c.real = gate[j][r].real * oldAmplitudes[stateIndex*2];
				c.imag = gate[j][r].imag * oldAmplitudes[stateIndex*2+1];
				////std::cout << "c: " <<  c.real << " " << c.imag << std::endl;
				newStateIndex = findState(saux);
				////std::cout << "oldAmplitudes = " << oldAmplitudes[stateIndex] << " " << oldAmplitudes[stateIndex+1] << std::endl;
				////std::cout << "Gate[j][r] = " << gate[j][r].real << " " << gate[j][r].imag << std::endl;
				//std::cout << "saux = " << saux << " newStateIndex = " << newStateIndex << std::endl;
				if(newStateIndex != -1){
					this->amplitudes[newStateIndex*2] += c.real;
					this->amplitudes[newStateIndex*2+1] += c.imag;
				}
				else{
					////std::cout << "saux = " << saux << " newStateIndex = " << newStateIndex << std::endl;
					this->states.push_back(saux);
					this->amplitudes.push_back(c.real);
					this->amplitudes.push_back(c.imag);
				}
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
