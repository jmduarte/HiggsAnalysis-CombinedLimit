from HiggsAnalysis.CombinedLimit.PhysicsModel import *

### This base class implements signal yields by production and decay mode
### Specific models can be obtained redefining getHiggsSignalYieldScale
class TwoHypotesisHiggs(PhysicsModel):
    def __init__(self): 
        self.mHRange = []
        self.muAsPOI    = False
        self.muFloating = False
        self.fqqIncluded = False
        self.fqqFloating = False
        self.poiMap  = []
        self.pois    = {}
        self.verbose = False
        self.altSignal  = "ALT"
        self.altSignal2  = "ALT2"
    def setModelBuilder(self, modelBuilder):
        PhysicsModel.setModelBuilder(self, modelBuilder)
        self.modelBuilder.doModelBOnly = False
    def getYieldScale(self,bin,process):
        "Split in production and decay, and call getHiggsSignalYieldScale; return 1 for backgrounds "
        if not self.DC.isSignal[process]: return 1

        isAlt=0 #VH scalar
        if 'ALT' in process: isAlt=1   #VH pseudoscalar
        elif ('ggH' in process or 'qqH' in process): isAlt=2     #VV
        elif 'ggZhTriangleOnly' in process: isAlt=3
        elif 'ggZhBoxOnly' in process: isAlt=4
        elif 'ggZh' in process:isAlt=5
        
        if self.pois:
            target = "%(bin)s/%(process)s" % locals()
            scale = 1
            for p, l in self.poiMap:
                for el in l:
                    if re.match(el, target):
                        scale = p + self.sigNorms[isAlt]

            print "Will scale ", target, " by ", scale
            return scale;

	elif self.fqqIncluded:
	    ret = self.sigNorms[isAlt]
	    if isAlt: ret+= self.sigNormsqqH["qqbarH" in process]
            print "Process ", process, " will get scaled by ", ret
	    return ret

        else:
            print "Process ", process, " will get norm ", self.sigNorms[isAlt]
            return self.sigNorms[isAlt]
    
    def setPhysicsOptions(self,physOptions):
        print "Physics options: ", physOptions
        for po in physOptions:
	    if po == "fqqIncluded":
		print "Will consider fqq = fraction of qqH in Alt signal (signal strength will be left floating)"
		# Here alsways setting muFloating if fqq in model, should this be kept optional?
		self.fqqIncluded = True
                self.muFloating = True
	    if po == "fqqFloating":
		self.fqqIncluded = True
		self.fqqFloating = True
		self.fqqRange = "0.","1."
                self.muFloating = True
            if po.startswith("fqqRange="):
		self.fqqIncluded = True
		self.fqqFloating = True
                self.muFloating = True
                self.fqqRange = po.replace("fqqRange=","").split(",")
                if len(self.fqqRange) != 2:
                    raise RuntimeError, "fqq range definition requires two extrema"
                elif float(self.fqqRange[0]) >= float(self.fqqRange[1]):
                    raise RuntimeError, "Extrema for fqq range defined with inverterd order. Second must be larger the first"
            if po == "muAsPOI": 
                print "Will consider the signal strength as a parameter of interest"
                self.muAsPOI = True
                self.muFloating = True
            if po == "muFloating": 
                print "Will consider the signal strength as a floating parameter (as a parameter of interest if --PO muAsPOI is specified, as a nuisance otherwise)"
                self.muFloating = True
            if po.startswith("altSignal="): self.altSignal = po.split(",")[1]
            if po.startswith("higgsMassRange="):
                self.mHRange = po.replace("higgsMassRange=","").split(",")
                if len(self.mHRange) != 2:
                    raise RuntimeError, "Higgs mass range definition requires two extrema"
                elif float(self.mHRange[0]) >= float(self.mHRange[1]):
                    raise RuntimeError, "Extrema for Higgs mass range defined with inverterd order. Second must be larger the first"
            if po.startswith("verbose"):
                self.verbose = True
            if po.startswith("map="):
                self.muFloating = True
                (maplist,poi) = po.replace("map=","").split(":")
                maps = maplist.split(",")
                poiname = re.sub("\[.*","", poi)
                if poiname not in self.pois:
                    if self.verbose: print "Will create a var ",poiname," with factory ",poi
                    self.pois[poiname] = poi
                if self.verbose:  print "Mapping ",poiname," to ",maps," patterns"
                self.poiMap.append((poiname, maps))
                                                                                                            
    def doParametersOfInterest(self):
        """Create POI and other parameters, and define the POI set."""
        
        #self.modelBuilder.doVar("CMS_zz4l_fg4[0,0,1]");
        if self.modelBuilder.out.var("CMS_zz4l_fg4"):
                   print "have CMS_zz4l_fg4 inside"
        else:
                   self.modelBuilder.doVar("CMS_zz4l_fg4[0,0,1]")
        poi = "CMS_zz4l_fg4"
        
        
        if self.muFloating: 

            if self.pois:
                for pn,pf in self.pois.items():
                    self.modelBuilder.doVar(pf)
                    if self.muAsPOI:
                        print 'Treating %(pn)s as a POI' % locals()
                        poi += ','+pn
        
                    self.modelBuilder.factory_('expr::%(pn)s_times_not_CMS_zz4l_fg4("@0*(1-@1)", %(pn)s, CMS_zz4l_fg4)' % locals())
                    self.modelBuilder.factory_('expr::%(pn)s_times_CMS_zz4l_fg4("@0*@1", %(pn)s, CMS_zz4l_fg4)' % locals())
                self.sigNorms = { True:'_times_CMS_zz4l_fg4', False:'_times_not_CMS_zz4l_fg4' }
                                    
            else:
                self.modelBuilder.doVar("r[1,0,4]");
                if self.muAsPOI:
                    print 'Treating r as a POI'
                    poi += ",r"

                self.modelBuilder.doVar("r_qq[1,-10,10]");
                self.modelBuilder.doVar("r_box[1,-100,100]");

                self.modelBuilder.factory_("expr::r_times_not_CMS_zz4l_fg4(\"@0*(1-@1)\", r, CMS_zz4l_fg4)")
                self.modelBuilder.factory_("expr::r_times_CMS_zz4l_fg4(\"@0*@1\", r, CMS_zz4l_fg4)")
                self.modelBuilder.factory_("expr::r_times_r_qq_times_not_CMS_zz4l_fg4(\"@0*@2*(1-@1)\", r, CMS_zz4l_fg4, r_qq)")
                self.modelBuilder.factory_("expr::r_times_r_qq_times_CMS_zz4l_fg4(\"@0*@1*@2\", r, CMS_zz4l_fg4, r_qq)")

                #ggZH
                self.modelBuilder.factory_("expr::rTimesRqqTimesOneMinusF_minus_sqrt_rTimesOneMinusF(\"(@0*@2*(1-@1)) - (((@3*@0*@2)/abs(@3*@0*@2))*((abs(@3*@0*@2)*(1-@1))^(0.5)))\",r,CMS_zz4l_fg4, r_qq, r_box)") #triangle
                self.modelBuilder.factory_("expr::rBox_minus_sqrt_rTimesOneMinusF(                   \"@3             - (((@3*@0*@2)/abs(@3*@0*@2))*((abs(@3*@0*@2)*(1-@1))^(0.5)))\",r,CMS_zz4l_fg4, r_qq, r_box)") #box
                self.modelBuilder.factory_("expr::sqrt_rTimesOneMinusF(                                               \"(((@3*@0*@2)/abs(@3*@0*@2))*((abs(@3*@0*@2)*(1-@1))^(0.5)))\",r,CMS_zz4l_fg4, r_qq, r_box)") #box + triangle

                """
                isAlt=0 #VH scalar
                if 'ALT' in process: isAlt=1   #VH pseudoscalar
                elif ('ggH' in process or 'qqH' in process): isAlt=2     #VV
                elif 'ggZhTriangleOnly' in process: isAlt=3
                elif 'ggZhBoxOnly' in process: isAlt=4
                elif 'ggZh' in process:isAlt=5
                """
                self.sigNorms = { 5:'sqrt_rTimesOneMinusF', 4:'rBox_minus_sqrt_rTimesOneMinusF', 3:'rTimesRqqTimesOneMinusF_minus_sqrt_rTimesOneMinusF', 2:'r', 1:'r_times_r_qq_times_CMS_zz4l_fg4', 0:'r_times_r_qq_times_not_CMS_zz4l_fg4' }

            	if self.fqqIncluded:

			if self.fqqFloating: self.modelBuilder.doVar("fqq[0,%s,%s]" % (self.fqqRange[0],self.fqqRange[1]));
			else: self.modelBuilder.doVar("fqq[0]");
	                self.modelBuilder.factory_("expr::r_times_CMS_zz4l_fg4_times_fqq(\"@0*@1\", r_times_CMS_zz4l_fg4, fqq)")
        	        self.modelBuilder.factory_("expr::r_times_CMS_zz4l_fg4_times_not_fqq(\"@0*(1-@1)\", r_times_CMS_zz4l_fg4, fqq)")
 
			self.sigNormsqqH = {True:'_times_fqq',False:'_times_not_fqq'}

        else:
            self.modelBuilder.factory_("expr::not_CMS_zz4l_fg4(\"(1-@0)\", CMS_zz4l_fg4)")
            self.sigNorms = { True:'CMS_zz4l_fg4', False:'not_CMS_zz4l_fg4' }
        if self.modelBuilder.out.var("MH"):
            if len(self.mHRange):
                print 'MH will be left floating within', self.mHRange[0], 'and', self.mHRange[1]
                self.modelBuilder.out.var("MH").setRange(float(self.mHRange[0]),float(self.mHRange[1]))
                self.modelBuilder.out.var("MH").setConstant(False)
                poi+=',MH'
            else:
                print 'MH will be assumed to be', self.options.mass
                self.modelBuilder.out.var("MH").removeRange()
                self.modelBuilder.out.var("MH").setVal(self.options.mass)
        else:
            if len(self.mHRange):
                print 'MH will be left floating within', self.mHRange[-1], 'and', self.mHRange[1]
                self.modelBuilder.doVar("MH[%s,%s]" % (self.mHRange[0],self.mHRange[1]))
                poi+=',MH'
            else:
                print 'MH (not there before) will be assumed to be', self.options.mass
                self.modelBuilder.doVar("MH[%g]" % self.options.mass)
        self.modelBuilder.doSet("POI",poi)

twoHypothesisHiggs = TwoHypotesisHiggs()

