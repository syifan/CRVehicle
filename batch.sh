#!/bin/bash

for a in PaperWithIA PaperWithoutIA PureQuery
do
	for d in 20
	do
		for v in 20
		do
			for r in 0 1 2 3
			do
				./main -a$a -d$d -v$v -r$r -o{$a}d{$d}v{$v}r{$r} &
			done
		done
	done
done
