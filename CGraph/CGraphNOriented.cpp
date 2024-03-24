#include "CGraphNOriented.h"

void CGraphNOriented::GROAddArc(CVertex& sVertexDep, CVertex& sVertexArr)
{
	if (GROCheckExistenceOfArc(sVertexDep, sVertexArr) == false)
	{
		sVertexArr.VERAddInTheMapIn(sVertexDep.VERGetName());
		sVertexDep.VERAddInTheMapOut(sVertexArr.VERGetName());

		GROAddArcInTheMap(sVertexDep.VERGetName(), new CArc(sVertexDep.VERGetName(), sVertexArr.VERGetName()));
		GROAddArcInTheMap(sVertexArr.VERGetName(), new CArc(sVertexArr.VERGetName(), sVertexDep.VERGetName()));
	}

}


void CGraphNOriented::GRORemoveArc(string& sVertexDep, string& sVertexArr)
{

}

bool CGraphNOriented::GROCheckExistenceOfArc(CVertex& vertexDep, CVertex& vertexArr)
{
	bool bRes = false;
	if (vertexDep.VERGetArcIn()[vertexArr.VERGetName()] || vertexDep.VERGetArcOut()[vertexArr.VERGetName()])
		bRes = true;

	return bRes;
}

//void CGraphNOriented::GROModifyVertex(const string& sVertexName, const string& sValue){}
