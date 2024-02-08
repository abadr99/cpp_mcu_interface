# !/bin/bash/
# This tests is called FROM MAIN DIR (SPECIALLY FOR CI SYSTEM)
hardware_tests_dir=tests/hardware
tests=$(ls $hardware_tests_dir)

for test in $tests; do
    echo "------- Compiling $test test"
    make compile-hardware-test test=$hardware_tests_dir/$test/*.cpp name=test
    if [ $? -gt 0 ]; then
        echo "[FAIL]: Compiling $test failed\n"
        exit 1
    fi
    echo "[DONE]: Compiling $test Successfully\n"
done