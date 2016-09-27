from ROOT import *
from array import array
from glob import glob
import os
import fnmatch

gROOT.SetBatch(1)
gROOT.ProcessLine(".L /uscms_data/d1/jstupak/fa3Combo/CMSSW_6_1_1/src/HiggsAnalysis/CombinedLimit/DR_p0plusp1_050915_correlatedBkg/plotEverything.C+")
#gROOT.ProcessLine('.L /uscms_data/d1/jstupak/fa3Combo/CMSSW_6_1_1/src/HiggsAnalysis/CombinedLimit/DR_p0plusp1_050915_correlatedBkg/johnPlot.C+')

inputs=[#'condor.ZZZh_CMS_common_observed_minuit2_0p01.out',
        'condor.*.out',
        ]

otherNuis=['r',
           'r_qq',
           'r_box',
           'zh_highBoost_trend',
           'wh_highBoost_trend',
           'zh_medBoost_trend',
           'wh_medBoost_trend',
           ]

toDraw=['r',
        'r_qq',
        'r_box',
        'r_times_r_qq',
        'zh_highBoost_trend',
        'wh_highBoost_trend',
        'zh_medBoost_trend',
        'wh_medBoost_trend',
        ]

#################################################################################################################

def plot(input):
    c=TCanvas()

    yValues={}
    tmp_yValues={}
    
    xValues=[]

    x=-1
    nextX=-1
    print 'opening file:',input
    try:
        for line in open(input):
            #print 'file open:',input
            if line.startswith('Point') and ' CMS_zz4l_fg4 ' in line:
                x=nextX
                nextX=float(line.split('=')[1])
                appended=False

                #print 'CMS_zz4l_fg4:',x

                for nuis in tmp_yValues.keys():
                    if not nuis in yValues.keys(): yValues[nuis]=[]
                    if tmp_yValues[nuis]:
                        yValues[nuis].append(tmp_yValues[nuis])
                        #if nuis=='r': print "append r:",tmp_yValues[nuis]
                        appended=True
                    else:
                        tmp_yValues[nuis]=None
                        break
                    tmp_yValues[nuis]=None

                if appended:
                    xValues.append(x)
                    #print "append x:",x

            else:
                for nuis in otherNuis:
                    if line.startswith(nuis):
                        nuis=line.split()[0]
                        #if not nuis in tmp_yValues.keys(): tmp_yValues[nuis]=[]
                        tmp_yValues[nuis]=float(line.split()[2])
                    elif nuis in line:
                        l=line.split()
                        try: float(l[0]),float(l[2]),float(l[3]),float(l[4])
                        except: continue
                        if nuis==l[1]:
                            #if not nuis in tmp_yValues.keys(): tmp_yValues[nuis]=[]
                            tmp_yValues[nuis]=float(l[2])
        appended=False
        for nuis in tmp_yValues.keys():
            if tmp_yValues[nuis]:
                yValues[nuis].append(tmp_yValues[nuis])
                appended=True
        if appended: xValues.append(nextX)

        #######################################################################

        madeSummary=False

        f2=TFile('.'.join(input.replace('.out','.combine.root').split('.')[1:]))
        t=f2.Get('limit')
        scan=None
        if t:
            #scan=johnPlot(TString('.'.join(input.replace('.out','.combine.root').split('.')[1:])))
            t.Draw('2*deltaNLL:CMS_zz4l_fg4')

            t_y=t.GetV1()
            t_x=t.GetV2()

            fa3=[]
            deltaNLL=[]
            for i in range(t.GetSelectedRows()):
                fa3.append(t_x[i])
                deltaNLL.append(t_y[i])
                #print i

            fa3,deltaNLL=[list(z) for z in zip(*sorted(zip(fa3,deltaNLL), key=lambda pair: pair[0]))]

            #-----------------------------------------------------------------------------------------
            #remove xValues from log if not in ntuple

            toPop=[]
            for i in range(len(xValues)):
                print i
                keep=False
                for f in fa3:
                    if abs(f-xValues[i])<.0001: keep=True
                if not keep:
                    print 'Not found in ntuple:',xValues[i]
                    toPop.append(i)
            toPop.reverse()
            for i in toPop:
                print i
                for key in yValues.keys(): 
                    yValues[key].pop(i)
                xValues.pop(i)

            #should we remove scan points from ntuple which look bad in log?
            scan=TGraph(len(fa3),array('f',fa3),array('f',deltaNLL))
            #scan=cleanGraph(t)

            scan.SetTitle(';fa3;-2#DeltalnL')
            scan.SetLineColor(kRed)
            scan.Draw("AL")
            c.SaveAs('plots/'+os.path.basename(input).replace('.out','_scan.pdf'))

        #-----------------------------------------------------------------------------------------

        print 'len(xValues) [from log]:',len(xValues)
        print xValues[:5],'...',xValues[-5:]
        print
        if scan:
            print 'len(fa3) [from ntuple]:',len(fa3)
            print fa3[:5],fa3[-5:]
            print
            print 'len(deltaNLL [from ntuple]:',len(deltaNLL)
            print deltaNLL[:5],'...',deltaNLL[-5:]
            print

        graphs={}
        for nuis in yValues.keys():
            print
            print 'len('+nuis+'):',len(yValues[nuis])
            print yValues[nuis][:5],'...',yValues[nuis][-5:]
            if len(yValues[nuis])!=len(xValues):
                print "ERROR!"
                print 'nuis:',nuis,'  len(yValues[nuis]):', len(yValues[nuis]), '  len(xValues):',len(xValues)
                print yValues[nuis]
                print xValues
                exit()

            print 'Making graph:',nuis
            g=TGraph(len(yValues[nuis]),array('f',xValues),array('f',yValues[nuis]))
            g.SetTitle(';fa3;'+nuis)
            g.SetLineColor(kRed)
            g.Draw('APL')
            print 'Saving canvas'
            c.SaveAs('plots/'+os.path.basename(input).replace('.out','_'+nuis+'.pdf'))
            print 'Saved canvas'
            graphs[nuis]=g.Clone('p_'+g.GetName())

        if 'r_qq' in yValues.keys():
            print 'Making graph: r times r_qq'
            y=[r*r_qq for r,r_qq in zip(yValues['r'],yValues['r_qq'])]
            g=TGraph(len(y),array('f',xValues),array('f',y))
            g.SetTitle(';fa3;r times r_qq')
            g.SetLineColor(kRed)
            g.Draw('APL')
            graphs['r_times_r_qq']=g.Clone('p_'+g.GetName())
            c.SaveAs('plots/'+os.path.basename(input).replace('.out','_r_times_r_qq.pdf')) 
        print 'Done with graphs'

        #-----------------------------------------------------------------------------------------
        """
        madeSummary=False

        f2=TFile('.'.join(input.replace('.out','.combine.root').split('.')[1:]))
        t=f2.Get('limit')
        scan=None
        if t:
            #scan=johnPlot(TString('.'.join(input.replace('.out','.combine.root').split('.')[1:])))
            t.Draw('2*deltaNLL:CMS_zz4l_fg4')

            t_y=t.GetV1()
            t_x=t.GetV2()

            fa3=[]
            deltaNLL=[]
            for i in range(t.GetSelectedRows()):
                fa3.append(t_x[i])
                deltaNLL.append(t_y[i])

            fa3,deltaNLL=[list(z) for z in zip(*sorted(zip(fa3,deltaNLL), key=lambda pair: pair[0]))]

            t_f=[]
            t_d=[]
            for i in range(len(fa3)):
                keep=False
                for x in xValues:
                    if abs(fa3[i]-x)<.0001: keep=True
                if not keep:
                    print 'Not found in log:',f

                    for l in 
            fa3=t_f
            deltaNLL=t_d
        """
        """
            for i in range(len(fa3)):
                keep = 0;
                if i==0: keep = 1;
                elif i==1: keep = 1;
                elif i==len(deltaNLL)-1: keep = 1;
                elif i==len(deltaNLL)-2: keep = 1;
                if keep==0:
                    if (deltaNLL[i+1]-deltaNLL[i])*(deltaNLL[i]-deltaNLL[i-1])>0: keep = 1;
                    elif abs((deltaNLL[i]-deltaNLL[i-1])/(deltaNLL[i]+deltaNLL[i-1]))<0.04: keep = 1;
                    elif abs((deltaNLL[i]-deltaNLL[i+1])/(deltaNLL[i]+deltaNLL[i+1]))<0.04: keep = 1;
                    if keep==0:
                        if abs((deltaNLL[i-1]-deltaNLL[i-2])/(deltaNLL[i-1]+deltaNLL[i-2]))>0.1: keep = 1;
                        elif abs((deltaNLL[i+1]-deltaNLL[i+2])/(deltaNLL[i+1]+deltaNLL[i+2]))>0.1: keep = 1;
            clean
        """
        """
            scan=TGraph(len(fa3),array('f',fa3),array('f',deltaNLL))

            #scan=cleanGraph(t)

            scan.SetTitle(';fa3;-2#DeltalnL')
            scan.SetLineColor(kRed)
            scan.Draw("AL")
            c.SaveAs('plots/'+os.path.basename(input).replace('.out','_scan.pdf'))
        """
        c.Clear()
        c.Divide(4,2)
        if scan:
            c.cd(1)
            scan.Draw("AL")
            madeSummary=True

        i=2
        for nuis in toDraw:
            if nuis in graphs.keys():
                c.cd(i)
                graphs[nuis].Draw("APL")
                i+=1
                madeSummary=True

        if madeSummary: c.SaveAs('plots/'+os.path.basename(input).replace('.out','_summary.pdf'))
    except: pass
        
#################################################################################################################

if __name__=='__main__':
    for input in inputs:
        for i in glob(input):
            print i
            plot(i)
            print
