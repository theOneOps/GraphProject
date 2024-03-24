#ifndef _GRAPH_ORIENTED_H
#define _GRAPH_ORIENTED_H

#include "CGraphOriented.h"

class CGraphNOriented:public CGraphOriented
{
public:

	//Constructors 
	CGraphNOriented(): CGraphOriented() {};
	~CGraphNOriented() {};

	// Methods
	
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
	* Entries : snumdep string  string snumarr
	* Needs : None
	* Returns : void
	* Leads : remove the arc whith the VertexDep value equals to the snumDep,the VertexArr value equals to the snumarr
	*******************************************************************************
	*/
	virtual void GRORemoveArc(string& sNumdep, string& sNumArr);

	virtual bool GROCheckExistenceOfArc(CVertex& vertexDep, CVertex& vertexArr);
	
	//virtual void GROModifyVertex(const string& sVertexName, const string& sValue);
};

#endif