#!/bin/bash
echo "sep=," > results_nc.csv
echo "#RESULTS NC" >> results_nc.csv

echo "sep=," > results_ic.csv
echo "#RESULTS IC" >> results_ic.csv

echo "sep=," > results_nm.csv
echo "#RESULTS NM" >> results_nm.csv

echo "sep=," > results_im.csv
echo "#RESULTS IM" >> results_im.csv

echo "sep=," > results_nb.csv
echo "#RESULTS NB" >> results_nb.csv

echo "sep=," > results_ib.csv
echo "#RESULTS IB" >> results_ib.csv

for ((i = 2 ; i <= 100 ; i++)); do
    echo "In Place Matrix Multiply ${i}"
    spike --extension=rim pk matrix_multiply_in_place ${i} > buff
    cat buff | grep user >> results_im.csv
    cat buff | grep MA >> results_im.csv

    spike pk matrix_multiply ${i} > buff
    echo "Normal Matrix Multiply ${i}"
    cat buff | grep user >> results_nm.csv
    cat buff | grep MA >> results_nm.csv     
done

for ((i = 1 ; i <= 1500 ; i++)); do
    echo "In Place Checksum ${i}"
    spike --extension=rim pk in_place_checksum ${i} > buff
    cat buff | grep user >> results_ic.csv
    cat buff | grep MA >> results_ic.csv

    spike pk normal_checksum ${i} > buff
    echo "Normal Checksum ${i}"
    cat buff | grep user >> results_nc.csv
    cat buff | grep MA >> results_nc.csv     

    echo "In Place Bitcount ${i}"
    spike --extension=rim pk bitcount_in_place ${i} > buff
    cat buff | grep user >> results_ib.csv
    cat buff | grep MA >> results_ib.csv

    spike pk bitcount ${i} > buff
    echo "Normal Bitcount ${i}"
    cat buff | grep user >> results_nb.csv
    cat buff | grep MA >> results_nb.csv     
done

rm buff
