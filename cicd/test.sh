#!/bin/bash
set -e

echo "Starting build process..."
sudo make
sudo make install
echo "Build completed successfully"
echo "1 22 4444" | ./programm > output.txt
expected="4444"
if ! grep -q "$expected" output.txt; then
	echo "Test 1 failed"
	exit 1
fi

echo "1" | ./programm > output.txt
if [ -s output.txt ]; then
	echo "Test 2 failed"
	exit 1
fi



echo "111 222 333" | ./programm > output.txt
if [ -s output.txt ]; then
	echo "Test 4 failed"
	exit 1
fi
rm output.txt
echo "all tests complete"
