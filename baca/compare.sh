#!/bin/bash
max=7

make make FILES="${1}" EXE="exe1"
make make FILES="${2}" EXE="exe2"

for (( i=1; i <= $max; ++i))
do
echo -e "test${i}:"
./exe1 < Tests/PokerKostkowy/poker.0${i}.in > tests2/1-test${i}.out
./main < Tests/PokerKostkowy/poker.0${i}.in > tests2/2-test${i}.out
diff --color tests2/1-test${i}.out tests2/2-test${i}.out
done
