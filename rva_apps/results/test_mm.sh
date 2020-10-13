#!/bin/bash

args="--dc=128:8:32 --ic=256:4:32 --l2=1024:4:32 pk"
args_pim="--extension=rim --dc=128:8:32 --ic=256:4:32 --l2=1024:4:32 pk"

for ((i = 2 ; i <= 100 ; i++)); do
    echo "In Place Matrix Multiply ${i}"
    spike ${args_pim} ../matrix_multiply_in_place ${i} > buff
    cat buff | grep MA | cut -d":" -f2
 
#    echo "Normal Matrix Multiply ${i}"
#    spike $args ../matrix_multiply ${i} > buff
#    cat buff | grep MA | cut -d":" -f2 >> results_normal_mm_ma.out
done

#for ((i = 1 ; i <= 1500 ; i++)); do
#    echo "In Place Checksum ${i}"
#    spike $args_pim ../in_place_checksum ${i} > buff
#    cat buff | grep MA | cut -d":" -f2 >> results_in_place_check_ma.out

#    echo "Normal Checksum ${i}"
#    spike $args ../normal_checksum ${i} > buff
#    cat buff | grep MA | cut -d":" -f2 >> results_normal_check_ma.out

#    echo "In Place Bitcount ${i}"
#    spike $args_pim ../bitcount_in_place ${i} > buff
#    cat buff | grep MA | cut -d":" -f2 >> results_in_place_bit_ma.out

#    echo "Normal Bitcount ${i}"
#    spike $args ../bitcount ${i} > buff
#    cat buff | grep MA | cut -d":" -f2 >> results_normal_bit_ma.out
#done

rm buff
