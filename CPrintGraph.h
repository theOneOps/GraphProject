#ifndef _CPRINT_GRAPH_
#define _CPRINT_GRAPH_


#include "CGraph/CGraphOriented.h"
#include "CGraph/CGraphNOriented.h"
#include "CVertex/CVertex.h"
#include "CArc/Arc.h"

using namespace std;

class CPrintGraph
{
public:

	static void GROPrintGraph(CGraphOriented& graphA)
	{
		graphA.GROPrintGraph();
	}
	
};

#endif