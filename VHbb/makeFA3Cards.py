import os

#sigThresholdList = [0,0.1,0.5,1,5,10]
sigThresholdList = [2.5]
LambdaList = [100,200,300,400,500,600,700,800,900,1000,2000,5000,10000,'Nominal']

for threshold in sigThresholdList:
	for Lambda in LambdaList:
		os.system('./makeFA3Cards.sh '+str(threshold)+' _lambda'+str(Lambda))