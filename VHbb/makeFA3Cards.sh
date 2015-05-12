#!/bin/bash -x

applyDoubleRatio=true
areChannelsSplit=true

#ZHDoubleRatio=255.414 # 7TeV, to convert ZZ 
#WHDoubleRatio=351.592 # 7TeV, to convert ZZ 
#ZHDoubleRatio=266.864 # 8TeV, to convert ZZ                                                                                                                         
#WHDoubleRatio=366.436 # 8TeV, to convert ZZ 
ZHDoubleRatio=1 # 8TeV, to convert ZH                                                                                                                 
WHDoubleRatio=1.373 # 8TeV, to convert ZH

statThresh=15
statTotalThresh=7
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
    WHtemplates=`ls -d templates_WH*`
    ZHtemplates=`ls -d templates_ZH*`
fi

if [ $areChannelsSplit == true ]; then
    WHtemplates=`ls -d templates_[23]*`
    ZHtemplates=`ls -d templates_[01]*`
fi

if [ $applyDoubleRatio != true ]; then
    ZHDoubleRatio=1
    WHDoubleRatio=1
fi

#mkdir backup
#cp -r templates_* backup

#mkdir zhDR_p0plusp1_050915_uncorrelatedBkg
#cp -r templates_* zhDR_p0plusp1_050915_uncorrelatedBkg
#cd zhDR_p0plusp1_050915_uncorrelatedBkg
mkdir teest
cp -r templates_* teest
cd teest

#####################################################################################

for dir in ${WHtemplates[@]}; do
    cd $dir

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

    python ../../addStatShapes.py $statThresh $statTotalThresh plots.root plots.root dataCard_combo.txt dataCard_combo.txt ../../plots2dWH.root $p0WHmed $p1WHmed $p0WHhigh $p1WHhigh
    python ../../addStatShapes.py $statThresh $statTotalThresh plots.root dummy.root dataCard_WhOnly.txt dataCard_WhOnly.txt ../../plots2dWH.root $p0WHmed $p1WHmed $p0WHhigh $p1WHhigh

    cd -
done

#####################################################################################

for dir in ${ZHtemplates[@]}; do
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

    python ../../addStatShapes.py $statThresh $statTotalThresh plots.root plots.root dataCard.txt dataCard.txt ../../plots2dZH.root $p0ZHmed $p1ZHmed $p0ZHhigh $p1ZHhigh

    cd -
done

#####################################################################################

# if the templates ARE NOT split into channels:
if [ $areChannelsSplit != true ]; then
	combineCards.py templates_WH/dataCard_WhOnly.txt > dataCard_Wh.txt
	combineCards.py templates_ZH/dataCard.txt > dataCard_Zh.txt
	combineCards.py templates_WH/dataCard_combo.txt templates_ZH/dataCard.txt > dataCard_Vh.txt

	combineCards.py templates_WH/dataCard_WhOnly.txt  $hVVCardDir/dataCard_WW.txt > dataCard_WWWh.txt
	combineCards.py templates_ZH/dataCard.txt         $hVVCardDir/dataCard_ZZ.txt > dataCard_ZZZh.txt
	combineCards.py templates_WH/dataCard_combo.txt  templates_ZH/dataCard.txt $hVVCardDir/dataCard_VV.txt > dataCard_VVVh.txt
fi

#if the templates ARE split into channels:
if [ $areChannelsSplit == true ]; then
	combineCards.py templates_[23]*/dataCard_WhOnly.txt > dataCard_Wh.txt
	combineCards.py templates_[01]*/dataCard.txt > dataCard_Zh.txt
	combineCards.py templates_[23]*/dataCard_combo.txt templates_[01]*/dataCard.txt > dataCard_Vh.txt

	combineCards.py templates_[23]*/dataCard_WhOnly.txt  $hVVCardDir/dataCard_WW.txt > dataCard_WWWh.txt
	combineCards.py templates_[01]*/dataCard.txt         $hVVCardDir/dataCard_ZZ.txt > dataCard_ZZZh.txt
	combineCards.py templates_[23]*/dataCard_combo.txt  templates_[01]*/dataCard.txt $hVVCardDir/dataCard_VV.txt > dataCard_VVVh.txt
fi

