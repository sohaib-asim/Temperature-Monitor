#!/bin/bash

tempInitial=$(./temperature);

while true
do
	tempCurrent=$(./temperature);
	echo $tempCurrent
	tempDiff=$(($tempCurrent-$tempInitial))
	tempDiff=$(($tempDiff/1000))
	tempDiff=${tempDiff#-}
	
	echo $tempInitial, $tempDiff
	
	if [ $tempDiff -lt 1 ]
	then
		gpio write 0 0;
		gpio write 1 0;
		gpio write 2 0;
	fi
	
	if [ $tempDiff -ge 1 -a $tempDiff -lt 2 ]
	then
		gpio write 0 1;
		gpio write 1 0;
		gpio write 2 0;
	fi
	
	if [ $tempDiff -ge 2 -a $tempDiff -lt 3 ]
	then
		gpio write 0 1;
		gpio write 1 1;
		gpio write 2 0;
	fi
	
	if [ $tempDiff -ge 3 ]
	then
		gpio write 0 1;
		gpio write 1 1;
		gpio write 2 1;
	fi
done
