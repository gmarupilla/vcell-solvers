#include "PdeOptTesting.h"
#include "NonspatialOptTesting.h"
#include "OptXmlReader2.h"
#include "OptSolverCFSQP.h"
#include "OptSolver2.h"
#include "OptResultSet.h"
#include <iostream>

int main(int argc, char *argv[])
{
	std::cout.precision(30);
	OptXmlReader2 optXmlReader;
	const char* filename1 = "test1.xml";
	const char* filename2 = "test2.xml";
	const char* filename3 = "test3.xml";
	const char* filename4 = "test4.xml";
	const char* filename5 = "test5.xml";
	const char* filename6 = "test6.xml";
	const char* filename7 = "test7.xml";
	OptProblemDescription* optProb = optXmlReader.readOptProblemDescription(filename7);
	OptSolverCFSQP* cfsqpOptSolver = new OptSolverCFSQP(optProb);
	OptResultSet* optResultSet = cfsqpOptSolver->solve();
	optResultSet->show();
	optResultSet->show();

	//runExplitOptTest1();
	//runOdeOptTesting();
	//runExplitOptTest2();
	//runOdeOptTesting();
//	runPdeOptTesting();
//	runVFRAPOptTesting();
}





