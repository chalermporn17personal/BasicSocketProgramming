#!/bin/bash
calc(){ awk "BEGIN { print "$*" }"; }
times=$1
SCRIPT="$(echo $2)"
cnt=0
sum=0
$tttt=1000
while [ $cnt -lt $times ]
do
    echo "-------- Round $cnt start --------"
    start=$(date +%s.%3N)
    echo ${SCRIPT}
    eval ${SCRIPT}
    end=$(date +%s.%6N)
    t=$(echo "$end - $start" | bc)
    echo "Round $cnt  --- Times : $t second."
    cnt=$((cnt + 1 ))
    sum=$(echo "$t + $sum" | bc)
    checksum=$(sha256sum output.file)
    echo checksum = $checksum
    FILENAME=output.file
    FILESIZE=$(stat -c%s "$FILENAME")
    echo "Size of $FILENAME = $FILESIZE bytes."
    spd=$(calc $FILESIZE/$t)
    spd=$(calc $spd/1000)
    echo "Speed : $spd KBps"
    echo ""
    
    sleep .2
done
avg=$(calc $sum/$times)
echo "average : $avg seconds."
spd=$(calc $FILESIZE/$avg)
spd=$(calc $spd/1000)
echo "Average Speed : $spd KBps."
echo ""