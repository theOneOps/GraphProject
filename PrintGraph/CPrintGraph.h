#ifndef _CPRINT_GRAPH_
#define _CPRINT_GRAPH_


#include "../CGraph/CGraphOrient.h"
#include "../CGraph/CGraphNOrient.h"

using namespace std;

class CPrintGraph
{
public:

	template<typename SommetType, typename ArcType>
	static void PrintGraph(CGraphOrient<SommetType, ArcType>& graphA)
	{
		graphA.GROPrintGraph();
	}
	
	template<typename SommetType, typename ArcType>
	static void PrintGraph(CGraphNOrient<SommetType, ArcType>& graphA)
	{
		graphA.GROPrintGraph();
	}
};

#endif