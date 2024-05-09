#ifndef SHORTEST_PATH_DJISTRA
#define SHORTEST_PATH_DJISTRA

#include <limits>
#include <utility> 
#include "../CGraph/CGraphOrient.h"
#include "../PrintGraph/CPrintGraph.h"

using namespace std;


class CShortestPathDjistra
{
private:



	// fonction pour vérifier s'il y a encore des noeuds non visités
	static bool areThereUnvisitedNodes(unordered_map<string, bool>& mNodeVisited)
	{
		unordered_map<string, bool>::iterator it = mNodeVisited.begin();

		for (; it != mNodeVisited.end(); it++)
		{
			if (!it->second)
				return false;

		}

		return true;
	}

	// fonction pour vérifier s'il y a au moins un noeud qui a déjà été visité
	static bool isVectNodeVisitedEmpty(unordered_map<string, bool>& mNodeVisited)
	{
		unordered_map<string, bool>::iterator it = mNodeVisited.begin();

		for (; it != mNodeVisited.end(); it++)
		{
			if (it->second)
				return false;
		}

		return true;
	}

	// mise à jour des noeuds non visités
	static const vector<string> SPDMAJVecOfVerteciesNotVisited(unordered_map<string, bool>& mNodeVisited)
	{
		unordered_map<string, bool>::iterator nodeVisitedIt = mNodeVisited.begin();

		vector<string> vNodeNotVistedRefreshed;

		for (; nodeVisitedIt != mNodeVisited.end(); nodeVisitedIt++)
		{
			if (!nodeVisitedIt->second)
				vNodeNotVistedRefreshed.push_back(nodeVisitedIt->first);
		}

		return vNodeNotVistedRefreshed;
	}

	// fonction pour déterminer le noeud ayant la distance minimale parmi l'ensemble des nœuds non visités
	static const string SPDFindMinWeight(unordered_map<string, unsigned int> distanceFromStartOfAllNodes, const vector<string>& vNodeNotVisited)
	{
		string sNameNodeMin;
		unsigned int iValNodeMin = numeric_limits<int>::min();


		for (const string sCurrentVertex : vNodeNotVisited)
		{

			if (iValNodeMin > distanceFromStartOfAllNodes[sCurrentVertex])
			{
				iValNodeMin = distanceFromStartOfAllNodes[sCurrentVertex];
				sNameNodeMin = sCurrentVertex;
			}
		}

		return sNameNodeMin;
	}

	static void SPDPrintPredecessors(const string& sVerDep, const string& finalMinVertex, unordered_map<string, string>& pred)
	{
		cout << "affichage des predecesseurs " << endl;
		unordered_map<string, string>::iterator predIt = pred.begin();

		for (; predIt != pred.end(); predIt++)
			cout << predIt->first << " : " << predIt->second << endl;
	}

	static void SPDPrintMinDistanceFromVertexDepOfAllNodes(unordered_map<string, unsigned int> distanceFromStartOfAllNodes)
	{
		cout << "display of the minimum distance which separates the starting node from the currentNode" << endl;

		unordered_map<string, unsigned int>::iterator nodesIt = distanceFromStartOfAllNodes.begin();

		for (; nodesIt != distanceFromStartOfAllNodes.end(); nodesIt++)
		{
			cout << nodesIt->first << " -> " << nodesIt->second << endl;
		}
	}

	template<typename SommetType, typename ArcType>
	static pair< pair<unordered_map<string, unsigned int>, vector<string>>, unordered_map<string, bool>> SPDInitializeValues(CGraphOrient<SommetType, ArcType>& graph,
		const string& sVerDep)
	{

		unordered_map<string, unsigned int> distanceFromStartOfAllNodes;
		unordered_map<string, bool> mNodeVisited;
		vector<string> vNodeNotVisited; // vector contenant les noeuds non visités


		unordered_map<string, SommetType*> VerticesMap = graph.GROGetVertexMap();
		typename unordered_map<string, SommetType*>::iterator it = VerticesMap.begin();

		for (; it != VerticesMap.end(); it++)
		{
			if (sVerDep == it->first)
				distanceFromStartOfAllNodes[it->first] = 0;
			else
			{
				distanceFromStartOfAllNodes[it->first] = numeric_limits<int>::max();
				vNodeNotVisited.push_back(it->first);
			}

			mNodeVisited[it->first] = false;
		}

		//return make_tuple(distanceFromStartOfAllNodes, vNodeNotVisited, mNodeVisited);

		return make_pair(make_pair(distanceFromStartOfAllNodes, vNodeNotVisited), mNodeVisited);
	}

	template<typename SommetType, typename ArcType>
	static void SPDUpdateNeighborDistances(CGraphOrient<SommetType, ArcType>& graph, unordered_map<string, bool> mNodeVisited, unordered_map<string,
		unsigned int>& distanceFromStartOfAllNodes, const string& sNameOfVertexWithMinWeight, unordered_map<string, string>& pred,
		unsigned int MinNodeWeight, vector<string> priorityNodes, set<string>& adjacentsValuesToSVerDep)
	{
		for (string sCurrentVertex : adjacentsValuesToSVerDep)
		{
			unsigned int currentDistance;

			if (mNodeVisited[sCurrentVertex] == false)
			{
				if (graph.GROExistenceOfArcNOriented(sCurrentVertex, sNameOfVertexWithMinWeight))
					currentDistance = MinNodeWeight + graph.GROGetWeightOFArc(sCurrentVertex, sNameOfVertexWithMinWeight);
				else
					currentDistance = MinNodeWeight + graph.GROGetWeightOFArc(sNameOfVertexWithMinWeight, sCurrentVertex);

				if (currentDistance < distanceFromStartOfAllNodes[sCurrentVertex])
				{
					distanceFromStartOfAllNodes[sCurrentVertex] = currentDistance;
					pred[sCurrentVertex] = priorityNodes.back();
				}
			}
		}

	}

public:
	template<typename SommetType, typename ArcType>
	static void SPDGetShortestPathDjistra(CGraphOrient<SommetType, ArcType>& graph, const string& sVerDep)
	{
		string sNameOfVertexWithMinWeight; // string qui contiendra à chque itération le noeud avec la plus petite distance parmi les noeuds non visités
		unsigned int MinNodeWeight = 0; // la distance du noeud minimale depuis le sommet de départ

		set<string> adjacentsValuesToSVerDep;

		unordered_map<string, string> pred;

		vector<string> priorityNodes;

		pair< pair<unordered_map<string, unsigned int>, vector<string>>, unordered_map<string, bool>> InitialValue = SPDInitializeValues(graph, sVerDep);
		
		unordered_map<string, unsigned int> distanceFromStartOfAllNodes = InitialValue.first.first;
		unordered_map<string, bool> mNodeVisited = InitialValue.second;
		vector<string> vNodeNotVisited = InitialValue.first.second; // vector contenant les noeuds non visités


		unordered_map<string, SommetType*> VerticesMap = graph.GROGetVertexMap();
		typename unordered_map<string, SommetType*>::iterator it = VerticesMap.begin();

		for (; it != VerticesMap.end(); it++)
		{
			pred[it->first] = "none";
		}

		while (!areThereUnvisitedNodes(mNodeVisited))
		{
			unordered_map<string, SommetType*> VerticesMap = graph.GROGetVertexMap();

			if (isVectNodeVisitedEmpty(mNodeVisited))
				sNameOfVertexWithMinWeight = sVerDep;
			else
				sNameOfVertexWithMinWeight = SPDFindMinWeight(distanceFromStartOfAllNodes, vNodeNotVisited);

			// get adjacents vertecies of the min Node "sNameOfVertexWithMinWeight"
			adjacentsValuesToSVerDep = (VerticesMap[sNameOfVertexWithMinWeight])->VERGetAllAdjacentsOutVertecies();

			MinNodeWeight = distanceFromStartOfAllNodes[sNameOfVertexWithMinWeight];

			if (MinNodeWeight == numeric_limits<int>::max())
				break;

			priorityNodes.push_back(sNameOfVertexWithMinWeight);


			//Update the distances of the neightbors of the minimum node
			SPDUpdateNeighborDistances(graph, mNodeVisited, distanceFromStartOfAllNodes, sNameOfVertexWithMinWeight, pred, MinNodeWeight, priorityNodes, adjacentsValuesToSVerDep);

			// current minimum node marking
			// if the node is marking, then it can be visited or updated again

			mNodeVisited[sNameOfVertexWithMinWeight] = true;

			// update the container that contains the node not visited 
			vNodeNotVisited = SPDMAJVecOfVerteciesNotVisited(mNodeVisited);
		}

		// display of the minimum distance which separates the starting node from the currentNode
		SPDPrintMinDistanceFromVertexDepOfAllNodes(distanceFromStartOfAllNodes);

		// Print the predecessors of nodes that formed a route to the SverDep
		SPDPrintPredecessors(sVerDep , sNameOfVertexWithMinWeight, pred);
	}
};


#endif // SHORTEST_PATH
