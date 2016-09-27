#!/bin/bash

applyDoubleRatio=false
areChannelsSplit=true

scriptDir=$PWD
cd templates_062515_formFact # working directory

#ZHDoubleRatio=255.414 # 7TeV, to convert to ZZ 
#WHDoubleRatio=351.592 # 7TeV, to convert to ZZ 
ZHDoubleRatio=266.864 # 8TeV, to convert to ZZ                                                                                                                         
WHDoubleRatio=366.436 # 8TeV, to convert to ZZ 
#ZHDoubleRatio=1 # 8TeV, to convert to ZH                                                                                                                 
#WHDoubleRatio=1.373 # 8TeV, to convert to ZH

statThresh=15
statTotalThresh=7
if [ $# -ge 2  ]; then 
    statSignalThresh=$1
    ID=$2
elif [ $# -ge 1 ]; then
    echo "Usage: ./makeFA3Cards.sh <signal threshold> <template id>"
    exit
else
    statSignalThresh=2.5
    ID=
fi

p0WHmed=0.5276
p1WHmed=0.001136
p0WHhigh=1.051
p1WHhigh=-0.0001513
p0ZHmed=0.7768
p1ZHmed=0.0009735
p0ZHhigh=1.039
p1ZHhigh=-0.0001152

hVVCardDir=/uscms_data/d1/jstupak/fa3Combo/CMSSW_6_1_1/src/vhvv_combination/hVVCards

#####################################################################################

if [ $areChannelsSplit != true ]; then
    WHtemplates=`ls -d templates${ID}_WH*`
    ZHtemplates=`ls -d templates${ID}_ZH*`
fi

if [ $areChannelsSplit == true ]; then
    WHtemplates=`ls -d templates${ID}_[23]*`
    ZHtemplates=`ls -d templates${ID}_[01]*`
fi

if [ $applyDoubleRatio != true ]; then
    ZHDoubleRatio=1
    WHDoubleRatio=1
fi

templateOutDir=noDR_062515_sigThrsld$statSignalThresh
if [ ! -d "$templateOutDir" ]; then
	mkdir $templateOutDir
	cp -r templates_* $templateOutDir
fi
cd $templateOutDir

#####################################################################################

for dir in ${WHtemplates[@]}; do
    cd $dir

    #add stat shape nuissance parameters first

    python ${scriptDir}/addStatShapes.py $statThresh $statTotalThresh plots.root plots.root dataCard_combo.txt dataCard_combo.txt ${scriptDir}/plots2dWH.root $p0WHmed $p1WHmed $p0WHhigh $p1WHhigh $statSignalThresh
    python ${scriptDir}/addStatShapes.py $statThresh $statTotalThresh plots.root dummy.root dataCard_WhOnly.txt dataCard_WhOnly.txt ${scriptDir}/plots2dWH.root $p0WHmed $p1WHmed $p0WHhigh $p1WHhigh $statSignalThresh

    #---------------------------------------------------------------------------------

    #modify signal names in datacards
    
    sed -i 's/Wh_125p6_0P       /whsig             /g' dataCard_combo.txt
    sed -i 's/Wh_125p6_0M       /whsig_ALT         /g' dataCard_combo.txt
    sed -i 's/Zh_125p6_0P       /zhsig             /g' dataCard_combo.txt
    sed -i 's/Zh_125p6_0M       /zhsig_ALT         /g' dataCard_combo.txt
    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    sed -i 's/Wh_125p6_0P       /whsig             /g' dataCard_WhOnly.txt
    sed -i 's/Wh_125p6_0M       /whsig_ALT         /g' dataCard_WhOnly.txt
    sed -i 's/Zh_125p6_0P       /zhsig             /g' dataCard_WhOnly.txt
    sed -i 's/Zh_125p6_0M       /zhsig_ALT         /g' dataCard_WhOnly.txt

    #---------------------------------------------------------------------------------

    #scale ALT signals to fa3_ZZ in datacards

    if [ $applyDoubleRatio = true ]; then
	python ${scriptDir}/modifyDataCardForMu.py $WHDoubleRatio whsig_ALT dataCard_combo.txt dataCard_combo.txt
	python ${scriptDir}/modifyDataCardForMu.py $ZHDoubleRatio zhsig_ALT dataCard_combo.txt dataCard_combo.txt
        #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	python ${scriptDir}/modifyDataCardForMu.py $WHDoubleRatio whsig_ALT dataCard_WhOnly.txt dataCard_WhOnly.txt
    fi

    #---------------------------------------------------------------------------------

    #change signal and systematic names, and scale ALT signals to fa3_ZZ in ROOT file

    root -l -b <<EOF
        .L ${scriptDir}/convertRootFileWH.C++
        convertRootFileWH("Wh_125p6_0P","Wh_125p6_0M",${WHDoubleRatio},"whsig","whsig_ALT","plots.root")
        .q
EOF

    root -l -b <<EOF
        .L ${scriptDir}/convertRootFileWH.C++
        convertRootFileWH("Zh_125p6_0P","Zh_125p6_0M",${ZHDoubleRatio},"zhsig","zhsig_ALT","plots.root")
        .q
EOF

    python ${scriptDir}/decorrelateNuisances.py plots.root plots.root dataCard_combo.txt dataCard_combo.txt
    python ${scriptDir}/decorrelateNuisances.py plots.root dummy.root dataCard_WhOnly.txt dataCard_WhOnly.txt
    
    cd -
done

#####################################################################################

for dir in ${ZHtemplates[@]}; do
    cd $dir
    
    #add stat shape nuissance parameters first

    python ${scriptDir}/addStatShapes.py $statThresh $statTotalThresh plots.root plots.root dataCard.txt dataCard.txt ${scriptDir}/plots2dZH.root $p0ZHmed $p1ZHmed $p0ZHhigh $p1ZHhigh $statSignalThresh
    
    #---------------------------------------------------------------------------------

    #modify signal names in datacards

    sed -i 's/Zh_125p6_0P       /zhsig             /g' dataCard.txt
    sed -i 's/Zh_125p6_0M       /zhsig_ALT         /g' dataCard.txt

    #---------------------------------------------------------------------------------

    #scale ALT signals to fa3_ZZ in datacards

    python ${scriptDir}/modifyDataCardForMu.py $ZHDoubleRatio zhsig_ALT dataCard.txt dataCard.txt

    #---------------------------------------------------------------------------------

    #change signal and systematic names, and scale ALT signals to fa3_ZZ in ROOT file

    root -l -b <<EOF
        .L ${scriptDir}/convertRootFileZH.C++
        convertRootFileZH("Zh_125p6_0P","Zh_125p6_0M",${ZHDoubleRatio},"zhsig","zhsig_ALT","plots.root")
        .q   
EOF

	python ${scriptDir}/decorrelateNuisances.py plots.root plots.root dataCard.txt dataCard.txt

    cd -
done

#####################################################################################

# if the templates ARE NOT split into channels:
if [ $areChannelsSplit != true ]; then
	combineCards.py templates${ID}_WH/dataCard_WhOnly.txt > dataCard${ID}_Wh.txt
	combineCards.py templates${ID}_ZH/dataCard.txt > dataCard${ID}_Zh.txt
	combineCards.py templates${ID}_WH/dataCard_combo.txt templates${ID}_ZH/dataCard.txt > dataCard${ID}_Vh.txt

	combineCards.py templates${ID}_WH/dataCard_WhOnly.txt  $hVVCardDir/dataCard_WW.txt > dataCard${ID}_WWWh.txt
	combineCards.py templates${ID}_ZH/dataCard.txt         $hVVCardDir/dataCard_ZZ.txt > dataCard${ID}_ZZZh.txt
	combineCards.py templates${ID}_WH/dataCard_combo.txt  templates${ID}_ZH/dataCard.txt $hVVCardDir/dataCard_VV.txt > dataCard${ID}_VVVh.txt
fi

#if the templates ARE split into channels:
if [ $areChannelsSplit == true ]; then
	combineCards.py templates${ID}_[23]*/dataCard_WhOnly.txt > dataCard${ID}_Wh.txt
	combineCards.py templates${ID}_[01]*/dataCard.txt > dataCard${ID}_Zh.txt
	combineCards.py templates${ID}_[23]*/dataCard_combo.txt templates${ID}_[01]*/dataCard.txt > dataCard${ID}_Vh.txt

	combineCards.py templates${ID}_[23]*/dataCard_WhOnly.txt  $hVVCardDir/dataCard_WW.txt > dataCard${ID}_WWWh.txt
	combineCards.py templates${ID}_[01]*/dataCard.txt         $hVVCardDir/dataCard_ZZ.txt > dataCard${ID}_ZZZh.txt
	combineCards.py templates${ID}_[23]*/dataCard_combo.txt  templates${ID}_[01]*/dataCard.txt $hVVCardDir/dataCard_VV.txt > dataCard${ID}_VVVh.txt
fi

