#!/bin/bash

for a in PureQuery PaperWithoutIA PaperWithIA
do
	for l in 0.01 0.05 0.10 0.20 0.50 1.00 
	do
		for v in 1 5 10 15 20 25 30
		do
			./main -a$a -l$l -v$v -o{$a}l{$l}v{$v} &
		done
	done
done
