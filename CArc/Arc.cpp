#include "Arc.h"


CArc::CArc()
{

}

CArc::CArc(string sDep, string sArr) :sARCArr(sArr), sARCDep(sDep)
{

}

string CArc::ARCGetVertexArr() const
{
	return sARCArr;
}

string CArc::ARCGetVertexDep() const
{
	return sARCDep;
}

void CArc::ModifyVertexDep(const string& sNewValue)
{
	sARCDep = sNewValue;
}

void CArc::ModifyVertexArr(const string& sNewValue)
{
	sARCArr = sNewValue;
}