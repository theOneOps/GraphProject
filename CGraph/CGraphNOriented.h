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

	virtual void GROAddArc(CVertex* sVertexDep, CVertex* sVertexArr);

	virtual void GRORemoveArc(const string& sNumdep, const string& sNumArr);

};

#endif