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


void CGraphOriented::GROAddVertex(CVertex* VerVertex)
{
	if (mGROVertex.count(VerVertex->VERGetName()) == 0)
	{
		mGROVertex[VerVertex->VERGetName()] = VerVertex;
	}
	else
	{
		throw CException(vertex_already_existed,"a vertex with that value already existed",  "CGraphOriented.cpp", 29);
	}
}

void CGraphOriented::GROAddArc(CVertex* sVertexDep, CVertex* sVertexArr)
{
	if (GROCheckExistenceOfArc(*sVertexDep, *sVertexArr) == false)
	{
		sVertexArr->VERAddInTheMapIn(sVertexDep->VERGetName());
		sVertexDep->VERAddInTheMapOut(sVertexArr->VERGetName());

		CArc* arc = new CArc(sVertexDep->VERGetName(), sVertexArr->VERGetName());

		GROAddArcInTheMap(sVertexDep->VERGetName(), arc);

		cout << "arc added successfully ! " << endl;
	}
	else
	{
		cout << "didn't work for " << sVertexDep->VERGetName() << " and " << sVertexArr->VERGetName() << endl;
	}
}
void CGraphOriented::GROAddArcInTheMap(const string& key, CArc* arc)
{
	mGROArcs[key] = arc;
}


void CGraphOriented::GRORemoveVertex(string& sNum)
{

}

void CGraphOriented::GRORemoveArc(string& sNumdep, string& sNumArr)
{


}

map<string, CVertex*> CGraphOriented::getGROVertex() const
{
	return mGROVertex;
}


bool CGraphOriented::GROCheckExistenceOfArc(CVertex& vertexDep, CVertex& vertexArr)
{
	bool bRes = false;
	if (vertexDep.VERGetArcIn()[vertexArr.VERGetName()] || vertexDep.VERGetArcOut()[vertexArr.VERGetName()]
		|| vertexArr.VERGetArcIn()[vertexDep.VERGetName()] || vertexArr.VERGetArcOut()[vertexDep.VERGetName()])
		bRes = true;

	return bRes;
}
