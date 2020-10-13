#!/bin/bash
echo "Checksum Results"> check_results.csv
echo "---------------------" >> check_results.csv

for ((i = 1 ; i <= 1500 ; i++)); do
    `spike pk ./normal_checksum ${i} > buff 2>&1`
    echo "Normal Checksum ${i}"
    echo "Normal Checksum ${i}" >> check_results.csv
    cat buff >> check_results.csv
    echo "----------------------" >> check_results.csv
done

echo "#####################" >> check_results.csv
   
for ((i = 1 ; i <= 1500 ; i++)); do
    `spike --extension=rim pk in_place_checksum ${i} > buff 2>&1`
    echo "In Place Checksum ${i}"
    echo "In Place Checksum ${i}" >> check_results.csv
    cat buff >> check_results.csv
    echo "-----------------------" >> check_results.csv

done

rm buff
