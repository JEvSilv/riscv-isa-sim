#!/bin/bash
rm results_in_place_check.txt
rm results_normal_check.txt

args="--dc=128:8:32 --ic=256:4:32 --l2=1024:4:32 pk"
args_pim="--extension=rim --dc=128:8:32 --ic=256:4:32 --l2=1024:4:32 pk"

for ((i = 1 ; i <= 1500 ; i++)); do
    echo "In Place Checksum ${i}"
    spike $args_pim ../in_place_checksum ${i} > buff
    t_h=`cat buff | grep Hierarchy | cut -d":" -f2`
    t_pim=`cat buff | grep PIM | grep Cycles | cut -d":" -f2`
    t_inst=`cat buff | grep Instruction| cut -d":" -f2`
    cat buff | grep fault
    #echo "$t_h + $t_pim + $t_inst"
    echo "$t_h + $t_pim + $t_inst"| bc >> results_in_place_check.txt

    spike $args ../normal_checksum ${i} > buff
    echo "Normal Checksum ${i}"
    t_h=`cat buff | grep Hierarchy | cut -d":" -f2`
    t_inst=`cat buff | grep Instruction| cut -d":" -f2`
    #echo "$t_h + $t_inst"
    echo "$t_h + $t_inst"| bc >> results_normal_check.txt
done

rm buff
