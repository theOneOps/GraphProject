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
	* Entries : the graph to print
	* Needs : None
	* Returns : void
	* Leads : Print the graph into the console
	*******************************************************************************
	*/
	template<typename SommetType, typename ArcType>
	static void PRIPrintGraph(CGraphOrient<SommetType, ArcType>& graphA)
	{
		// we create an iterator on the GROVertex unordered_map 
		unordered_map<string, SommetType*> VerticesMap = graphA.GROGetVertexMap();
		typename unordered_map<string, SommetType*>::iterator it = VerticesMap.begin();

		for (; it != VerticesMap.end(); it++)
		{
			// we print the value of the current vertex and then call the VERGetAllListOutVertices's method of 
			// the current vertex which prints a string that contains all the Vertices's
			// values that have connections with our current vertex
			cout << it->first << " : " << it->second->VERGetAllListOutVertices() << endl;
		}
	}
	

	/**
	*******************************************************************************
	* GROPrintGraph
	* *****************************************************************************
	* Entries : the graph to print
	* Needs : None
	* Returns : void
	* Leads : Print the graph into the console
	*******************************************************************************
	*/
	template<typename SommetType, typename ArcType>
	static void PRIPrintGraph(CGraphNOrient<SommetType, ArcType>& graphA)
	{
		unordered_map<string, SommetType*> VerticesMap = graphA.GROGetVertexMap();
		typename unordered_map<string, SommetType*>::iterator it = VerticesMap.begin();

		for (; it != VerticesMap.end(); it++)
		{
			cout << it->first << " : " << it->second->VERPrintAdjacentNeightboors() << endl;
		}
	}


	/**
	*******************************************************************************
	* PRIPrintAllVertices
	* *****************************************************************************
	* Entries : the graph whose vertices will be print
	* Needs : None
	* Returns : void
	* Leads : Print all the Vertices of the graph into the console
	*******************************************************************************
	*/
	template<typename SommetType, typename ArcType>
	static void PRIPrintAllVertices(CGraphOrient<SommetType, ArcType>& graphA)
	{
		// to print all Vertices of the graph, we just have to iterate on the unordered_map mGROVertex 
		// that contains all Vertices of the graph
		unordered_map<string, SommetType*> VerticesMap = graphA.GROGetVertexMap();
		typename unordered_map<string, SommetType*>::iterator it = VerticesMap.begin();

		for (; it != VerticesMap.end(); it++)
		{
			// and we just print the key of the current record vertex (the key is the value of the vertex)
			cout << it->first << endl;
		}
	}


};

#endif