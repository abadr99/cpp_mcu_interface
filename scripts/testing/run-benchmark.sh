#!/bin/bash
# This script is called from main path
# bash run-benchmark path/to/benchmark

benchmark_path=$1
# make sure that optimised objects are used
make clean
make build-avr-opt

# compile passed benchmark
make compile-benchmark DIR=$benchmark_path INPUT_FILE=$benchmark_path/modules.in
avr-size --mcu=atmega32 -C $benchmark_path/benchmark.elf > $benchmark_path/result.temp
date +"%Y-%m-%d %H:%M:%S" >> $benchmark_path/results.bm
grep -E "Program|Data" $benchmark_path/result.temp | awk '{print $1": "$2, $3, $4, $5, $6, $7, $8}' >> $benchmark_path/results.bm
echo "================================================================================" >> $benchmark_path/results.bm
rm -rf $benchmark_path/result.temp
