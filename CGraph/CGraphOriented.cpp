#include "CGraphOriented.h"


CGraphOriented::~CGraphOriented()
{
	for (auto& pair : mGROArcs)
	{
		delete pair.second;
	}

	for (auto& pair : mGROVertex)
	{
		delete pair.second;
	}
}

void CGraphOriented::GROModifyVertex(string& sVertexName, string& sValue)
{

}

void CGraphOriented::GROAddVertex(CVertex& VerVertex)
{

}

void CGraphOriented::GROAddArc(string& sVertexDep, string& sVertexArr)
{

}

void CGraphOriented::GRORemoveVertex(string& sNum)
{

}

void CGraphOriented::GRORemoveArc(string& sNumdep, string& sNumArr)
{

}