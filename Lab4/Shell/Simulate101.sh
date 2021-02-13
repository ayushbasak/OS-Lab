#!/bin/bash
pathVariable=../Programs

# $1 $2 $3 $4 are Problem Size, Page Frame Size, Pafe Frame Count, Replacement Policy arguments respectively

case $1 in
	2000 | 3000 | 4000 | 5000 | 6000 | 7000 | 8000)
		;;
	*)
		echo "Invalid Problem Size! Must be [2000 | 3000 | 4000 | 5000 | 6000 | 7000 | 8000]"
		exit 1
		;;
esac
case $2 in
	16 | 32 | 64 | 128 | 256)
		;;
	*)
		echo "Invalid Page Frame Size! Must be [16 | 32 | 64 | 128 | 256]"
		exit 1
		;;
esac
case $3 in
	16 | 32 | 64 | 128 | 256)
		;;
	*)
		echo "Invalid Page Frame Count! Must be [16 | 32 | 64 | 128 | 256 | 512]"
		exit 1
		;;
esac
case $4 in
	LRU | NRU | FIFO | Opt)
		;;
	*)
		echo "Invalid Page Replacement Policy! Must be [LRU | NRU | FIFO | Opt]"
		exit 1
		;;
esac

DiskIO=`$pathVariable/./nameSorter $1 listaccess | $pathVariable/./pageRefGen $2 | $pathVariable/./$4 $3 | grep -e "Reads from" -e "Writes to" -h`
DiskRead=`echo $DiskIO | cut -d' ' -f 5`
DiskWrites=`echo $DiskIO | cut -d' ' -f 9`

let r=$DiskRead
let w=$DiskWrites
let DiskActivity=r+w
echo $DiskActivity

