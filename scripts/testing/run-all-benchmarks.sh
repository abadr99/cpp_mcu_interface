#!/bin/bash
# This script is called from main path
# bash run-benchmark 

benchmark_path=tests/benchmarks/
benchmarks=$(ls $benchmark_path)

for bm in $benchmarks; do
    sh scripts/testing/run-benchmark.sh $benchmark_path/$bm
done