#include "CGraphOriented.h"

#include "../CException/CException.h"


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

	if (mGROVertex.find(VerVertex.VERGetName()) != mGROVertex.end())
	{
		mGROVertex[VerVertex.VERGetName()] = &VerVertex;
	}
	else
	{
		throw CException(vertex_already_existed,"a vertex with that value already existed",  "CGraphOriented.cpp", 29);
	}
}

void CGraphOriented::GROAddArc(CVertex& sVertexDep, CVertex& sVertexArr)
{
	if (GROCheckExistenceOfArc(sVertexDep, sVertexArr) == false)
	{
		sVertexArr.VERAddInTheMapIn(sVertexDep.VERGetName());
		sVertexDep.VERAddInTheMapOut(sVertexArr.VERGetName());

		CArc* arc = new CArc(sVertexDep.VERGetName(), sVertexArr.VERGetName());
		mGROArcs[sVertexDep.VERGetName()] = arc;
	}


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

bool CGraphOriented::GROCheckExistenceOfArc(CVertex& vertexDep, CVertex& vertexArr)
{
	bool bRes = false;
	if (vertexDep.VERGetArcIn()[vertexArr.VERGetName()] || vertexDep.VERGetArcOut()[vertexArr.VERGetName()]
		|| vertexArr.VERGetArcIn()[vertexDep.VERGetName()] || vertexArr.VERGetArcOut()[vertexDep.VERGetName()])
		bRes = true;

	return bRes;
}

}
