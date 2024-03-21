#ifndef _CPRINT_GRAPH_
#define _CPRINT_GRAPH_


#include "CGraph/CGraphOriented.h"
#include "CVertex/CVertex.h"
#include "CArc/Arc.h"

using namespace std;

class CPrintGraph
{
public:

	static void GROPrintGraph(const CGraphOriented* graphA)
	{
		const map<string, CVertex*> vertexes = graphA->getGROVertex();
		map<string, CVertex*>::const_iterator it = vertexes.begin();
		for (; it != vertexes.end(); it++)
		{
			cout << it->first + ": " << it->second->printAdjacentNeightboors() << endl;
		}
	}
};

#endif