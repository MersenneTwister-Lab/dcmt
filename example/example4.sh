#!/bin/bash
mexp=$1
inter=$((65536/16))
for ((i = 0; i < 16; i++)) do
from=$(printf "%05d" $((i * inter)))
to=$(printf "%05d" $(((i+1) * inter -1)))
nohup ./example4 32 $mexp $((i * inter)) $(((i+1)*inter-1)) > example4.32.${mexp}.${from}-${to}.txt &
done
