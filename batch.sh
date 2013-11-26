#!/bin/bash

for a in PureQuery PaperWithoutIA PaperWithIA
do
	for l in 0.05 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0 1.1
	do
		for v in 1 3 5 7 9 11 13 15 17 20 23 25 27 29 31
		do
			./main -a$a -l$l -v$v -o{$a}l{$l}v{$v}
		done
	done
done
