#ifndef ODEOBJECTIVEFUNCTION_H
#define ODEOBJECTIVEFUNCTION_H

#include <vector>
using namespace std;

#include "ObjectiveFunction.h"

class OdeResultSet;
class VCellSundialsSolver;
class ParameterDescription;

class OdeObjectiveFunction : public ObjectiveFunction {
public:
	OdeObjectiveFunction(ParameterDescription* parameterDescription, 
		OdeResultSet* arg_referenceData, 
		vector<string>& refColumnMappingExpressions, 
		const char* arg_inputChars,
		void (*checkStopRequested)(double, long));

	~OdeObjectiveFunction();

	virtual void objective(int nparams, double* x, double* f);
	virtual int getNumObjFuncEvals();
	virtual double getBestObjectiveFunctionValue();
	virtual double* getBestParameterValues();
	OdeResultSet* OdeObjectiveFunction::getBestResultSet();
	void setCheckStopRequested(void (*checkStopRequested)(double, long));

private:
	VCellSundialsSolver* sundialsSolver;

	double computeL2error(double* paramValues);

	double* unscaled_x;
	ParameterDescription* parameterDescription;

	OdeResultSet* testResultSet;
	OdeResultSet* referenceData;
	OdeResultSet* bestResultSet;

	void (*fn_checkStopRequested)(double, long);

};

#endif
