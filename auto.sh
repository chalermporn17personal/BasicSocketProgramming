#!/bin/bash
for j in 100 1000 10000 1000000 10000000 100000000
do
    echo "---------------------------------------------------------"
    echo Data size = $j Bytes.
    echo "---------------------------------------------------------"
    echo ""
    x="./client $1 $2 Data/$j.file output.file"
    ./perform.sh $3 "$x"
done