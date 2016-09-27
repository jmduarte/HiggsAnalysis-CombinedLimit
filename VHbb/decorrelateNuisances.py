#!/usr/bin/env python

from utils import printTable
from numpy import linspace
import fnmatch
import logging
import ROOT
import sys,os

none = "-"
one = "1"

def readDataCard(filename):
    f = open(filename, 'rU')
    lines = f.readlines()
    f.close()
    data = []
    bin = []
    process = []
    for line in lines:
    	if (line.startswith("bin") or line.startswith("process") or line.startswith("rate")): 
    		if line.startswith("bin"): bin=line.strip().split()
    		if line.startswith("process"): process.append(line.strip().split())
    	else: continue
    for line in lines:
    	doDecor = "eff_b" in line or "FakeRate_b" in line or "scale_j" in line or "res_j" in line or "ttbar_shape" in line or "W_light_shape" in line or "W_b_shape" in line or "W_bb_shape" in line
    	if line.startswith("----"): data.append(['break'])
    	elif (line.startswith("Observation") or line.startswith("shapes")): data.append([line.strip().split()[0],'','','']+line.strip().split()[1:])
    	elif (line.startswith("bin") or line.startswith("process") or line.startswith("rate")): data.append([line.strip().split()[0],'']+line.strip().split()[1:])
    	elif line.startswith("stat_"): continue
    	elif "trend" in line: data.append(line.replace("5", "2").strip().split())
    	elif doDecor:
    		lineMed = [line.strip().split()[0]+'_medBoost',line.strip().split()[1]]
    		lineHigh = [line.strip().split()[0]+'_highBoost',line.strip().split()[1]]
    		for i in range(len(bin)-1):
    			if 'medBoost' in bin[i+1]: 
    				lineMed.append(line.strip().split()[2+i])
    				lineHigh.append(none)
    			elif 'highBoost' in bin[i+1]:
    				lineMed.append(none)
    				lineHigh.append(line.strip().split()[2+i])
    			else: print "WARNING: NO BOOST INFO FOUND IN BIN NAME!!!" 
    		data.append(lineMed)
    		data.append(lineHigh)
    		print "De-correlating Nuisance: ", line.strip().split()[0]
    		print "                     AS: ", lineMed[0], " and ", lineHigh[0]
    	else: data.append(line.strip().split())
    return data

def walk_and_copy(inputdir, outputdir):
    ''' Recursive function which copies from inputdir to outputdir '''
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
        	th1_temp = inputdir.Get(histo)
        	if 'medBoost' in histo: boost='medBoost'
        	elif 'highBoost' in histo: boost='highBoost'
        	else: print "WARNING: NO BOOST INFO FOUND IN HISTOGRAM NAME!!!"
        	doDeCorr = "eff_b" in histo[histo.find("__")+2:]
        	doDeCorr = doDeCorr or "FakeRate_b" in histo[histo.find("__")+2:]
        	doDeCorr = doDeCorr or "scale_j" in histo[histo.find("__")+2:]
        	doDeCorr = doDeCorr or "res_j" in histo[histo.find("__")+2:]
        	doDeCorr = doDeCorr or "ttbar_shape" in histo[histo.find("__")+2:]
        	doDeCorr = doDeCorr or "W_light_shape" in histo[histo.find("__")+2:]
        	doDeCorr = doDeCorr or "W_b_shape" in histo[histo.find("__")+2:]
        	doDeCorr = doDeCorr or "W_bb_shape" in histo[histo.find("__")+2:] 
        	if "Up" not in histo and "Down" not in histo: th1 = th1_temp
        	elif doDeCorr:
        		if 'Up' in histo[histo.find("__")+2:]: 
        			th1 = th1_temp.Clone(histo[:histo.find("Up")] + '_' + boost + "Up")
        		if 'Down' in histo[histo.find("__")+2:]: 
        			th1 = th1_temp.Clone(histo[:histo.find("Down")] + '_' + boost + "Down")
        	else: th1 = th1_temp
        	if th1.GetName() != th1_temp.GetName(): 
        		print "Modifying histogram: ", th1_temp.GetName()
        		print "                 AS: ", th1.GetName()
        	outputdir.cd()
        	th1.Write()

def main(inputRfilename, outputRfilename, inputDCfilename, outputDCfilename):
    input = ROOT.TFile(inputRfilename, 'READ')
    output = ROOT.TFile(outputRfilename, 'RECREATE')
    if not os.path.exists(inputDCfilename[:-4]+'_original.txt'): os.system('mv '+inputDCfilename+' '+inputDCfilename[:-4]+'_original.txt')
    data = readDataCard(inputDCfilename[:-4]+'_original.txt')
    out=open(inputDCfilename,'w')
    printTable(data,out)
    walk_and_copy(input, output)

if __name__ == "__main__":

    if len(sys.argv)>1: inputRfile = sys.argv[1]
    else:               inputRfile = "plots.root"

    if len(sys.argv)>2: outputRfile = sys.argv[2]
    else:               outputRfile = "plotsMod.root"

    if len(sys.argv)>3: inputDataCard = sys.argv[3]
    else:               inputDataCard = "dataCard.txt"

    if len(sys.argv)>4: outputDataCard = sys.argv[4]
    else:               outputDataCard = "dataCardMod.txt"
    
    main(inputRfile, outputRfile, inputDataCard, outputDataCard)
