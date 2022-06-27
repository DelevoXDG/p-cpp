#!/bin/bash
max=8

for ((id = 1; id <= $max; ++id)); do
	echo -e "test${id}:"
	./main <Tests/poker.0${id}.in >test${id}.out
	diff --color Tests/poker.0${id}.oac test${id}.out
done
