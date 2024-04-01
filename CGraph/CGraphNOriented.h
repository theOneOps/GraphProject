#ifndef _CGRAPH_NORIENTE_H
#define _CGRAPH_NORIENTE_H

#include "CGraphOriented.h"

class CGraphNOriented : public CGraphOriented
{
public:

	CGraphNOriented();

	virtual void GROAddArc(const string& sVertexDep, const string& sVertexArr);

	virtual void GRORemoveArc(const string& sVertexDep, const string& sVertexArr);

	virtual void GROModifyVertex(const string& sVertexOldValue, const string& sVertexNewValue);

	virtual void GROInverserArc(const string& sVertexDep, const string& sVertexArr) {};

	virtual void GROInverserAllArcs() {};

	virtual void GRORemoveVertex(const string& key);

	virtual void GROPrintGraph();
};


#endif
