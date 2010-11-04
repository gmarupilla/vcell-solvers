#ifndef VFRAPOBJECTIVEFUNCTION_H
#define VFRAPOBJECTIVEFUNCTION_H

#include "ObjectiveFunction.h"

class SpatialReferenceData;
class ParameterDescription;
class FVSolver;

class VFRAPObjectiveFunction : public ObjectiveFunction {
public:
	VFRAPObjectiveFunction(ParameterDescription *parameterDescription,
		SpatialReferenceData* refData,
		SpatialReferenceData* simData,
		void (*checkStopRequested)(double, long));
	~VFRAPObjectiveFunction();

	virtual void objective(int nparams, double* parameterValus, double* functionValue);
	virtual int getNumObjFuncEvals();
	virtual double getBestObjectiveFunctionValue();
	virtual double* getBestParameterValues();
	void setCheckStopRequested(void (*checkStopRequested)(double, long));

private:
	//
	// need output time array support in FVSolver or at least integrate until t=T and continue.
	//
	double* unscaled_x;
	FVSolver* fvSolver;
	ParameterDescription* parameterDescription;
	SpatialReferenceData* referenceData;
	SpatialReferenceData* simDataD1;

	void (*fn_checkStopRequested)(double, long);
};

#endif
