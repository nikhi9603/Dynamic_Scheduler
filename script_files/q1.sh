#!/bin/bash

trace_files=("perl_trace.txt" "gcc_trace.txt")

scheduling_queue_sizes=(8 16 32 64 128 256)

bandwidth_list=(2 4 8)

for trace_file in "${trace_files[@]}"; do
    for N in "${bandwidth_list[@]}"; do
        for S in "${scheduling_queue_sizes[@]}"; do
            ./ooosim "$N" "$S" "$trace_file"
        done
    done
done