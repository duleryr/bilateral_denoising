#!/bin/bash

for file in *; do
    sed -e 's/,/./g' "$file"
done
