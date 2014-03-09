#ifndef CHOMBOSPEC_H_
#define CHOMBOSPEC_H_

#include <string>
using std::string;

#include <VCELL/ChomboGeometry.h>

class ChomboSpec
{
public:
	ChomboSpec();
	ChomboSpec(ChomboGeometry* cg, int numLevels, double rel_tol, int boxsize, int* tagsGrowSize, double fillRatio, int viewLevel, bool bSaveVCellOutput, bool bSaveChomboOutput, string* roi, int* ratios);
	virtual ~ChomboSpec();

	static int defaultTagsGrow;
	
	int getNumLevels() {
		return numLevels;
	}
	
	int* getRefRatios() {
		return refRatios;
	}
	
	int getMaxBoxSize()
	{
		return maxBoxSize;
	}
	
	double getFillRatio()
	{
		return fillRatio;
	}
	ChomboGeometry* getChomboGeometry() {
		return chomboGeometry;
	}

	const string& getRefinementRoi(int ilev)
	{
		return refinementRois[ilev];
	}

	int getViewLevel()
	{
		return viewLevel;
	}
	void setSaveVCellOutput(bool b)
	{
		bSaveVCellOutput = b;
	}
	void setSaveChomboOutput(bool b)
	{
		bSaveChomboOutput = b;
	}
	bool isSaveVCellOutput()
	{
		return bSaveVCellOutput;
	}
	bool isSaveChomboOutput()
	{
		return bSaveChomboOutput;
	}
	double getRelativeTolerance()
	{
		return relTol;
	}
	
	const int* getTagsGrow()
	{
		return tagsGrow;
	}
private:
	ChomboGeometry* chomboGeometry;
	int numLevels;
	int* refRatios;
	double relTol;
	int maxBoxSize;
	double fillRatio;
	int viewLevel;
	string* refinementRois;
	bool bSaveVCellOutput;
	bool bSaveChomboOutput;
	int* tagsGrow;
};

#endif /*CHOMBOSPEC_H_*/
