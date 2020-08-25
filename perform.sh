#!/bin/bash
calc(){ awk "BEGIN { print "$*" }"; }
times=$1
SCRIPT="$(echo $2)"
cnt=0
sum=0
while [ $cnt -lt $times ]
do
    echo "-------- Round $cnt start --------"
    start=$(date +%s.%3N)
    echo ${SCRIPT}
    eval ${SCRIPT}
    cnt=$((cnt + 1 ))
    end=$(date +%s.%6N)
    t=$(echo "$end - $start" | bc)
    echo "Round $cnt  --- Times : $t second."
    sum=$(echo "$t + $sum" | bc)
    checksum=$(sha256sum output.file)
    echo checksum = $checksum
    FILENAME=output.file
    FILESIZE=$(stat -c%s "$FILENAME")
    echo "Size of $FILENAME = $FILESIZE bytes."
    echo ""
    sleep .1
done
avg=$(calc $sum/$times)
echo "average : $avg"
echo ""