#!/bin/bash

EXIT=0
main_CPP_test_directory=tests/integration

if [ -d "$main_CPP_test_directory" ]; then
  rm -rf "$main_CPP_test_directory"/summary
  test_files_dirs=$(ls "$main_CPP_test_directory")
else
  echo "Directory not found: $main_CPP_test_directory"
  exit 1 
fi

# Loop over the tests directories
for test_file_dir in $test_files_dirs
do
    if sh scripts/testing/run-regressions.sh -d $main_CPP_test_directory/$test_file_dir 
    then
        :   # NOP command
    else 
        EXIT=1 #Once we are get here then we have to exit with error
    fi
done

echo "Tests Summary:\n"
cat $main_CPP_test_directory/summary
rm -rf $main_CPP_test_directory/summary
exit $EXIT