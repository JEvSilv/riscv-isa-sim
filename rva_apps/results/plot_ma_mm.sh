#!/bin/bash
rm results_in_place_mm_ma.out
rm results_normal_mm_ma.out

args="--dc=128:8:32 --ic=256:4:32 --l2=1024:4:32 pk"
args_pim="--extension=rim --dc=128:8:32 --ic=256:4:32 --l2=1024:4:32 pk"

for ((i = 2 ; i <= 100 ; i++)); do
    echo "In Place Matrix Multiply ${i}"
    spike ${args_pim} ../matrix_multiply_in_place ${i} > buff1
    cat buff1 | grep MA | cut -d":" -f2  >> results_in_place_mm_ma.out
 
    echo "Normal Matrix Multiply ${i}"
    spike $args ../matrix_multiply ${i} > buff1
    cat buff1 | grep MA | cut -d":" -f2 >> results_normal_mm_ma.out
done

rm buff1
