# !/bin/bash/
# This tests is called FROM MAIN DIR (SPECIALLY FOR CI SYSTEM)
hardware_tests_dir=tests/hardware
tests=$(ls $hardware_tests_dir)

for test in $tests; do
    echo "------- Compiling $test test"
    make compile-hardware-test test=$hardware_tests_dir/$test/$test.cpp name=test
    echo "[DONE]: Compiling $test Successfully\n"
done