#!/bin/bash

file="$1"
sed -i -e 's/\./,/g' "$file"
concat="_meshlab.off"
filename=$(echo $file | cut -f 1 -d '.')
mv "$file" "$filename$concat"
