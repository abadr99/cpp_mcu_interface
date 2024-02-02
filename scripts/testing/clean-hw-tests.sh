# !/bin/bash/
# This tests is called FROM MAIN DIR (SPECIALLY FOR CI SYSTEM)
hardware_tests_dir=tests/hardware
tests=$(ls $hardware_tests_dir)

for test in $tests; do
    echo "------- Removing binaries of $test test"
    rm -rf $hardware_tests_dir/$test/*.elf $hardware_tests_dir/$test/*.hex
    echo "[DONE]: Removing $test Successfully\n"
done