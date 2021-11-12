#!/bin/bash
max=7

make make FILES="${1}"

for (( i=1; i <= $max; ++i))
do
echo -e "test${i}:"
./main < Tests/PokerKostkowy/poker.0${i}.in > test${i}.out
diff Tests/PokerKostkowy/poker.0${i}.oac test${i}.out
done
