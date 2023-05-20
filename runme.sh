#!/bin/bash

make build_serv
make build_client
./server &
sleep 1
touch result.txt
echo "First task:" > result.txt
./task1.sh
echo "" >> result.txt
echo "Second task:" >> result.txt
./task2.sh
echo "" >> result.txt
echo "Third task:" >> result.txt
./task3.sh
rm /tmp/serv*