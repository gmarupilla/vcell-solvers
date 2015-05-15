/*
 * (C) Copyright University of Connecticut Health Center 2001.
 * All rights reserved.
 */

#include <iostream>
#include <sstream>
#include <stdexcept>
using std::stringstream;
using std::cout;
using std::endl;

#include <VCELL/ChomboIF.h>
#include <VCELL/ChomboSpec.h>
#include <VCELL/SimTool.h>
#include <VCELL/DataSet.h>
#include <VCELL/SimulationMessaging.h>
#include <VCELL/SimulationExpression.h>
#include <VCELL/Variable.h>
#include <VCELL/PostProcessingHdf5Writer.h>

#include <float.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>

#if ( !defined(WIN32) && !defined(WIN64) ) // UNIX
#include <unistd.h>
#endif

#define ZIP_FILE_LIMIT 1E9

#define SIM_FILE_EXT ".sim"
#define SIM_HDF5_FILE_EXT ".sim.hdf5"
#define MESH_HDF5_FILE_EXT ".mesh.hdf5"
#define LOG_FILE_EXT ".log"
#define ZIP_FILE_EXT ".zip"
#define ZIP_HDF5_FILE_EXT ".hdf5.zip"
#define TID_FILE_EXT ".tid"
#define PP_HDF5_FILE_EXT ".hdf5"

int zip32(int filecnt, char* zipfile, ...);
int unzip32(char* zipfile, char* file, char* exdir);

SimTool* SimTool::instance = NULL;

#ifdef CH_MPI
int SimTool::rootRank = 0;
#endif
extern bool bConsoleOutput;

static int NUM_TOKENS_PER_LINE = 4;
static const int numRetries = 2;
static const int retryWaitSeconds = 5;

SimTool::SimTool()
{
	simEndTime = 0.0;
	keepEvery = 100;
	bStoreEnable = true;
	baseFileName=0;
	simFileCount=0;
	zipFileCount = 0;
	baseDirName = NULL;
	baseSimName = NULL;

	vcellModel = 0;
	simulation = 0;
	solver = CHOMBO_SEMIIMPLICIT_SOLVER;
	simStartTime = 0;
	
	postProcessingHdf5Writer = NULL;
	
	
#ifdef CH_MPI
	MPI_Comm_rank(MPI_COMM_WORLD,&myRank);
	MPI_Comm_size(MPI_COMM_WORLD,&commSize);
#endif
	
//	numDiscontinuityTimes = 0;
//	discontinuityTimes = 0;
//	sundialsRelTol = 1e-7;
//	sundialsAbsTol = 1e-9;
//	sundialsMaxStep = 0.1;
//	pcgRelTol = 1e-8;
//	bSundialsOneStepOutput = false;
//	keepAtMost = 5000;
}

SimTool::~SimTool()
{
	delete baseSimName;
	delete baseDirName;
	delete baseFileName;

	if (postProcessingHdf5Writer != NULL)
	{
		delete postProcessingHdf5Writer;
	}
//	delete[] discontinuityTimes;
}

void SimTool::setModel(VCellModel* model) {
	if (model == 0) {
		throw "SimTool::setModel(), model can't be null";
	}
	vcellModel = model;
}

void SimTool::setSimulation(SimulationExpression* sim) {
	if (sim == 0) {
		throw "SimTool::setSimulation(), simulation can't be null";
	}
	simulation = sim;
	simulation->setDT_sec(simDeltaTime);
}

void SimTool::setTimeStep(double period) {
	simDeltaTime = period;
}

void SimTool::create() {
	if (instance == 0) {
		instance = new SimTool();
	} else {
		throw "SimTool (singleton) has been created";
	}
}

SimTool* SimTool::getInstance() {
	return instance;
}

bool SimTool::checkStopRequested() {
	 return SimulationMessaging::getInstVar()->isStopRequested();
}

void SimTool::setBaseFilename(char *fname) {
	if (fname == 0 || strlen(fname) == 0) {
		throw "invalid base file name for data set";
	}
	baseFileName = new char[strlen(fname) + 1];
	memset(baseFileName, 0, strlen(fname) + 1);
	memcpy(baseFileName, fname, strlen(fname) * sizeof(char));

	// extract directory
	baseDirName = new char[strlen(baseFileName) + 1];
	baseSimName = NULL;

	strcpy(baseDirName, baseFileName);
	char* p = strrchr(baseDirName, DIRECTORY_SEPARATOR);
	if (p == NULL) {
		baseSimName = baseDirName;
		baseDirName = 0;
	} else {
		baseSimName = new char[strlen(p+1) + 1];
		strcpy(baseSimName, p + 1);
		*(p + 1)= 0;
	}
	pout() << "Base Simulation Name is " << baseSimName << endl;
}

static void retryWait(int seconds) {
#if ( defined(WIN32) || defined(WIN64) )
	Sleep(seconds * 1000);
#else
	sleep(seconds);
#endif
}

static FILE* openFileWithRetry(const char* fileName, const char* mode) {
	static const char* METHOD = "(openFileWithRetry)";
	pout() << "Entry " << METHOD << endl;

	FILE *fp = NULL;
	for (int retry = 0; retry < numRetries; retry ++)
	{
		fp = fopen(fileName, mode);

		if (fp != NULL) {
			break;
		}
		if (retry < numRetries - 1) {
			cout << "SimTool, error opening log file <" << fileName << ">, trying again" << endl;
			retryWait(retryWaitSeconds);
		}
	}
	pout() << "Exit " << METHOD << endl;
	return fp;
}

static bool zipUnzipWithRetry(bool bZip, char* zipFileName, char* simFileName, char* errmsg) {
	const char* methodName = "(zipUnzipWithRetry)";
	pout() << "Entry " << methodName << endl;

	bool bSuccess = true;
	int retcode = 0;
	for (int retry = 0; retry < numRetries; retry ++) {
		try {
			if (bZip) {
				retcode = zip32(1, zipFileName, simFileName);						
			} else {
				retcode = unzip32(zipFileName, simFileName, NULL);
			}
			break;
		} catch (const char* ziperr) {
			sprintf(errmsg, "%s", ziperr);
		} catch (...) {
			sprintf(errmsg, "%s, adding .sim to .zip failed.", methodName);
		}
		bSuccess = false;
		if (retry < numRetries - 1) {
			retryWait(retryWaitSeconds);
			pout() << methodName << ", adding .sim to .zip failed, trying again" << endl;
		}
	}
	if (bSuccess && retcode != 0) {
		sprintf(errmsg, "Writing zip file <%s> failed, return code is %d", zipFileName, retcode);
		bSuccess = false;
	}
	pout() << "Exit " << methodName << endl;
	return bSuccess;
}

FILE* SimTool::lockForReadWrite()
{
	const char* thisMethod = "(SimTool::lockForReadWrite)";
	pout() << "Entry " << thisMethod << endl;
	
	int myTaskID = SimulationMessaging::getInstVar()->getTaskID();
	if (myTaskID < 0) {
		return 0;
	}

	char tidFileName[128];
	sprintf(tidFileName,"%s%s", baseFileName, TID_FILE_EXT);

	bool bExist = false;

	struct stat buf;
	if (stat(tidFileName, &buf) == 0) { // if exists
		bExist = true;
	}
	
	FILE* fp = openFileWithRetry(tidFileName, bExist ? "r+" : "w+");

	if (fp == 0){
		char errmsg[512];
		sprintf(errmsg, "%s - error opening .tid file <%s>", thisMethod, tidFileName);
		throw errmsg;
	}
	if (bExist) {
		int taskIDInFile = 0;
		int numRead = fscanf(fp, "%d", &taskIDInFile);
		if (numRead == 1) {
			if (myTaskID < taskIDInFile) {
				cout << "there is a new process running the simulation, exit..." << endl;
				exit(0);
			}
			if (myTaskID == taskIDInFile) { // it's me
				return fp;
			}
		}
		rewind(fp);
	}
	fprintf(fp, "%5d", myTaskID);
	fflush(fp);

	pout() << "Exit " << thisMethod << endl;
	return fp;
}

void SimTool::writeData(double progress, double time, int iteration, bool convertChomboData)
{
	const char* methodName = "(SimTool::writeData)";
	pout() << "Entry " << methodName << endl;	

#ifndef CH_MPI
	FILE *logFP;
	char logFileName[128];
	char zipHdf5FileName[128];

	FILE* tidFP = NULL;
	if (isRootRank())
	{
		tidFP = lockForReadWrite();
	}
#endif
	
	bool bSuccess = true;
	char errmsg[512];
	char hdf5SimFileName[128];
	sprintf(hdf5SimFileName,"%s%.4d%s",baseSimName, simFileCount, SIM_HDF5_FILE_EXT);
	// write VCell and/or Chombo output
	simulation->getScheduler()->writeData(hdf5SimFileName, convertChomboData);

#ifndef CH_MPI
	if (chomboSpec->isSaveVCellOutput())
	{
		sprintf(logFileName,"%s%s",baseFileName, LOG_FILE_EXT);
		logFP = openFileWithRetry(logFileName, "a");

		if (logFP == 0) {
			sprintf(errmsg, "%s - error opening log file <%s>", methodName, logFileName);
			bSuccess = false;
		} else {
			sprintf(zipHdf5FileName,"%s%.2d%s",baseFileName, zipFileCount, ZIP_HDF5_FILE_EXT);
			bSuccess = zipUnzipWithRetry(true, zipHdf5FileName, hdf5SimFileName, errmsg);
			remove(hdf5SimFileName);

			// write the log file
			if (bSuccess) {					
				char zipFileNameWithoutPath[512];
				sprintf(zipFileNameWithoutPath,"%s%.2d%s",baseSimName, zipFileCount, ZIP_HDF5_FILE_EXT);
				fprintf(logFP,"%4d %s %s %.15lg\n", iteration, hdf5SimFileName, zipFileNameWithoutPath, time);

				struct stat buf;
				if (stat(zipHdf5FileName, &buf) == 0 || stat(zipHdf5FileName, &buf)) { // if exists
					if (buf.st_size > ZIP_FILE_LIMIT) {
						zipFileCount ++;
					}
				}
			}
		}
		// close log file
		fclose(logFP);
		// close tid file
		if (tidFP != 0) {
			fclose(tidFP);
		}
	}

	// write hdf5 post processing before writing log entry
	if (postProcessingHdf5Writer != NULL)
	{
		postProcessingHdf5Writer->writeOutput();
	}
#endif
	
	if (bSuccess) {
		if (bConsoleOutput || isRootRank())
		{
#ifndef CH_MPI
			SimulationMessaging::getInstVar()->setWorkerEvent(new WorkerEvent(JOB_DATA, progress, time));
#endif
		}
		simFileCount++;
	} else {
		throw errmsg;
	}
	pout() << "Exit " << methodName << endl;
}

void SimTool::cleanupLastRun(bool convertChomboData)
{
	const char* thisMethod = "(cleanupLastRun)";
	pout() << "Entry " << thisMethod << ", removing log and zip files" << endl;

	simStartTime = 0;
	simFileCount = 0;
	zipFileCount = 0;

	char buffer[256];
	if (!convertChomboData)
	{
		sprintf(buffer,"%s%s",baseFileName, MESH_HDF5_FILE_EXT);
		remove(buffer);
	}
	for (int i = 0; i < 10; ++ i)
	{
		sprintf(buffer,"%s%s%02d",baseFileName, zipFileCount, ZIP_HDF5_FILE_EXT);
		remove(buffer);
	}
	sprintf(buffer,"%s%s",baseFileName, LOG_FILE_EXT);
	remove(buffer);
	sprintf(buffer,"%s%s",baseFileName, PP_HDF5_FILE_EXT);
	remove(buffer);
	pout() << "Exit " << thisMethod << endl;
}

void SimTool::setSolver(string& s) {
	if (s.length() == 0 || s != CHOMBO_SEMIIMPLICIT_SOLVER) {
		stringstream ss;
		ss << "SimTool::setSolver(), unknown solver : " << s;
		throw ss.str();
	}
	solver = s;
}

void SimTool::start(bool convertChomboData)
{
	if (convertChomboData)
	{
#ifdef CH_MPI
		throw "Chombo data conversion is not supported in MPI Parallel";
#else
		chomboSpec->setSaveChomboOutput(false);
		chomboSpec->setSaveVCellOutput(true);
#endif
	}

#ifndef CH_MPI
	if (simulation->getPostProcessingBlock() != NULL)
	{
		char h5PPFileName[128];
		sprintf(h5PPFileName, "%s%s", baseFileName, PP_HDF5_FILE_EXT);
		postProcessingHdf5Writer = new PostProcessingHdf5Writer(h5PPFileName, simulation->getPostProcessingBlock());
	}
#endif
	
	simulation->initSimulation();
	// clean up last run results
	cleanupLastRun(convertChomboData);

	if (checkStopRequested()) {
		return;
	}

	if (simulation == NULL) {
		throw "NULL simulation";
	}

	if (bStoreEnable && (baseFileName == NULL || strlen(baseFileName) == 0)) {
		throw "Invalid base file name for dataset";
	}

	char message[256];
	sprintf(message, "simulation [%s] started", baseSimName);
	if (bConsoleOutput || isRootRank())
	{
		SimulationMessaging::getInstVar()->setWorkerEvent(new WorkerEvent(JOB_STARTING, message));
	}

	//
	// destroy any partial results from unfinished iterations
	//
	double percentile = simStartTime/simEndTime;
	double increment = 0.01;
	double lastSentPercentile = percentile;
	//
    // store initial log if enabled
    //
	if (simulation->getCurrIteration()==0)
	{
		// simulation starts from scratch
		if (bStoreEnable)
		{
			if (!convertChomboData)
			{
				simulation->getScheduler()->writeMembraneFiles();
			}
			writeData(0.0, 0.0, 0, convertChomboData);
		}
		else
		{
			if (bConsoleOutput || isRootRank())
			{
#ifndef CH_MPI
				SimulationMessaging::getInstVar()->setWorkerEvent(new WorkerEvent(JOB_DATA, 0, 0));
#endif
			}
		}
	} else {
		// simulation continues from existing results, send data message
		if (bConsoleOutput || isRootRank())
		{
#ifndef CH_MPI
			SimulationMessaging::getInstVar()->setWorkerEvent(new WorkerEvent(JOB_DATA, percentile, simStartTime));
#endif
		}
	}
	//
	// iterate up to but not including end time
	//
	double epsilon = 1e-12;

	while (true) {
		if (simulation->getTime_sec() + simulation->getDT_sec() > simEndTime + epsilon) {
			break;
		}

		if (checkStopRequested()) {
			return;
		}

#ifdef CH_MPI
		if (MPI_Barrier(MPI_COMM_WORLD) != MPI_SUCCESS) {
			throw std::invalid_argument("barrier didn't accept MPI_COMM_WORLD"); 
		}
#endif
		
		simulation->iterate(convertChomboData ? false : true);

		if (checkStopRequested()) {
			return;
		}

		if (simulation->getCurrIteration() % keepEvery == 0 || simulation->getTime_sec() > simEndTime - epsilon){
			if (bStoreEnable){
				writeData(percentile,simulation->getTime_sec(), simulation->getCurrIteration(), convertChomboData);
      }
    }
		percentile = (simulation->getTime_sec() - simStartTime)/(simEndTime - simStartTime);
		if (percentile - lastSentPercentile >= increment) {
			if (bConsoleOutput || isRootRank())
			{
				SimulationMessaging::getInstVar()->setWorkerEvent(new WorkerEvent(JOB_PROGRESS, percentile, simulation->getTime_sec()));
			}
			lastSentPercentile = percentile;
		}
	}

	if (checkStopRequested()) {
		return;
	} 
	if (bConsoleOutput || isRootRank())
	{
#ifdef CH_MPI
		SimulationMessaging::getInstVar()->setWorkerEvent(new WorkerEvent(JOB_DATA, 1.0, simulation->getTime_sec()));
#endif
		SimulationMessaging::getInstVar()->setWorkerEvent(new WorkerEvent(JOB_PROGRESS, 1.0, simulation->getTime_sec()));
		SimulationMessaging::getInstVar()->setWorkerEvent(new WorkerEvent(JOB_COMPLETED, percentile, simulation->getTime_sec()));
	}
}
