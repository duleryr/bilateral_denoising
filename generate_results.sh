#!/bin/bash

for nb_iter in 1 3 5
do
    for neighboorhoodSize in 1 3
    do
        echo "file : bone_gaussien.off, nb_iter = $nb_iter, neighboorhoodSize = $neighboorhoodSize"
        ./main "OFF_Files_Noised/bone_gaussien.off" "$nb_iter" "$neighboorhoodSize"
        echo "done"
    done
done
