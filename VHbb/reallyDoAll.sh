#!/bin/bash

if [ $# -ge 1  ]; then
    cardDir=$1
else
    echo "Specify card dir"
    exit
fi

for i in 0 1
do
  for j in 0 1
  do

    if [ $i -eq 0 -a $j -eq 0 ]; then continue
    fi

    for k in 0 1
    do
      for l in 0.1 0.01 0.001
      do

	if [ $i -eq 0 ]; then
	    if (( $( echo "$l <= 0.01" | bc -l) )); then continue
	    fi
	fi

	for m in 0 1
	do
	  
	  if [ $i -eq 0 -a $m -eq 0 ]; then continue
	  fi

	  for n in 5 10
	  do

	    for o in 0 1 2
	    do
	  
	      /uscms_data/d1/jstupak/fa3Combo/CMSSW_6_1_1/src/HiggsAnalysis/CombinedLimit/VHbb/doAll.condor.sh $cardDir $i $j $k $l $m $n $o
	      sleep 2
	      
	      done
	  done
	done
      done
    done
  done
done