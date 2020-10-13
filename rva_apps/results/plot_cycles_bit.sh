#!/bin/bash
rm results_in_place_bit.txt 
rm results_normal_bit.txt

args="--dc=128:8:32 --ic=256:4:32 --l2=1024:4:32 pk"
args_pim="--extension=rim --dc=128:8:32 --ic=256:4:32 --l2=1024:4:32 pk"

for ((i = 1 ; i <= 1500 ; i++)); do
    echo "In Place Bitcount ${i}"
    spike $args_pim ../bitcount_in_place ${i} > buff
    t_h=`cat buff | grep Hierarchy | cut -d":" -f2`
    t_pim=`cat buff | grep PIM | grep Cycles | cut -d":" -f2`
    t_inst=`cat buff | grep Instruction| cut -d":" -f2`
    #echo "$t_h + $t_pim + $t_inst"
    cat buff| grep fault
    echo "$t_h + $t_pim + $t_inst + 200"| bc >> results_in_place_bit.txt

    spike $args ../bitcount ${i} > buff
    echo "Normal Bitcount ${i}"
    t_h=`cat buff | grep Hierarchy | cut -d":" -f2`
    t_inst=`cat buff | grep Instruction| cut -d":" -f2`
    #echo "$t_h + $t_inst"
    cat buff| grep fault
    echo "$t_h + $t_inst"| bc >> results_normal_bit.txt
done

rm buff
