#ifndef _CGRAPH_ORIENTE_H
#define _CGRAPH_ORIENTE_H
#include <string>
#include <map>
#include <set>
#include <vector>
#include "../CArc/Arc.h"
#include "../CVertex/CVertex.h"

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
	* Entries : sVertexDep : CVertex* which represents the beginning of the arc
	*		and sVertexArr : CVertex* which represents the end of the arc
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
	* Entries : sNum : string is the name of the vertex
	* Needs : None
	* Returns : void
	* Leads : remove the vertex which name is the value of snum
	*******************************************************************************
	*/
	void GRORemoveVertex(const string& sNum);

	/**
	*******************************************************************************
	* GRORemoveArc
	* *****************************************************************************
	* Entries : sNumdep : string which represents the name of the arc's beginning
	*		and sNumArr : string which represents the name of the arc's end
	* Needs : None
	* Returns : void
	* Leads : remove the arc which the sNumdep value equals to the snumDep,
				the VertexArr value equals to the sNumArr 
	*******************************************************************************
	*/
	virtual void GRORemoveArc(const string& sNumdep, const string& sNumArr);

	/**
	*******************************************************************************
	* GROinverseArc
	* *****************************************************************************
	* Entries : sNumdep : string which represents the name of the arc's beginning
	*		and sNumArr : string which represents the name of the arc's end
	* Needs : None
	* Returns : void
	* Leads : the arc will be inverse, basically the beginning of the vertex become 
		the end of the arc and vice versa
	*******************************************************************************
	*/
	void GROInverseArc(const string& valueDep, const string& valueArr);

	/**
	*******************************************************************************
	* GROInverseAllArcs
	* *****************************************************************************
	* Entries : None
	* Needs : None
	* Returns : void
	* Leads : all the arcs of the graph will be inverse
	*******************************************************************************
	*/
	void GROInverseAllArcs();

	/**
	*******************************************************************************
	* getGROVertex
	* *****************************************************************************
	* Entries : None
	* Needs : None
	* Returns : const map<string, CVertex*>
	* Leads : Return the map that contains all the vertex of the graph
	*******************************************************************************
	*/
	map<string, CVertex*> getGROVertex() const;

	/**
	*******************************************************************************
	* getGROArcs
	* *****************************************************************************
	* Entries : None
	* Needs : None
	* Returns : const map<string, vector<CArc*>>
	* Leads : Return the map that contains all the vertex of the graph
	*******************************************************************************
	*/
	map<string, vector<CArc*>> getGROArcs() const;

	void printArc();
	
protected:

	/**
	*******************************************************************************
	* GROAddArcInTheMap
	* *****************************************************************************
	* Entries : the key: const string& which represents the key which
				the arc:(CArc*) will be insert into
	* Needs : None
	* Returns : void
	* Leads : the arc will be insert into the map mGROVertex with at the key's value
	*******************************************************************************
	*/
	void GROAddArcInTheMap(const string& key, CArc* arc);

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

	vector<CArc*>& getGROArcsAtIndex(string value);


};
#endif 