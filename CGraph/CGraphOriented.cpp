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
		throw CException(vertex_already_existed,"a vertex with that value already existed",  "CGraphOriented.cpp", 27);
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
		string res = "an arc with that vertexDep " + sVertexDep->VERGetName() +" and vertexArr " + sVertexArr->VERGetName() +" already existed in the graph";
		throw CException(arc_already_existed, res, "CGraphOriented.cpp", 39);
	}
}
void CGraphOriented::GROAddArcInTheMap(const string& key, CArc* arc)
{
	mGROArcs[key] = arc;
}


void CGraphOriented::GRORemoveVertex(const string& sNum)
{
	
	if (mGROVertex.find(sNum) != mGROVertex.end())
	{
		set<string> allAdjacentsVertex = mGROVertex[sNum]->getAllAdjacenceVertexToAVertex();
		if (!allAdjacentsVertex.empty())
		{
			for (string num : allAdjacentsVertex)
			{
				GRORemoveArc(sNum, num);
			}
		}

		delete mGROVertex[sNum];
		mGROVertex.erase(sNum);
	}
}

void CGraphOriented::GRORemoveArc(const string& sNumDep, const string& sNumArr)
{
	if (mGROVertex[sNumDep] && mGROVertex[sNumArr])
	{
		CVertex* vDep = mGROVertex[sNumDep];
		CVertex* vArr = mGROVertex[sNumArr];

		if (GROCheckExistenceOfArc(*vDep, *vArr))
		{
			vDep->removeArcFromArcIn(vArr->VERGetName());
			vDep->removeArcFromArcOut(vArr->VERGetName());

			vArr->removeArcFromArcIn(vDep->VERGetName());
			vArr->removeArcFromArcOut(vDep->VERGetName());

			if (mGROArcs[sNumDep])
			{
				if (mGROArcs[sNumDep]->ARCGetVertexArr() == sNumArr)
				{
					delete mGROArcs[sNumDep];
					mGROArcs.erase(sNumDep);
				}
			}
			else
			{
				if (mGROArcs[sNumArr]->ARCGetVertexArr() == sNumDep)
				{
					delete mGROArcs[sNumArr];
					mGROArcs.erase(sNumArr);
				}
			}
		}
	}
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
