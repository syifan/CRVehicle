#!/bin/bash

for a in PaperWithIA PaperWithoutIA PureQuery CSMA
do
	for d in 1 2 5 10 20 50 100 200 500 1000 
	do
		for v in 1 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30
		do
			./main -a$a -d$d -v$v -o{$a}d{$d}v{$v} &
		done
	done
done
