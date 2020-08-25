#!/bin/bash
#--------------------------------------------------
#
#
STRING=ILOVEPRAYUT
SIZE=(100 1000 10000 1000000 10000000 100000000)		#RELATIVE TO STRING
RSIZE=(100 1000 10000 1000000 10000000 100000000)
PREFIX=""
SUFFIX=.file

echo "N = ${SIZE[@]}"
echo "FSIZE = ${RSIZE[@]}"
echo ""
for i in $(seq 0 $((${#SIZE[@]} - 1))); do
	printf "Generating N = ${RSIZE[$i]} ..."
	yes $STRING | head -${SIZE[$i]} | tr -d '\n' > Data/$PREFIX${RSIZE[$i]}$SUFFIX
	truncate --size=${RSIZE[$i]} Data/$PREFIX${RSIZE[$i]}$SUFFIX
	echo " DONE"
done
echo ""
echo "============================================"
