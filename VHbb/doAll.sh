#!/bin/bash

#1=True, 0=False
cmsStyle=1
commonMu=1   #this parameter is ignored for tevatron style

expected=0

tolerance=0.01

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
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
echo

#################################################

for card in `ls dataCard_*txt`; do
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

    command="mkdir $ID; text2workspace.py -m 125.6 $card -P HiggsAnalysis.CombinedLimit.HiggsJPC_combo:twoHypothesisHiggs --PO=muFloating -o ${ID}.root -v 7; cd $ID; combine -M MultiDimFit ../${ID}.root "

    command=${command}" --setPhysicsModelParameters cww_zz=0.5,r_ww=1"
    
    if [ $cmsStyle == 0 ]; then command=${command}",r=1,r_qq=1,r_box=1 "
    elif [ $commonMu == 1 ]; then   command=${command}",r_qq=1,r_box=1 "
    fi

    command=${command}" --freezeNuisances r_ww,cww_zz"
    if [ $cmsStyle == 0 ]; then command=${command}",r,r_qq,r_box "
    elif [ $commonMu == 1 ]; then command=${command}",r_qq,r_box "
    fi
    
    command=${command}" --setPhysicsModelParameterRanges CMS_zz4l_fg4=0,1 --algo=grid --points 100 --minimizerTolerance "${tolerance}" --minimizerStrategy 0 -m 125.6 "

    if [ $expected == 1 ]; then command=${command}" -n 1D_exp "
    else                        command=${command}" -n 1D_obs "
    fi

    command=${command}" -P CMS_zz4l_fg4 "

    if [ $expected == 1 ]; then command=${command}" -t -1 --expectSignal=1 "; fi

    command=${command}" -v 7 "

    echo $command
    nohup sh -c "echo $command; eval $command" >& $ID.log &
    echo
    
done