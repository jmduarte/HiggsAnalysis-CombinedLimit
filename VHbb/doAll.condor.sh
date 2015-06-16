#!/bin/bash

if [ $# -ge 8  ]; then 
    cardDir=$1
    cmsStyle=$2
    commonMu=$3 #this parameter is ignored for tevatron style
    expected=$4
    tolerance=$5
    minuit2=$6
    maxSteps=$7
    strategy=$8
elif [ $# -ge 1 ]; then
    echo "Usage: ./doAll.condor.sh <cmsStyle> <commonMu> <expected> <tolerance> <minuit2>"
    exit
else
    cardDir=/uscms_data/d1/jstupak/fa3Combo/CMSSW_6_1_1/src/HiggsAnalysis/CombinedLimit/DR_p0plusp1_050915_correlatedBkg
    #1=True, 0=False
    cmsStyle=1
    commonMu=1 #this parameter is ignored for tevatron style
    expected=1
    tolerance=0.1
    minuit2=1
    maxSteps=20
    strategy=0
fi

execDir=$PWD

#################################################

if [ $expected == 1 ]; then scan="EXPECTED"; else scan="OBSERVED"; fi

echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
if [ $cmsStyle == 1 ]; then
    if [ $commonMu == 1 ]; then echo "RUNNING "${scan}" CMS-STYLE FA3 SCANS WITH A COMMON MU PARAMETER"
    else                        echo "RUNNING "${scan}" CMS-STYLE FA3 SCANS WITH SEPARATE MU PARAMETERS"
    fi
else
                                echo "RUNNING "${scan}" TEVATRON-STYLE FA3 SCANS"
fi

if [ $minuit2 == 1 ]; then echo "MINIMIZER: Minuit2"
else                       echo "MINIMIZER: Minuit"
fi

echo "TOLERANCE: "${tolerance}

echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
echo

#################################################

for card in `ls ${cardDir}/dataCard_*txt`; do
    ID=${card##*_}
    ID=${ID%%.*}
    
    if [ $cmsStyle == 1 ]; then ID=${ID}_CMS;
    elif [ $cmsStyle == 0 ]; then ID=${ID}_TEV;
    else exit
    fi
    
    if [ $commonMu == 1 ]; then ID=${ID}_common;
    elif [ $commonMu == 0 ]; then ID=${ID}_float;
    else exit
    fi

    if [ $expected == 1 ]; then ID=${ID}_expected;
    elif [ $expected == 0 ]; then ID=${ID}_observed;
    else exit
    fi
    
    if [ $minuit2 == 1 ]; then ID=${ID}_minuit2;
    elif [ $minuit2 == 0 ]; then ID=${ID}_minuit;
    else exit
    fi

    ID=${ID}_${tolerance/./p}_tries${maxSteps}_strategy${strategy}

    #--------------------------------------------------------

    command="cd ${cardDir}; eval \`scramv1 runtime -sh\`; "
    #command=${command}" cd ${execDir}; rm -rf ${ID}; mkdir ${ID}; cd ${ID}; "
    command=${command}" cd -; "
    command=${command}" cp -r "${cardDir}/templates_*" .; cp -r "${cardDir}/dataCard_*" .; text2workspace.py -m 125.6 $card -P HiggsAnalysis.CombinedLimit.HiggsJPC_combo:twoHypothesisHiggs --PO=muFloating -o ${ID}.text2workspace.root -v 7; combine -M MultiDimFit ${ID}.text2workspace.root "

    command=${command}" --setPhysicsModelParameters cww_zz=0.5,r_ww=1,r_box=1"
    
    #HACK
    #command=${command}",wh_medBoost_trend=0,wh_highBoost_trend=0,zh_medBoost_trend=0,zh_highBoost_trend=0"

    if [ $cmsStyle == 0 ]; then command=${command}",r=1,r_qq=1 "
    elif [ $commonMu == 1 ]; then   command=${command}",r_qq=1 "
    fi

    command=${command}" --freezeNuisances r_ww,cww_zz,r_box"
    if [ $cmsStyle == 0 ]; then command=${command}",r,r_qq"
    elif [ $commonMu == 1 ]; then command=${command}",r_qq"
    fi

    #HACK
    #command=${command}",wh_medBoost_trend,wh_highBoost_trend,zh_medBoost_trend,zh_highBoost_trend"

    command=${command}" --setPhysicsModelParameterRanges CMS_zz4l_fg4=0,1 --algo=grid --points 100 -m 125.6 --minimizerTolerance=${tolerance} --maxFailedSteps=${maxSteps} --minimizerStrategy=${strategy}"

    if [ $minuit2 == 0 ]; then command=${command}" --minimizerAlgo=Minuit "
    fi

    if [ $expected == 1 ]; then command=${command}" -n 1D_exp "
    else                        command=${command}" -n 1D_obs "
    fi

    command=${command}" -P CMS_zz4l_fg4 "

    if [ $expected == 1 ]; then command=${command}" -t -1 --expectSignal=1 "; fi

    command=${command}" -v 2; mv higgsCombine*root ${ID}.combine.root"

cat <<EOF >condor.job
universe = vanilla
Executable = ${ID}.sh
Should_Transfer_Files = YES
WhenToTransferOutput = ON_EXIT
Output = condor.${ID}.out
Error = condor.${ID}.err
Log = condor.${ID}.log
Notification = Never
Queue 1
EOF

cat <<EOF >${ID}.sh
#!/bin/bash -x
$command
EOF

    chmod +x $ID.sh
    sleep 1
    condor_submit condor.job

done