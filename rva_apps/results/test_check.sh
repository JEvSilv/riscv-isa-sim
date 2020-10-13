#!/bin/bash

args="--dc=128:8:32 --ic=256:4:32 --l2=1024:4:32 pk"
args_pim="--extension=rim --dc=128:8:32 --ic=256:4:32 --l2=1024:4:32 pk"

for ((i = 1 ; i <= 1500 ; i++)); do
    echo "In Place Checksum ${i}"
    spike $args_pim ../in_place_checksum ${i} > buff
    t_h=`cat buff | grep Hierarchy | cut -d":" -f2`
    t_pim=`cat buff | grep PIM | grep Cycles | cut -d":" -f2`
    t_inst=`cat buff | grep Instruction| cut -d":" -f2`
    echo "$t_h + $t_pim + $t_inst"
    echo "$t_h + $t_pim + $t_inst"| bc

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
