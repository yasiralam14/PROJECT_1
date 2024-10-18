wc -l data.dat
grep -E 'dolor|dalor' data.dat | wc -l
wc -w data.dat
cat data.dat|tr ' ' '\n' | grep '^mol' | wc -w
