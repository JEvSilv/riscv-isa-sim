#!/bin/bash
rm results_normal_bit_ma.out
rm results_in_place_bit_ma.out

args="--dc=128:8:32 --ic=256:4:32 --l2=1024:4:32 pk"
args_pim="--extension=rim --dc=128:8:32 --ic=256:4:32 --l2=1024:4:32 pk"

for ((i = 1 ; i <= 1500 ; i++)); do
    echo "In Place Bitcount ${i}"
    spike $args_pim ../bitcount_in_place ${i} > buff1
    cat buff1 | grep MA | cut -d":" -f2 >> results_in_place_bit_ma.out

    echo "Normal Bitcount ${i}"
    spike $args ../bitcount ${i} > buff1
    cat buff1 | grep MA | cut -d":" -f2 >> results_normal_bit_ma.out
done

rm buff1
