#ifndef _CGRAPH_ORIENTE_H
#define _CGRAPH_ORIENTE_H
#include <string>
#include <map>
#include "../CArc/Arc.h"
#include "../CVertex/CVertex.h"

using namespace std;

#define vertex_already_existed 11

/**********************************************************
*  Class : CGrapheOriente
* *********************************************************
* ROLE : management of the oriented graph
* *********************************************************
* VERSION: 1.0
* AUTHOR: Selly Bill-Gate MEDEWOU
*                 Jeremie YANG
* DATE: 19/03/2024
* *********************************************************
*/
class CGraphOriented
{
private:
	//Attributs
	map<string, CVertex*> mGROVertex;
	map<string, CArc*> mGROArcs;
public:

	//Constructors

	/**
	*******************************************************************************
	* CGraphOriented
	* *****************************************************************************
	* Entries : None
	* Needs : None
	* Returns : None
	* Leads : destroy the Vertex value of all the key of each map (mGROVertex, mGROArcs)
	*******************************************************************************
	*/
	~CGraphOriented();


	//methods

	/**
	*******************************************************************************
	* GROModifyVertex
	* *****************************************************************************
	* Entries : svertexname a string ; savalue a string
	* Needs : None
	* Returns : void
	* Leads : modify a svertexname by svalue
	*******************************************************************************
	*/
	void GROModifyVertex(string& sVertexName, string& sValue);

	/**
	*******************************************************************************
	* GROAddVertex
	* *****************************************************************************
	* Entries : Ververtex a vertex
	* Needs : None
	* Returns : void
	* Leads : add a vertex
	*******************************************************************************
	*/
	void GROAddVertex(CVertex& VerVertex);

	/**
	*******************************************************************************
	* GROAddArc
	* *****************************************************************************
	* Entries : Ververtex a vertex
	* Needs : None
	* Returns : void
	* Leads : add a Arc
	*******************************************************************************
	*/
	virtual void GROAddArc(CVertex& sVertexDep, CVertex& sVertexArr);

	/**
	*******************************************************************************
	* GRORemoveVertex
	* *****************************************************************************
	* Entries : snum a name of the vertex
	* Needs : None
	* Returns : void
	* Leads : remove the vertex which name is the value of snum
	*******************************************************************************
	*/
	void GRORemoveVertex(string& sNum);

	/**
	*******************************************************************************
	* GRORemoveVertex
	* *****************************************************************************
	* Entries : snumdep string  string snumarr
	* Needs : None
	* Returns : void
	* Leads : remove the arc whith the VertexDep value equals to the snumDep,the VertexArr value equals to the snumarr 
	*******************************************************************************
	*/
	virtual void GRORemoveArc(string& sNumdep, string& sNumArr);

	/**
	*******************************************************************************
	* GROCheckExistenceOfArc
	* *****************************************************************************
	* Entries : the vertexDep that will check the existence of the second vertex value
	* Needs : those vertex should be create before calling the function
	* Returns : bool
	* Leads : None
	*******************************************************************************
	*/
	bool GROCheckExistenceOfArc(CVertex& vertexDep, CVertex& vertexArr);
};
#endif 