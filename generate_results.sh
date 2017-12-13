#!/bin/bash

for file in OFF_Files_Noised/*.off
do
    for nb_iter in 1 2 3 4 5
    do
        for neighboorhoodSize in 1 2
        do
            echo "file : $file, nb_iter = $nb_iter, neighboorhoodSize = $neighboorhoodSize"
            ./main "$file" "$nb_iter" "$neighboorhoodSize"
            echo "done"
        done
    done
done
