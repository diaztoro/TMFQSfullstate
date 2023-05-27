#include <iostream>
#include "types.h"

using namespace std;

int main(int argc, char *argv[]){
	AmplitudesVector amplitudes;

	amplitudes.resize(1, 2);
	amplitudes(0,0) = 1.0;
	amplitudes(0,1) = 0.0;
	cout << amplitudes[0] << endl;
	cout << *(amplitudes[0]+1) << endl;

	return 0;
}
