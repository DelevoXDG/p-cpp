for file in $2/*.in; do
start=`date +%s%N`
test=${file%.in}.out
diff -bs -c --color <(./$1 < $file)  $test || break
end=`date +%s%N`
printf "\n%.3f%s\n" $(((end-start)/(10**6)))e-3 s
done
