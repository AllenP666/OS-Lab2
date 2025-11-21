#!/bin/bash

echo "Updating reposistory..."
git pull || { echo "Git pull failed"; exit 1; }

echo "Ensuring build directory..."
[ -d build ] || mkdir build
cd build

echo "Running CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Debug || { echo "CMake configuration failed"; exit 1; }

echo "Building project..."
cmake --build . || { echo "Build failed"; exit 1; }

echo ""
echo "Build succeeded. Running test utility..."
./test_utility/test_utility || { echo "Test utility failed!"; exit 1; }

echo "Test utility finished successfully."