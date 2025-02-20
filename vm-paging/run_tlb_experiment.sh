#!/bin/bash

# Ensure the script is executable: chmod +x run_tlb_experiment.sh
# Run: ./run_tlb_experiment.sh > tlb_results.csv

EXE="./tlb"         # Path to compiled tlb program
NUMTRIALS=10000      # Fixed number of trials
OUTFILE="tlb_results.csv"

# Check if tlb executable exists
if [[ ! -f "$EXE" ]]; then
    echo "Error: tlb program not found. Compile it first using: gcc -O2 -o tlb tlb.c"
    exit 1
fi

echo "num_pages,avg_time_ns" > $OUTFILE  # CSV header

NUMPAGES=1
while [[ $NUMPAGES -le 261888 ]]; do
    RESULT=$($EXE $NUMPAGES $NUMTRIALS | grep -v Ignore | awk '{print $2}')  # Extract time from output
    echo "$NUMPAGES,$RESULT"
    echo "$NUMPAGES,$RESULT" >> $OUTFILE
    NUMPAGES=$((NUMPAGES * 2))  # Double the number of pages
done
