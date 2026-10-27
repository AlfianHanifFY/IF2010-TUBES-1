#!/bin/bash

# Output file
OUTPUT_FILE="all_headers.txt"

# Clear previous content
> "$OUTPUT_FILE"

# Find all .hpp files under src/lib and generate #include lines
find ./src/lib -type f -name "*.hpp" | while read -r filepath; do
    # Remove the "./src/lib/" prefix
    relative_path="${filepath#./src/lib/}"
    echo "#include \"$relative_path\"" >> "$OUTPUT_FILE"
done

echo "Header list saved to $OUTPUT_FILE"
