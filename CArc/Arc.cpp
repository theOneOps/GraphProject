#include "Arc.h"



CArc::CArc(string sDep, string sArr) :sARCArr(sArr), sARCDep(sDep){}

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