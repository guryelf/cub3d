#!/bin/bash

# Configuration
EXE="../cub3D"
INVALID_DIR="../assets/maps/invalid"
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

# Check if executable exists
if [ ! -f "$EXE" ]; then
    echo -e "${RED}Error: cub3D executable not found. Please run make.${NC}"
    exit 1
fi

echo "Starting Invalid Map Tests..."
echo "---------------------------"

# List of files and expected substrings (or just run all in order)
files=$(ls $INVALID_DIR/*.cub | sort)

for file in $files; do
    echo "=================================================================="
    echo "Testing $file"
    echo "=================================================================="
    fname=$(basename "$file")
    output=$(cd .. && LD_LIBRARY_PATH=/usr/lib valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./cub3D "assets/maps/invalid/$fname" 2>&1)
    status=$?
    
    # We expect an error, so if exit status is 0, it's a failure
    if [ $status -eq 0 ]; then
        echo -e "${RED}FAILED (Exited with 0)${NC}"
    else
        echo -e "${GREEN}COMPLETED (Exited with $status)${NC}"
    fi
    echo "$output"
    echo "------------------------------------------------------------------"
    echo ""
done

echo "---------------------------"
echo "Tests Completed."
