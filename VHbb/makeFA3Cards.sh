#!/bin/bash -x

applyDoubleRatio=true

#ZHDoubleRatio=255.414 # 7TeV
#WHDoubleRatio=351.592 # 7TeV
ZHDoubleRatio=266.864 # 8TeV                                                                                                                         
WHDoubleRatio=366.436 # 8TeV

statThresh=15
statTotalThresh=7

hVVCardDir=/uscms_data/d1/jstupak/fa3Combo/CMSSW_6_1_1/src/vhvv_combination/hVVCards

#####################################################################################

if [ $applyDoubleRatio != true ]; then
    ZHDoubleRatio=1
    WHDoubleRatio=1
fi

#mkdir backup
#cp -r templates_* backup

mkdir DR_042315
cp -r templates_* DR_042315
cd DR_042315

#####################################################################################

for dir in `ls -d templates_WH*`; do
#for dir in `ls -d templates_[23]*`; do
    cd $dir

    #modify signal names in datacards
    
    sed -i 's/Wh_125p6_0P       /whsig             /g' dataCard_combo.txt
    sed -i 's/Wh_125p6_0M       /whsig_ALT         /g' dataCard_combo.txt
    sed -i 's/Zh_125p6_0P       /zhsig             /g' dataCard_combo.txt
    sed -i 's/Zh_125p6_0M       /zhsig_ALT         /g' dataCard_combo.txt
    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    sed -i 's/Wh_125p6_0P       /whsig             /g' dataCard_WhOnly.txt
    sed -i 's/Wh_125p6_0M       /whsig_ALT         /g' dataCard_WhOnly.txt

    #---------------------------------------------------------------------------------

    #scale ALT signals to fa3_ZZ in datacards

    if [ $applyDoubleRatio = true ]; then
	python ../../modifyDataCardForMu.py $WHDoubleRatio whsig_ALT dataCard_combo.txt dataCard_combo.txt
	python ../../modifyDataCardForMu.py $ZHDoubleRatio zhsig_ALT dataCard_combo.txt dataCard_combo.txt
        #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	python ../../modifyDataCardForMu.py $WHDoubleRatio whsig_ALT dataCard_WhOnly.txt dataCard_WhOnly.txt
    fi

    #---------------------------------------------------------------------------------

    #change signal and systematic names, and scale ALT signals to fa3_ZZ in ROOT file

    root -l -b <<EOF
        .L ../../convertRootFileWH.C++
        convertRootFileWH("Wh_125p6_0P","Wh_125p6_0M",${WHDoubleRatio},"whsig","whsig_ALT","plots.root")
        .q
EOF

    root -l -b <<EOF
        .L ../../convertRootFileWH.C++
        convertRootFileWH("Zh_125p6_0P","Zh_125p6_0M",${ZHDoubleRatio},"zhsig","zhsig_ALT","plots.root")
        .q
EOF
    
    #---------------------------------------------------------------------------------

    #add stat shape nuissance parameters

    python ../../addStatShapes.py $statThresh $statTotalThresh plots.root plots.root dataCard_combo.txt dataCard_combo.txt
    python ../../addStatShapes.py $statThresh $statTotalThresh plots.root dummy.root dataCard_WhOnly.txt dataCard_WhOnly.txt

    cd -
done

#####################################################################################

for dir in `ls templates_ZH* -d`; do
#for dir in `ls templates_[01]* -d`; do
    cd $dir

    #modify signal names in datacards

    sed -i 's/Zh_125p6_0P       /zhsig             /g' dataCard.txt
    sed -i 's/Zh_125p6_0M       /zhsig_ALT         /g' dataCard.txt

    #---------------------------------------------------------------------------------

    #scale ALT signals to fa3_ZZ in datacards

    python ../../modifyDataCardForMu.py $ZHDoubleRatio zhsig_ALT dataCard.txt dataCard.txt

    #---------------------------------------------------------------------------------

    #change signal and systematic names, and scale ALT signals to fa3_ZZ in ROOT file

    root -l -b <<EOF
        .L ../../convertRootFileZH.C++
        convertRootFileZH("Zh_125p6_0P","Zh_125p6_0M",${ZHDoubleRatio},"zhsig","zhsig_ALT","plots.root")
        .q   
EOF

    #---------------------------------------------------------------------------------

    #add stat shape nuissance parameters

    python ../../addStatShapes.py $statThresh $statTotalThresh plots.root plots.root dataCard.txt dataCard.txt

    cd -
done

#####################################################################################

combineCards.py templates_WH/dataCard_WhOnly.txt > dataCard_Wh.txt
combineCards.py templates_ZH/dataCard.txt > dataCard_Zh.txt
combineCards.py templates_WH/dataCard_combo.txt templates_ZH/dataCard.txt > dataCard_Vh.txt

combineCards.py templates_WH/dataCard_WhOnly.txt  $hVVCardDir/dataCard_WW.txt > dataCard_WWWh.txt
combineCards.py templates_ZH/dataCard.txt         $hVVCardDir/dataCard_ZZ.txt > dataCard_ZZZh.txt
combineCards.py templates_WH/dataCard_combo.txt  templates_ZH/dataCard.txt $hVVCardDir/dataCard_VV.txt > dataCard_VVVh.txt


# combineCards.py templates_[23]*/dataCard_WhOnly.txt > dataCard_Wh.txt
# combineCards.py templates_[01]*/dataCard.txt > dataCard_Zh.txt
# combineCards.py templates_[23]*/dataCard_combo.txt templates_[01]*/dataCard.txt > dataCard_Vh.txt
# 
# combineCards.py templates_[23]*/dataCard_WhOnly.txt  $hVVCardDir/dataCard_WW.txt > dataCard_WWWh.txt
# combineCards.py templates_[01]*/dataCard.txt         $hVVCardDir/dataCard_ZZ.txt > dataCard_ZZZh.txt
# combineCards.py templates_[23]*/dataCard_combo.txt  templates_[01]*/dataCard.txt $hVVCardDir/dataCard_VV.txt > dataCard_VVVh.txt

