#!/bin/bash

# Usage: ./compare_all_datasets_master.sh <folder_containing_datasets>

FOLDER="$1"
M_PARAM="-M-1500"

K_START=2700000
K_END=3100000
K_STEP=100000

#K_START=130000
#K_END=180000
#K_STEP=10000

EXEC_ORIG="./kingfisher_original"
EXEC_GEM="./kingfisher_gemini"

# Output master file
MASTER_FILE="compare_40ints.csv"
echo "dataset,k,binary_exec_time,itemset_exec_time" > "$MASTER_FILE"

# Loop through all .dat files in the folder
for DATASET in "$FOLDER"/*.dat; do
    BASE=$(basename "$DATASET" .dat)
    echo "Running comparisons on $DATASET..."

    for ((k=$K_START; k<=$K_END; k+=$K_STEP)); do
        echo "  k=$k..."

        # Initialize sum of times for averaging
        SUM_ORIG=0
        SUM_GEM=0

        # Run original (binary) 3 times
        for i in {1..3}; do
            OUTPUT_ORIG=$($EXEC_ORIG -i "$DATASET" -k$k $M_PARAM)
            TIME_ORIG=$(echo "$OUTPUT_ORIG" | grep "Total execution time" | sed -E 's/.*= \((.*) s\).*/\1/')
            if [[ -z "$TIME_ORIG" ]]; then
                TIME_ORIG="MISSING"
            fi
            # If time is valid, add it to the sum
            if [[ "$TIME_ORIG" != "MISSING" ]]; then
                SUM_ORIG=$(echo "$SUM_ORIG + $TIME_ORIG" | bc)
            fi
        done

        # Run gemini (itemset) 3 times
        for i in {1..3}; do
            OUTPUT_GEM=$($EXEC_GEM -i "$DATASET" -k$k $M_PARAM)
            TIME_GEM=$(echo "$OUTPUT_GEM" | grep "Total execution time" | sed -E 's/.*= \((.*) s\).*/\1/')
            if [[ -z "$TIME_GEM" ]]; then
                TIME_GEM="MISSING"
            fi
            # If time is valid, add it to the sum
            if [[ "$TIME_GEM" != "MISSING" ]]; then
                SUM_GEM=$(echo "$SUM_GEM + $TIME_GEM" | bc)
            fi
        done

        # Calculate the average time for both binary and itemset
        if [[ "$TIME_ORIG" != "MISSING" ]]; then
            AVG_ORIG=$(echo "$SUM_ORIG / 3" | bc -l)
        else
            AVG_ORIG="MISSING"
        fi

        if [[ "$TIME_GEM" != "MISSING" ]]; then
            AVG_GEM=$(echo "$SUM_GEM / 3" | bc -l)
        else
            AVG_GEM="MISSING"
        fi

        # Append result to master CSV
        echo "$BASE,$k,$AVG_ORIG,$AVG_GEM" >> "$MASTER_FILE"
    done

    echo "✅ Done with $BASE"
done

echo "🎉 All datasets in '$FOLDER' processed. Master CSV: $MASTER_FILE"
