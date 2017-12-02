#!/bin/bash

for file in OFF_Files_Noised/*.off
do
    for nb_iter in 1 2 4 5
    do
        for neighboorhoodSize in 1 2 3
        do
            ./main "$file" "$nb_iter" "$neighboorhoodSize"
            echo "file : $file, nb_iter = $nb_iter, neighboorhoodSize = $neighboorhoodSize, done"
        done
    done
done
