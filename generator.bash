#!/bin/bash
#--------------------------------------------------
#
#
SIZE=(100 1000 10000 1000000 10000000 100000000)		#RELATIVE TO STRING
RSIZE=(100 1000 10000 1000000 10000000 100000000)
PREFIX=""
SUFFIX=.file

echo "N = ${SIZE[@]}"
echo "FSIZE = ${RSIZE[@]}"
echo ""
for i in $(seq 0 $((${#SIZE[@]} - 1))); do
	STRING=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 10 | head -n 1)
	printf "Generating N = ${RSIZE[$i]} ..."
	yes $STRING | head -${SIZE[$i]} | tr -d '\n' > Data/$PREFIX${RSIZE[$i]}$SUFFIX
	truncate --size=${RSIZE[$i]} Data/$PREFIX${RSIZE[$i]}$SUFFIX
	echo " DONE"
done
echo ""
echo "============================================"
