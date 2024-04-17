#ifndef _CPRINT_GRAPH_
#define _CPRINT_GRAPH_


#include "../CGraph/CGraphOrient.h"
#include "../CGraph/CGraphNOrient.h"

using namespace std;

class CPrintGraph
{
public:



	/**
	*******************************************************************************
	* GROPrintGraph
	* *****************************************************************************
	* Entries : None
	* Needs : None
	* Returns : void
	* Leads : Print the graph into the console
	*******************************************************************************
	*/
	template<typename SommetType, typename ArcType>
	static void PRIPrintGraph(CGraphOrient<SommetType, ArcType>& graphA)
	{
		// we create an iterator on the GROVertex unordered_map 
		unordered_map<string, SommetType*> VerteciesMap = graphA.GROGetVertexMap();
		typename unordered_map<string, SommetType*>::iterator it = VerteciesMap.begin();

		for (; it != VerteciesMap.end(); it++)
		{
			// we print the value of the current vertex and then call the VERGetAllListOutVertecies's method of 
			// the current vertex which prints a string that contains all the vertecies's
			// values that have connections with our current vertex
			cout << it->first << " : " << it->second->VERGetAllListOutVertecies() << endl;
		}
	}
	

	/**
	*******************************************************************************
	* GROPrintGraph
	* *****************************************************************************
	* Entries : None
	* Needs : None
	* Returns : void
	* Leads : Print the graph into the console
	*******************************************************************************
	*/
	template<typename SommetType, typename ArcType>
	static void PRIPrintGraph(CGraphNOrient<SommetType, ArcType>& graphA)
	{
		unordered_map<string, SommetType*> VerteciesMap = graphA.GROGetVertexMap();
		typename unordered_map<string, SommetType*>::iterator it = VerteciesMap.begin();

		for (; it != VerteciesMap.end(); it++)
		{
			cout << it->first << " : " << it->second->VERPrintAdjacentNeightboors() << endl;
		}
	}
};

#endif