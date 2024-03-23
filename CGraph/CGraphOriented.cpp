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

void CGraphOriented::GROModifyVertex(const string& sVertexName, const string& sValue)
{
	if (mGROVertex.find(sValue) != mGROVertex.end())
		throw CException(vertex_already_existed, "a vertex with that value already existed", "CGraphOriented.cpp", 40);
	else
	{
		if (mGROVertex.find(sVertexName) == mGROVertex.end())
			throw CException(vertex_not_existed, "a vertex with that value is not existed", "CGraphOriented.cpp", 40);
		else
		{
			set<string> allAdjacentsVertex = mGROVertex[sVertexName]->getAllAdjacenceVertexToAVertex();

			for (string v : allAdjacentsVertex)
			{
				if (mGROVertex[v]->VERGetArcIn()[sVertexName] == true)
					mGROVertex[v]->changeKeysVerArcIn(sVertexName, sValue);

				if (mGROVertex[v]->VERGetArcOut()[sVertexName] == true)
					mGROVertex[v]->changeKeysVerArcOut(sVertexName, sValue);

				if (mGROArcs[v]->ARCGetVertexArr() == sVertexName)
					mGROArcs[v]->ModifyVertexArr(sValue);

				if (mGROArcs[v]->ARCGetVertexDep() == sVertexName)
					mGROArcs[v]->ModifyVertexDep(sValue);
			}

			if (mGROArcs.find(sVertexName) != mGROArcs.end())
			{
				CArc* ARClocalArc = mGROArcs[sVertexName];
				mGROArcs.erase(sVertexName);
				mGROArcs[sValue] = ARClocalArc;
			}

			if (mGROVertex.find(sVertexName) != mGROVertex.end())
			{
				CVertex* VERlocalVertex = mGROVertex[sVertexName];
				VERlocalVertex->VERModifyName(sValue);
				mGROVertex.erase(sVertexName);
				mGROVertex[sValue] = VERlocalVertex;
			}

		}
	}
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

void CGraphOriented::GROInverseArc(const string& valueDep, const string& valueArr)
{
	if (mGROVertex.find(valueDep) == mGROVertex.end())
	{
		throw CException(vertex_not_existed, "a vertex with that value is not existed", "CGraphOriented.cpp", 29);
	}
	else if (mGROVertex.find(valueArr) == mGROVertex.end())
	{
		throw CException(vertex_not_existed, "a vertex with that value is not existed", "CGraphOriented.cpp", 29);
	}
	else
	{
		if (GROCheckExistenceOfArc(*mGROVertex[valueDep], *mGROVertex[valueArr]))
		{
			mGROVertex[valueDep]->VERModifyArcIn(valueArr, false);
			mGROVertex[valueDep]->VERAddInTheMapOut(valueArr);

			mGROVertex[valueDep]->VERModifyArcOut(valueArr, false);
			mGROVertex[valueDep]->VERAddInTheMapIn(valueArr);

			CArc* ARClocalArc = mGROArcs[valueDep];
			mGROArcs.erase(valueDep);
			mGROArcs[valueArr] = ARClocalArc;
		}
		else
			throw CException(arc_not_existed, "an arc with those vertices's names are not existed", "CGraphOriented.cpp", 29);
	}
}

void CGraphOriented::GROInverseAllArcs()
{
	for (auto it = mGROArcs.begin(); it != mGROArcs.end(); it++)
	{
		if (it->second->ARCGetVertexDep() != it->second->ARCGetVertexArr())
		{
			GROInverseArc(it->second->ARCGetVertexDep(), it->second->ARCGetVertexArr());
		}
	}
}


bool CGraphOriented::GROCheckExistenceOfArc(CVertex& vertexDep, CVertex& vertexArr)
{
	bool bRes = false;
	if (vertexDep.VERGetArcIn()[vertexArr.VERGetName()] || vertexDep.VERGetArcOut()[vertexArr.VERGetName()]
		|| vertexArr.VERGetArcIn()[vertexDep.VERGetName()] || vertexArr.VERGetArcOut()[vertexDep.VERGetName()])
		bRes = true;

	return bRes;
}
