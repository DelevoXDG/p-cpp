#!/bin/bash
max=$1
source=$2
make make FILES="$source"
mkdir -p Tests/tmp/

for (( id=1; id <= $max; ++id))
do
echo -e "test${id}:"
./main < Tests/test.0${id}.in > Tests/tmp/test${id}.out
diff --color Tests/test.0${id}.oac Tests/tmp/test${id}.out
done
