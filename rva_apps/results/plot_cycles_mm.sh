#!/bin/bash
rm results_normal_mm.txt
rm results_in_place_mm.txt
args="--dc=128:8:32 --ic=256:4:32 --l2=1024:4:32 pk"
args_pim="--extension=rim --dc=128:8:32 --ic=256:4:32 --l2=1024:4:32 pk"

for ((i = 2 ; i <= 100 ; i++)); do
    echo "In Place Matrix Multiply ${i}"
    spike ${args_pim} ../matrix_multiply_in_place ${i} > buff
    t_h=`cat buff | grep Hierarchy | cut -d":" -f2`
    t_pim=`cat buff | grep PIM | grep Cycles | cut -d":" -f2`
    t_inst=`cat buff | grep Instruction| cut -d":" -f2`
    cat buff| grep fault
    #echo "$t_h + $t_pim + $t_inst"
    echo "$t_h + $t_pim + $t_inst + 600"| bc >> results_in_place_mm.txt


    echo "Normal Matrix Multiply ${i}"
    spike $args ../matrix_multiply ${i} > buff
    t_h=`cat buff | grep Hierarchy | cut -d":" -f2`
    t_inst=`cat buff | grep Instruction| cut -d":" -f2`
    #echo "$t_h + $t_inst"
    cat buff| grep fault
    echo "$t_h + $t_inst"| bc >> results_normal_mm.txt
done

rm buff
