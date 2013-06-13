OBJECTFILES = mCG.obj


prog: $(OBJECTFILES)
	cl /FemCG $(OBJECTFILES)
	
	
run:
	mCG dumpdata.txt