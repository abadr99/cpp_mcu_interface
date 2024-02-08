# !/bin/bash/

benchmarks_tests_dir=tests/benchmarks
tests=$(ls $benchmarks_tests_dir)

for test in $tests; do
    echo "------- Removing binaries of $test test"
    rm -rf $benchmarks_tests_dir/$test/*.elf $benchmarks_tests_dir/$test/*.hex
    echo "[DONE]: Removing $test Successfully\n"
done