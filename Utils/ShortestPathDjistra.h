#ifndef SHORTEST_PATH_DJISTRA
#define SHORTEST_PATH_DJISTRA

#include <limits>
#include <utility> 
#include "../CGraph/CGraphOrient.h"
#include "../PrintGraph/CPrintGraph.h"


// This structure represents the return values of Dijkstra's algorithm.
typedef struct
{
	unordered_map<string, string> pred; // This attribute stores the predecessors of the vertices, where the key is the vertex and the value is the predecessor of that vertex.
	unordered_map<string, unsigned int> distanceFromStartOfAllNodes; // This attribute stores the distances from the source vertex, where the key is the vertex and the value is the distance from the source vertex.
} pred_distance_djistra;

typedef struct initialUnits
{
	unordered_map<string, unsigned int> distanceFromStartOfAllNodes;
	vector<string> vNodeNotVisited;
	unordered_map<string, bool> mNodeVisited;
}initialUnits;


using namespace std;


class CShortestPathDjistra
{
private:

	/**
	*******************************************************************************
	* areThereUnvisitedNodes
	* *****************************************************************************
	* Entries: 
	*    mNodeVisited : unordered_map<string, bool> :  map where the keys represent the vertices of the graph and the
		 values indicate whether a vertex has been visited (true) or not (false).
	* Needs : None
	* Returns : void
	* Leads :return true if there is still some unvisited Nodes, unless false
	*******************************************************************************
	*/
	static bool areThereUnvisitedNodes(unordered_map<string, bool>& mNodeVisited)
	{
		// we initialize an iterator to go through the unordered_map
		unordered_map<string, bool>::iterator it = mNodeVisited.begin();

		// we iterate through the unordered_map
		for (; it != mNodeVisited.end(); it++)
		{
			// if there is a node which has not been visited yet, that means the it->second is equals to "false"
			if (!it->second)
				return false;

		}

		return true;
	}

	/**
	*******************************************************************************
	* isVectNodeVisitedEmpty
	* *****************************************************************************
	* Entries : unordered_map<string, bool>& mNodeVisited :
	* Needs : None
	* Returns : void
	* Leads :return true if there is no  visited Nodes, unless false
	*******************************************************************************
	*/
	static bool isVectNodeVisitedEmpty(unordered_map<string, bool>& mNodeVisited)
	{
		// we initialize an iterator to go through the unordered_map
		unordered_map<string, bool>::iterator it = mNodeVisited.begin();

		// we iterate through the unordered_map
		for (; it != mNodeVisited.end(); it++)
		{
			// if there is a node which has not been visited yet, that means the it->second is equals to "false"
			if (it->second)
				return false;
		}

		return true;
	}


	/**
	*******************************************************************************
	* SPDMAJVecOfVerteciesNotVisited
	* *****************************************************************************
	* Entries : unordered_map<string, bool>& mNodeVisited 
	* Needs : None
	* Returns : const vector<string>
	* Leads : return a container vector of string, which elements represents the values of the vertex which 'have not been visited' yet
	*******************************************************************************
	*/
	static const vector<string> SPDMAJVecOfVerteciesNotVisited(unordered_map<string, bool>& mNodeVisited)
	{
		// first, we create an iterator to iterate through the unordered_map
		unordered_map<string, bool>::iterator nodeVisitedIt = mNodeVisited.begin();

		vector<string> vNodeNotVistedRefreshed;

		for (; nodeVisitedIt != mNodeVisited.end(); nodeVisitedIt++)
		{
			// if there is a node which has not been visited yet, that means the it->second is equals to "false"
			if (!nodeVisitedIt->second)
				vNodeNotVistedRefreshed.push_back(nodeVisitedIt->first);
		}

		return vNodeNotVistedRefreshed;
	}

	/**
	*******************************************************************************
	* SPDFindMinWeight
	* *****************************************************************************
	* Entries : unordered_map<string:
		unsigned int> distanceFromStartOfAllNodes: 
		const vector<string>& vNodeNotVisited:
	* Needs : None
	* Returns : cosnt string
	* Leads : the value of the node having the minimum distance among the set of unvisited nodes
	*******************************************************************************
	*/
	static const string MinNodeDistance(unordered_map<string, unsigned int> distanceFromStartOfAllNodes, const vector<string>& vNodeNotVisited)
	{
		// first we declare the value of the node which has the min distance to return
		string sNameNodeMin;

		// now, the min current distance of the current node
		// we want the min distance, so by putting the current_distance to infinite, we make sure that the iValNodeMin will eventually be equald to a min value unelss all distances are equals to infinite...
		unsigned int iValNodeMin = numeric_limits<int>::min();

		// we iterate throw the unvisited node container
		for (const string sCurrentVertex : vNodeNotVisited)
		{
			// we compare the last min value to the distance of the current Node
			if (iValNodeMin > distanceFromStartOfAllNodes[sCurrentVertex])
			{
				// we find one, we update the values of 'sNameNodeMin' and the 'iValNodeMin'
				iValNodeMin = distanceFromStartOfAllNodes[sCurrentVertex];
				sNameNodeMin = sCurrentVertex;
			}
		}

		return sNameNodeMin;
	}


	/**
	*******************************************************************************
	* SPDPrintPredecessors
	* *****************************************************************************
	* Entries : const string& sVerDep:
		const string& finalMinVertex : 
		unordered_map<string, string>& pred : 
	* Needs : None
	* Returns : void
	* Leads : Print the predecessors of each node of the graph
	*******************************************************************************
	*/
	static void SPDPrintPredecessors(const string& sVerDep, unordered_map<string, string>& pred)
	{
		cout << "predecessors' views " << endl;

		cout << "vertex" << " -> " << "predecessor" << endl;

		unordered_map<string, string>::iterator predIt = pred.begin();

		for (; predIt != pred.end(); predIt++)
			cout << predIt->first << " : " << predIt->second << endl;
	}


	/**
	*******************************************************************************
	* SPDPrintMinDistanceFromVertexDepOfAllNodes
	* *****************************************************************************
	* Entries : unordered_map<string :
		unsigned int> distanceFromStartOfAllNodes:
		const string& sVerDep:
	* Needs : None
	* Returns : void
	* Leads :  Print the minimal distance from the source for each node of the graph
	*******************************************************************************
	*/
	static void SPDPrintMinDistanceFromVertexDepOfAllNodes(unordered_map<string, unsigned int> distanceFromStartOfAllNodes, const string& sVerDep)
	{
		cout << "display of the minimum distance which separates the starting node "  << sVerDep <<  " from the currentNode" << endl;

		unordered_map<string, unsigned int>::iterator nodesIt = distanceFromStartOfAllNodes.begin();

		cout << "vertex" << " -> " << "minimal distance" << endl;

		for (; nodesIt != distanceFromStartOfAllNodes.end(); nodesIt++)
		{
			cout << nodesIt->first << " -> " << nodesIt->second << endl;
		}
	}


	/**
	*******************************************************************************
	* SPDInitializeValues
	* *****************************************************************************
	* Entries : CGraphOrient<SommetType, ArcType>& graph :
		const string& sVerDep : 
	* Needs : None
	* Returns : initialUnits
	* Leads : return a initialUnits struct which contains all values that will be used for the dijkstra's algorithm
	*******************************************************************************
	*/
	template<typename SommetType, typename ArcType>
	static initialUnits SPDInitializeValues(CGraphOrient<SommetType, ArcType>& graph,
		const string& sVerDep)
	{
		initialUnits units;

		unordered_map<string, SommetType*> VerticesMap = graph.GROGetVertexMap();
		typename unordered_map<string, SommetType*>::iterator it = VerticesMap.begin();

		for (; it != VerticesMap.end(); it++)
		{
			// the distance of the source is put to 0
			if (sVerDep == it->first)
				units.distanceFromStartOfAllNodes[it->first] = 0;
			else // and the others, to infinite
			{
				units.distanceFromStartOfAllNodes[it->first] = numeric_limits<int>::max();
				units.vNodeNotVisited.push_back(it->first);
			}
			// we put false to mean that all node at the beginning of the dijkstra method, are unvisited
			units.mNodeVisited[it->first] = false;
		}
		return units;
	}



public:
	template<typename SommetType, typename ArcType>
	static pred_distance_djistra  SPDGetShortestPathDjistra(CGraphOrient<SommetType, ArcType>& graph, const string& sVerDep)
	{
		string sNameOfVertexWithMinWeight; // string qui contiendra à chque itération le noeud avec la plus petite distance parmi les noeuds non visités
		unsigned int MinNodeWeight = 0; // la distance du noeud minimale depuis le sommet de départ

		set<string> adjacentsValuesToSVerDep;

		unordered_map<string, string> pred;

		vector<string> priorityNodes;

		initialUnits InitialValues = SPDInitializeValues(graph, sVerDep);
		
		unordered_map<string, unsigned int> distanceFromStartOfAllNodes = InitialValues.distanceFromStartOfAllNodes;
		unordered_map<string, bool> mNodeVisited = InitialValues.mNodeVisited;
		vector<string> vNodeNotVisited = InitialValues.vNodeNotVisited; // vector contenant les noeuds non visités


		unordered_map<string, SommetType*> verticesMap = graph.GROGetVertexMap();
		typename unordered_map<string, SommetType*>::iterator it = verticesMap.begin();

		// we initialize the predecessors container by st=etting every value to none
		for (; it != verticesMap.end(); it++)
		{
			pred[it->first] = "none";
		}

		// Loop as long as there are unvisited nodes remaining
		while (!areThereUnvisitedNodes(mNodeVisited))
		{

			unordered_map<string, SommetType*> VerticesMap = graph.GROGetVertexMap();

			if (isVectNodeVisitedEmpty(mNodeVisited)) // If no node is visited, we start with the starting node (the source : sVerDep)
				sNameOfVertexWithMinWeight = sVerDep;
			else // Determine the vertex with the minimum weight among those not visited
				sNameOfVertexWithMinWeight = MinNodeDistance(distanceFromStartOfAllNodes, vNodeNotVisited);

			// get adjacents vertecies of the min Node "sNameOfVertexWithMinWeight"
			adjacentsValuesToSVerDep = (VerticesMap[sNameOfVertexWithMinWeight])->VERGetAllAdjacentsOutVertecies();

			// we store the current minimum weight for the vertex in question
			MinNodeWeight = distanceFromStartOfAllNodes[sNameOfVertexWithMinWeight];

			// If the minimum weight is infinite ( which means that there is no path)
			if (MinNodeWeight == numeric_limits<int>::max())
				break; // we stop the loop

			// we add the vertex with the minimum weight to the list of priority nodes
			priorityNodes.push_back(sNameOfVertexWithMinWeight);


			//Update the distances of the neightbors of the minimum node
			for (string sCurrentVertex : adjacentsValuesToSVerDep)
			{
				unsigned int currentDistance;
				// Check if the current vertex has not yet been visited
				if (mNodeVisited[sCurrentVertex] == false)
				{
					// we calculate the new possible distance, by first checking the existence of an arc
					if (graph.GROExistenceOfArcNOriented(sCurrentVertex, sNameOfVertexWithMinWeight))
						currentDistance = MinNodeWeight + graph.GROGetWeightOFArc(sCurrentVertex, sNameOfVertexWithMinWeight);
					else
						currentDistance = MinNodeWeight + graph.GROGetWeightOFArc(sNameOfVertexWithMinWeight, sCurrentVertex);

					// If the new distance is less than the current saved distance, updates the distance and predecessor
					if (currentDistance < distanceFromStartOfAllNodes[sCurrentVertex])
					{
						distanceFromStartOfAllNodes[sCurrentVertex] = currentDistance;
						pred[sCurrentVertex] = priorityNodes.back(); // Update the predecessor with the last vertex with the min weight we found at the current time
					}
				}
			}

			// current minimum node marking
			// if the node is marking, then it can be visited or updated again
			mNodeVisited[sNameOfVertexWithMinWeight] = true;

			// update the container that contains the node not visited 
			vNodeNotVisited = SPDMAJVecOfVerteciesNotVisited(mNodeVisited);
		}

		pred_distance_djistra values;

		values.pred = pred;

		values.distanceFromStartOfAllNodes = distanceFromStartOfAllNodes;

		// display of the minimum distance which separates the starting node from the currentNode
		SPDPrintMinDistanceFromVertexDepOfAllNodes(values.distanceFromStartOfAllNodes, sVerDep);

		// Print the predecessors of nodes that formed a route to the SverDep
		SPDPrintPredecessors(sVerDep, values.pred);

		return values;
		
	}
};


#endif // SHORTEST_PATH
