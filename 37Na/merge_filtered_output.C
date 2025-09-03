#!/bin/bash

# Directory containing your output ROOT files (adjust if needed)
OUTPUT_DIR="/mnt/analysis/e21062/tg/batch_analysis/analyzed"

# Output file name
MERGED_FILE="merged_decay_analysis_1_percent.root"

# Go to output directory
cd "$OUTPUT_DIR" || { echo "ERROR: Cannot cd to $OUTPUT_DIR"; exit 1; }

# Find all individual output files
# FILES=$(ls clover_analysis_run*.root 2>/dev/null)
FILES=$(ls decay_vs_radius_1_percent_run*.root 2>/dev/null)
if [ -z "$FILES" ]; then
  echo "No files found to merge."
  exit 1
fi

# Merge using hadd
echo "Merging files into $MERGED_FILE..."
hadd -f "$MERGED_FILE" $FILES

# Check result
if [ $? -eq 0 ]; then
  echo "✅ Merge successful: $MERGED_FILE"
else
  echo "❌ Merge failed."
fi
