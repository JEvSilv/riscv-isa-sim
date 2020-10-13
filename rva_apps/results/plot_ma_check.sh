#!/bin/bash

rm results_in_place_check_ma.out
rm results_normal_check_ma.out

args="--dc=128:8:32 --ic=256:4:32 --l2=1024:4:32 pk"
args_pim="--extension=rim --dc=128:8:32 --ic=256:4:32 --l2=1024:4:32 pk"

for ((i = 1 ; i <= 1500 ; i++)); do
    echo "In Place Checksum ${i}"
    spike $args_pim ../in_place_checksum ${i} > buff1
    cat buff1 | grep MA | cut -d":" -f2 >> results_in_place_check_ma.out

    echo "Normal Checksum ${i}"
    spike $args ../normal_checksum ${i} > buff1
    cat buff1 | grep MA | cut -d":" -f2 >> results_normal_check_ma.out
done

rm buff1
