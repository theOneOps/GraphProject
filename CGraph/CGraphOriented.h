#ifndef _CGRAPH_ORIENTE_H
#define _CGRAPH_ORIENTE_H
#include <string>
#include <map>
#include <vector>
#include "../CArc/Arc.h"
#include "../CVertex/CVertex.h"
#include <set>

using namespace std;

#define vertex_already_existed 11
#define arc_already_existed 10
#define vertex_not_existed 9
#define arc_not_existed 8


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
	map<string, vector<CArc*>> mGROArcs;

public:

	//Constructors

	/**
	*******************************************************************************
	* CGraphOriented
	* *****************************************************************************
	* Entries : None
	* Needs : None
	* Returns : None
	* Leads : destroy the Vertex value of all the key for each map (mGROVertex, mGROArcs)
	*******************************************************************************
	*/
	~CGraphOriented();


	//Methods

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
	virtual void GROModifyVertex(const string& sVertexName, const string& sValue);

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
	void GROAddVertex(CVertex* VerVertex);

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
	virtual void GROAddArc(CVertex* sVertexDep, CVertex* sVertexArr);

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
	void GRORemoveVertex(const string& sNum);

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
	virtual void GRORemoveArc(const string& sNumdep, const string& sNumArr);

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
	virtual bool GROCheckExistenceOfArc(CVertex& vertexDep, CVertex& vertexArr);


	/**
	*******************************************************************************
	* GROinverseArc
	* *****************************************************************************
	* Entries : tree : BSTree* = the tree we want to compare with
	* Needs : None
	* Returns : void
	* Leads : Return description
	*******************************************************************************
	*/
	void GROInverseArc(const string& valueDep, const string& valueArr);

	/**
	*******************************************************************************
	* GROInverseAllArcs
	* *****************************************************************************
	* Entries : tree : BSTree* = the tree we want to compare with
	* Needs : None
	* Returns : void
	* Leads : Return description
	*******************************************************************************
	*/
	void GROInverseAllArcs();

	/**
	*******************************************************************************
	* getGROVertex
	* *****************************************************************************
	* Entries : tree : BSTree* = the tree we want to compare with
	* Needs : None
	* Returns : void
	* Leads : Return description
	*******************************************************************************
	*/
	map<string, CVertex*> getGROVertex() const;
	
protected:
	/**
	*******************************************************************************
	* GROAddArcInTheMap
	* *****************************************************************************
	* Entries : tree : BSTree* = the tree we want to compare with
	* Needs : None
	* Returns : void
	* Leads : Return description
	*******************************************************************************
	*/
	void GROAddArcInTheMap(const string& key, CArc* arc);
};
#endif 