#include "CGraphNOriented.h"
#include "../CException/CException.h"


void CGraphNOriented::GROAddArc(CVertex* sVertexDep, CVertex* sVertexArr)
{
	if (GROCheckExistenceOfArc(*sVertexDep, *sVertexArr) == false)
	{
		if (GROCheckExistenceOfArc(*sVertexArr, *sVertexDep) == false)
		{
			sVertexArr->VERAddInTheMapIn(sVertexDep->VERGetName());
			sVertexDep->VERAddInTheMapOut(sVertexArr->VERGetName());

			sVertexDep->VERAddInTheMapIn(sVertexArr->VERGetName());
			sVertexArr->VERAddInTheMapOut(sVertexDep->VERGetName());

			CArc* arc = new CArc(sVertexDep->VERGetName(), sVertexArr->VERGetName());

			GROAddArcInTheMap(sVertexDep->VERGetName(), arc);

			cout << "arc added successfully ! " << endl;
		}

		else
		{
			string sErrorMessage = "an arc with a vertexDep " + sVertexDep->VERGetName() + " and vertexArr " + sVertexArr->VERGetName() + " already existed in the graph";
			throw CException(arc_already_existed, sErrorMessage, "CGraphNOriented.cpp", 9);
		}

	}
	else
	{
		string sErrorMessage = "an arc with a vertexDep " + sVertexDep->VERGetName() + " and vertexArr " + sVertexArr->VERGetName() + " already existed in the graph";
		throw CException(arc_already_existed, sErrorMessage, "CGraphNOriented.cpp", 7);
	}
}

void CGraphNOriented::GRORemoveArc(const string& sNumDep, const string& sNumArr)
{
	if (getGROVertex()[sNumDep] && getGROVertex()[sNumArr])
	{
		CVertex* vDep = getGROVertex()[sNumDep];
		CVertex* vArr = getGROVertex()[sNumArr];

		if (GROCheckExistenceOfArc(*vDep, *vArr))
		{
			vDep->removeArcFromArcIn(vArr->VERGetName());
			vDep->removeArcFromArcOut(vArr->VERGetName());
			vArr->removeArcFromArcIn(vDep->VERGetName());
			vArr->removeArcFromArcOut(vDep->VERGetName());

			auto& allArcDep = getGROArcsAtIndex(sNumDep);
			vector<CArc*>::iterator itDep = allArcDep.begin();

			for (; itDep != allArcDep.end(); itDep++)
			{
				if ((*itDep)->ARCGetVertexArr() == sNumArr)
				{
					break;
				}
			}

			if (itDep != allArcDep.end())
			{
				CArc* local = *itDep;
				allArcDep.erase(itDep);
				delete local;
				//cout << "suppression reussi " << endl;
			}

			auto& allArcArr = getGROArcsAtIndex(sNumArr);
			vector<CArc*>::iterator itArr = allArcArr.begin();

			for (; itArr != allArcArr.end(); itArr++)
			{
				if ((*itArr)->ARCGetVertexArr() == sNumDep)
				{
					break;
				}
			}

			if (itArr != allArcArr.end())
			{
				CArc* local = *itArr;
				allArcArr.erase(itArr);
				delete local;
				//cout << "suppression reussi " << endl;
			}
		}
		else
		{
			string sErrorMessage = "an arc with a vertex Dep " + sNumDep + " an vertex Arr " + sNumArr + " doesn't exist";
			throw CException(arc_not_existed, sErrorMessage, "CGraphOriented.cpp", 151);
		}
	}
	else
	{
		string sErrorMessage = "one of those vertex " + sNumDep + " and " + sNumArr + " doesn't exist";
		throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.cpp", 146);
	}

}
