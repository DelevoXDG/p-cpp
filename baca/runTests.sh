#!/bin/bash
max=8

# make make FILES="${1}"

for (( id=1; id <= $max; ++id))
do
echo -e "test${id}:"
./main < Tests/PokerKostkowy/poker.0${id}.in > test${id}.out
diff --color Tests/PokerKostkowy/poker.0${id}.oac test${id}.out
done
