#!/bin/bash

for file in *; do
    sed -i -e 's/\././g' "$file"
done
