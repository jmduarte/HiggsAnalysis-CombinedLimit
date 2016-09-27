#!/usr/bin/env python

'''
Re-created from:
'''
'''
Add statistical shape errors (aka Barlow Beeston) to a shape .root file

Author: Evan K. Friis, UW Madison
'''
from utils import printTable
from numpy import linspace
import fnmatch
import logging
import ROOT
import sys
import os

none = "-"
one = "1"

log = logging.getLogger('shapes')
logS = logging.getLogger('stat_shapes')
logT = logging.getLogger('trend_shapes')

def readOldDataCard(filename):
    f = open(filename, 'rU')
    lines = f.readlines()
    f.close()
    data = []
    bin = []
    process = []
    for line in lines:
    	if line.startswith("----"): data.append(['break'])
    	elif (line.startswith("Observation") or line.startswith("shapes")): data.append([line.strip().split()[0],'','','']+line.strip().split()[1:])
    	elif (line.startswith("bin") or line.startswith("process") or line.startswith("rate")): 
    		data.append([line.strip().split()[0],'']+line.strip().split()[1:])
    		if line.startswith("bin"): bin=line.strip().split()
    		if line.startswith("process"): process.append(line.strip().split())
    		#if (line.startswith("process") and not line.strip().split()[1].startswith("-6") and not line.strip().split()[1].startswith("-5") and not line.strip().split()[1].startswith("-4") and not line.strip().split()[1].startswith("-3") and not line.strip().split()[1].startswith("-2") and not line.strip().split()[1].startswith("-1") and not line.strip().split()[1].startswith("0")): process=line.strip().split()
    	elif line.startswith("stat_") or 'ss_bin' in line: continue
    	else: data.append(line.strip().split())
    return data, bin, process

def walk_and_copy(inputdir, input2Ddir, outputdir, threshold, thresholdBG, thresholdSignal, binList, processLists, p0m, p1m, p0h, p1h):
    ''' Recursive function which copies from inputdir to outputdir '''
    dataStat = []
    dataTrend= ['dummy']
    allProcesses = processLists[0][1:]
    backgProcesses = processLists[0][processLists[1].index('0')+1:]
    #print allProcesses
    #print backgProcesses
    for key in inputdir.GetListOfKeys():
        # Keep track of stuff we find in this directory
        directories = []
        histos = []
        name = key.GetName()
        classname = key.GetClassName()
        if classname.startswith('TDirectory'):
            directories.append(name)
        elif isinstance(inputdir.Get(name), ROOT.TH1):
            histos.append(name)
        # Copy all histograms from input -> output directory
        for histo in histos:
            th1 = inputdir.Get(histo)
            th1totBG = inputdir.Get(histo[:histo.find("__")+2]+'totalBackground')
            if 'Vtype2' in histo[:histo.find("__")+2] or 'Vtype3' in histo[:histo.find("__")+2]:
            	th10P = inputdir.Get(histo[:histo.find("__")+2]+'Wh_125p6_0P')
            	th10M = inputdir.Get(histo[:histo.find("__")+2]+'Wh_125p6_0M')
            if 'Vtype0' in histo[:histo.find("__")+2] or 'Vtype1' in histo[:histo.find("__")+2]:
            	th10P = inputdir.Get(histo[:histo.find("__")+2]+'Zh_125p6_0P')
            	th10M = inputdir.Get(histo[:histo.find("__")+2]+'Zh_125p6_0M')
            outputdir.cd()
            th1.Write()
            
            #do_shapes = histo.endswith("0P") or histo.endswith("0M") or histo.endswith("W_light") or histo.endswith("W_b") or histo.endswith("W_bb") or histo.endswith("Z_light") or histo.endswith("Z_b") or histo.endswith("Z_bb") or histo.endswith("ttbar") or histo.endswith("singleTop") or histo.endswith("VZ") or histo.endswith("VV")
            do_StatShapes = histo[histo.find("__")+2:] in allProcesses
            if do_StatShapes:
                # check all bins to see if they need to be shape-errored
                logS.info("Building stat shapes for %s", histo)
                one = "1"
                for ibin in range(1, th1.GetNbinsX()+1):
                    if th1.GetBinContent(ibin): 
                        error = th1.GetBinError(ibin)
                        val = th1.GetBinContent(ibin)
                        valtotBG = th1totBG.GetBinContent(ibin)
                        val0P = th10P.GetBinContent(ibin)
                        val0M = th10M.GetBinContent(ibin)
                        checkTotBG = False
                        checkSignal0P = val0P/valtotBG > thresholdSignal/100
                        checkSignal0M = val0M/valtotBG > thresholdSignal/100
                        if valtotBG == 0: 
                        	checkTotBG = True
                        	print "WARNING! EMPTY BIN IN THE TOTAL BACKGROUND!!!"
                        if valtotBG != 0: checkTotBG = error/valtotBG > thresholdBG/100
                        # Check if we are above threshold
                        if (error/val > threshold/100 and checkTotBG and (checkSignal0P or checkSignal0M)):
                            vtype = histo[histo.find("Vtype"):histo.find("Vtype")+6]
                            boost = histo[histo.find("Vtype")+7:histo.find("__")]
                            process0 = histo[histo.find("__")+2:]
                            process = process0
                            if process0.endswith("_0P"): process = "0P"
                            if process0.endswith("_0M"): process = "0M"
                            err_up = th1.Clone(
                                th1.GetName() + '_' + vtype + '_' + boost + '_' + process + "_ss_bin_%iUp" % ibin)
                            err_down = th1.Clone(
                                th1.GetName() + '_' + vtype + '_' + boost + '_' + process + "_ss_bin_%iDown" % ibin)
                            err_up.SetBinContent(ibin, val + error)
                            err_down.SetBinContent(ibin, val - error)
                            liste = [vtype + '_' + boost +  '_' + process + "_ss_bin_%i" % ibin,'shape']
                            for i in range(len(binList)-1):
                            	if ((vtype+'_'+boost==binList[i+1]) and (process0==allProcesses[i])): liste.append(one)
                            	else: liste.append(none)
                            dataStat.append(liste)
                            outputdir.cd()
                            err_up.Write()
                            err_down.Write()
                            logS.info("==> built shape for %s bin %i", histo, ibin)
            do_TrendShapes = histo[histo.find("__")+2:] in allProcesses
            if do_TrendShapes:
                logT.info("Building trend shapes for %s", histo)
                one = "2"
                isCorrelatedBkg = 1
                if 'med' in histo: 
                	p0 = p0m
                	p1 = p1m
                if 'high' in histo: 
                	p0 = p0h
                	p1 = p1h
                vtype = histo[histo.find("Vtype"):histo.find("Vtype")+6]
                if '0' in vtype or '1' in vtype: channel = 'zh'
                if '2' in vtype or '3' in vtype: channel = 'wh'
                boost = histo[histo.find("Vtype")+7:histo.find("__")]
                process = '_'+histo[histo.find("__")+2:]
                if isCorrelatedBkg: process=''
                # Get mVh values from 2D templates before unrolling 
                ###### -- NEEDS TO BE UPDATED IF BINNING CHANGES -- ############
                th2d = input2Ddir.Get(histo[:histo.find("__")+2]+'Data')
                nxbins = th2d.GetXaxis().GetNbins()
                err_up = th1.Clone(th1.GetName()+'_'+channel+'_'+boost+process+'_trendUp')
                err_down = th1.Clone(th1.GetName()+'_'+channel+'_'+boost+process+'_trendDown')
                for ibin in range(1, th1.GetNbinsX()+1):
                	if ibin%nxbins: mVh = th2d.GetBinCenter(ibin%nxbins)
                	if not ibin%nxbins: mVh = th2d.GetBinCenter(nxbins)
                	val = th1.GetBinContent(ibin)
                	err_up.SetBinContent(ibin, max(0,val*(p0+p1*mVh)))
                	err_down.SetBinContent(ibin, max(0,val*(2.-p0-p1*mVh)))
                	#err_up.SetBinContent(ibin, max(0,val*(1.0+p1*mVh)))
                	#err_down.SetBinContent(ibin, max(0,val*(1.0-p1*mVh)))
                	#err_up.SetBinContent(ibin, max(0,val*(1.0+p1*mVh/p0)))
                	#err_down.SetBinContent(ibin, max(0,val*(1.0-p1*mVh/p0)))
                if histo[histo.find("__")+2:] in backgProcesses:
                	liste = [channel+'_'+boost+process+'_trend','shape']
                	for i in range(len(binList)-1):
                		if not isCorrelatedBkg:
                			if boost in binList[i+1] and process[1:]==allProcesses[i]: liste.append(one)
                			else: liste.append(none)
                		if isCorrelatedBkg:
                			if boost in binList[i+1] and allProcesses[i] in backgProcesses: liste.append(one)
                			else: liste.append(none)
                	if liste not in dataTrend: dataTrend.append(liste)
                outputdir.cd()
                err_up.Write()
                err_down.Write()
                logT.info("==> built trend shape for %s", histo)

        # Now copy and recurse into subdirectories
        for subdir in directories:
            output_subdir = outputdir.mkdir(subdir)
            # Recurse
            walk_and_copy(
                inputdir.Get(subdir), input2Ddir, output_subdir, 
                threshold, thresholdBG, thresholdSignal, binList, processLists, p0m, p1m, p0h, p1h)
    return dataStat, dataTrend[1:]

def main(inputRfilename, input2dRfilename, outputRfilename, inputDCfilename, outputDCfilename, threshold, thresholdBG, thresholdSignal, p0m, p1m, p0h, p1h):
    input = ROOT.TFile(inputRfilename, 'READ')
    input2d = ROOT.TFile(input2dRfilename, 'READ')
    output = ROOT.TFile(outputRfilename, 'RECREATE')
    data = []
    olddata, binList, processLists = readOldDataCard(inputDCfilename)
    data += olddata
    newdataS, newdataT = walk_and_copy(input, input2d, output, threshold, thresholdBG, thresholdSignal, binList, processLists, p0m, p1m, p0h, p1h)
    data += newdataT
    data += newdataS
    out=open(outputDCfilename,'w')
    printTable(data,out)

if __name__ == "__main__":
    logging.basicConfig(stream=sys.stderr, level=logging.INFO)

    if len(sys.argv)>1: threshold = sys.argv[1]
    else:               threshold = 15 # cut on binError/binContent in %

    if len(sys.argv)>2: thresholdBG = sys.argv[2]
    else:               thresholdBG = 7 # cut on binError/binContent_TotalBackground in %

    if len(sys.argv)>3: inputRfile = sys.argv[3]
    else:               inputRfile = "plots.root"

    if len(sys.argv)>4: outputRfile = sys.argv[4]
    else:               outputRfile = "plotsMod.root"

    if len(sys.argv)>5: inputDataCard = sys.argv[5]
    else:               inputDataCard = "dataCard.txt"

    if len(sys.argv)>6: outputDataCard = sys.argv[6]
    else:               outputDataCard = "dataCardMod.txt"
 
    if len(sys.argv)>7: input2dRfile = sys.argv[7]
    else:               input2dRfile = "plots2dZH.root"
    
    if len(sys.argv)>8: p0m = sys.argv[8]
    else:               p0m = 0.8536
    
    if len(sys.argv)>9: p1m = sys.argv[9]
    else:               p1m = 0.0005738
    
    if len(sys.argv)>10:p0h = sys.argv[10]
    else:               p0h = 1.083
    
    if len(sys.argv)>11:p1h = sys.argv[11]
    else:               p1h = -0.000287
    
    if len(sys.argv)>12:thresholdSignal = sys.argv[12]
    else:               thresholdSignal = 0

    '''
    prefix = "/uscms_data/d3/ssagir/WlnuHbbAnalysis/CMSSW_5_3_6/src/VHbb/post/plots"
    prefix += "/dataCardsForBen/templates_3H/"
    inputRfile = prefix+"plots.root"
    outputRfile = prefix+"plots_statUnc%(threshold)s_bg%(thresholdBG)s.root" %locals()
    inputDataCard = prefix+"dataCard.txt"
    outputDataCard = prefix+"dataCard_statUnc%(threshold)s_bg%(thresholdBG)s.txt" %locals()
    '''
    
    log.info("Building shape systematics. input: %s output: %s",
             inputRfile, outputRfile)
    main(inputRfile, input2dRfile, outputRfile, inputDataCard, outputDataCard, float(threshold), float(thresholdBG), float(thresholdSignal), float(p0m), float(p1m), float(p0h), float(p1h))
