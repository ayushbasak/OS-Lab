#!/bin/bash 
chmod u+x simulate101.sh

problem_size=('2000' '3000' '4000' '5000' '6000' '7000' '8000')
frame_size=('16' '32' '64' '128' '256')
frame_count=('16' '32' '64' '128' '256' '512')
policy=('FIFO' 'NRU' 'LRU' 'Opt')

if [ $1 == "ALL" ]
then
    for i in "${problem_size[@]}"
	do
	bash simulate101.sh $i $2 $3 $4
	done

elif [ $2 == "ALL" ]
then
    for	i in "${frame_size[@]}"
	do
        bash simulate101.sh $1 $i $3 $4
	done

elif [ $3 == "ALL" ]
then
    for i in "${frame_count[@]}"
	do
        bash simulate101.sh $1 $2 $i $4
	done

elif [ $4 == "ALL" ]
then
    for i in "${policy[@]}"
	do
        bash simulate101.sh $1 $2 $3 $i
	done

else
    bash simulate101.sh $1 $2 $3 $4
fi
