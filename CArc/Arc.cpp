#include "Arc.h"



CArc::CArc(string sDep, string sArr, unsigned int iweight=0) :sARCArr(sArr), sARCDep(sDep), uiWeight(iweight){}

const string CArc::ARCGetVertexArr() const
{
	return sARCArr;
}

const string CArc::ARCGetVertexDep() const
{
	return sARCDep;
}

void CArc::ARCGROModifyVertexDep(const string& sNewValue)
{
	// set a new value to the dep value of the arc
	sARCDep = sNewValue;
}

void CArc::ARCGROModifyVertexArr(const string& sNewValue)
{
	// set a new value to the arr value of the arc

	sARCArr = sNewValue;
}


const unsigned int CArc::ARCGetWeight() const
{
	return uiWeight;
}