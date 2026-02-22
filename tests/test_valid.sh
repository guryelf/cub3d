#!/bin/bash

# Configuration
VALID_DIR="../assets/maps/valid"
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

# Check if executable exists
if [ ! -f "../cub3D" ]; then
    echo -e "${RED}Error: cub3D executable not found. Please run make.${NC}"
    exit 1
fi

echo "Starting Valid Map Tests with Input Simulation..."
echo "------------------------------------------------"

files=$(ls $VALID_DIR/*.cub | sort)

for file in $files; do
    echo "=================================================================="
    echo "Testing $file"
    echo "=================================================================="
    fname=$(basename "$file")
    
    # Run in the background so we can send keys
    (cd .. && LD_LIBRARY_PATH=/usr/lib valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./cub3D "assets/maps/valid/$fname" > /tmp/cub3d_test_out 2>&1) &
    PID=$!
    
    # Run input simulation in background while game is running
    (
        # Wait longer for Valgrind + MLX window initialization
        sleep 4.0
        
        if [ "$XDG_SESSION_TYPE" = "wayland" ]; then
            echo "Sending inputs (Wayland/Deep Exercise + ESC)..."
            if command -v ydotool >/dev/null; then
                # Repeat movement 5 times
                for i in {1..5}; do
                    for key in w s a d; do ydotool type "$key"; sleep 0.1; done
                done
                # Repeat rotation 5 times
                for i in {1..5}; do ydotool key 105:1 105:0; sleep 0.1; done # Left
                for i in {1..5}; do ydotool key 106:1 106:0; sleep 0.1; done # Right
                # ESC key
                ydotool key 1:1 1:0
            else
                for i in {1..5}; do
                    for key in w s a d; do wtype "$key"; sleep 0.1; done
                done
                for i in {1..5}; do wtype -k left; sleep 0.1; done
                for i in {1..5}; do wtype -k right; sleep 0.1; done
                wtype -k Escape
            fi
        else
            echo "Sending inputs (X11/Deep Exercise + ESC)..."
            for i in {1..5}; do xdotool key --delay 100 w s a d; done
            for i in {1..5}; do xdotool key --delay 100 Left; done
            for i in {1..5}; do xdotool key --delay 100 Right; done
            xdotool key Escape
        fi
    ) &
    INPUT_PID=$!
    
    # Wait for completion (No kill, rely on ESC key)
    wait $PID
    status=$?
    output=$(cat /tmp/cub3d_test_out)
    
    # status 124 is timeout (success for us)
    if [ $status -eq 124 ] || [ $status -eq 0 ]; then
        echo -e "${GREEN}COMPLETED (Successfully initialized and exercised)${NC}"
    else
        echo -e "${RED}FAILED (Exited with $status)${NC}"
    fi
    echo "$output"
    echo "------------------------------------------------------------------"
    echo ""
done

echo "---------------------------"
echo "Tests Completed."
rm -f /tmp/cub3d_test_out
