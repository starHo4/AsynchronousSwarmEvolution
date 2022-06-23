#!/bin/bash

echo Hiroyuki Hoshi
rm -r ./data
mkdir ./data
for ((i=0; i<100; i++)); do
    ./Experiment $i &
done
wait
echo Finished!