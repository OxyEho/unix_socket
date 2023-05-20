#!/bin/bash

clients=(10, 30, 40, 80, 100)
delays=(0, 0.2, 0.4, 0.6, 0.8, 1)

touch /tmp/client.log

for c in ${clients}
do
    for d in ${delays}
    do
        echo "Test with clients: $c delay: $d" >> result.txt
        start_time="$(date -u +%s)"
        for ((i=1; i<=$c;i++));
        do
            (./client $i $d < nums) >> /tmp/client.log &
        done
        wait
        end_time="$(date -u +%s)"
        total_time="$(($end_time-$start_time))"
        max_delay=$(grep -Eo '[0-9].[0-9]+' /tmp/client.log | sort -rn | head -n 1)
        echo "Max sum delay: $max_delay seconds" >> result.txt
        effective_time="$(($total_time - $max_delay))"
        echo "Total time: $total_time" >> result.txt
        echo "Effective time: $effective_time" >> result.txt
    done
done
