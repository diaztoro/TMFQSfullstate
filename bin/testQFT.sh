#!/bin/bash

for numQubits in `seq 1 15`
do
	echo $numQubits '##########################################' >> TMFQSfullState_QFT_results
	(time ./qft $numQubits 0) &>> TMFQS_QFT_results
done


