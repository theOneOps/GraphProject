#ifndef CGRAPH_PONDERE_PARSER_H
#define CGRAPH_PONDERE_PARSER_H

#include "Parser.h"
#include "../CArc/ArcPondere.h"
#include "../Utils/ShortestPathDjistra.h"


/**********************************************************
*  Class : CGraphPondereParser management
* *********************************************************
* ROLE : parse a file txt, create the graph described in the file and finally returns:
* A pred table of vertex predecessors
* And an array of the lengths of the shortest paths between the source vertex and the index vertex
* *********************************************************
* VERSION: 1.0
* AUTHOR: Selly Bill-Gate MEDEWOU
		  Jeremie YANG
* DATE: 29/04/2024
* *********************************************************
*/
template<typename SommetType, typename ArcType>
class CGraphPondereParser : public CGraphParser<SommetType, ArcType>
{
private :

public : 

	// we just check if the type put in the class's type are what we are expected to have
	static_assert(is_base_of<CVertex, SommetType>::value, "SommetType needs to be a CVertex class or a derivate of CVertex's class");
	static_assert(is_base_of<CArcPondere, ArcType>::value, "ArcType needs to be a CArcPondere class or a derivate of CArcPondere's class");

	//using CGraphParser<SommetType, ArcType>::CGraphParser; // Inherit constructor if needed


		/**
	*******************************************************************************
	* GPRAddArc
	* *****************************************************************************
	* Entries :  graph : CGraphOrient<SommetType, ArcType> representing the graph to create arcs for
	*			sSizeArcs : string representing the value of the name of the element size we want to read (eg: "Nbarc" for "Nbarc=2")
	*			sSectionName : string representing the name of the section to read plus the first delimiter of the section (eg:"Arcs" for "Arcs=[2, 3]")
				ArcsVariableName: vector of strings representing the value of the attributs that contains the value we're looking for (eg: 'vector<>("Debut","Fin")' for "Arcs=[ Debut = 2, Fin = 3]")
				sDelimiterBegin : string representing the delimiter at the beginning of an section (eg:"[" for "Sommets=[ numero = 2,  numero = 3]")
				sDelimiterEnd : string representing the delimiter at the ending of an section (eg:"]" for "Sommets=[ numero = 2,  numero = 3]")
				sDelimiterAffectation : string representing the affectation sign used for the section (eg:"=" for "Sommets=[ numero = 2,  numero = 3]")
				sDelimiterBetweenArcsValuesNames : string representing the sign separating two values or more the section (eg:"," for "Sommets=[ numero = 2,  numero = 3]")
	* Needs : None
	* Returns : void
	* Leads : add some arcs to the graph with values dep and arr read from the file
	*******************************************************************************
	*/
	void GPRAddArc(CGraphOrient<SommetType, ArcType>*& graph, const string& sSizeArcs, const string& sSectionName, const vector<string>& ArcsVariableName,
		const string& sDelimiterBegin = "[", const string& sDelimiterEnd = "]", const string& sDelimiterAffectation = "=", const string& sDelimiterBetweenArcsValuesNames = ",")
	{
		// we get accessed to lines that describes the arcs to create
		vector<string> allArcsSection = CGraphParser<SommetType, ArcType>::PARAnalyzeSection(sSectionName, sDelimiterAffectation, sDelimiterBegin, sDelimiterEnd);
		// first, we read the number of arcs to create
		unsigned int size = 0;

		size_t pos;
		size_t current_pos;
		size_t finalPos;
		string sDebArc;
		string sArrArc;
		string sArrWeight;

		if (!sDelimiterAffectation.empty())
		{
			string res = CGraphParser<SommetType, ArcType>::PARAnalyzeSectionElement(CGraphParser<SommetType, ArcType>::PARGetLineContains(sSizeArcs), sSizeArcs, sDelimiterAffectation);
			if (!res.empty())
			{
				for (char c : res)
				{
					// by a for loop, we check if all characters of the res's value are digits, 
					if (!isdigit(c))
					{
						// if not, we throw an exception
						string error_message = "the size of the " + sSizeArcs + " is not fully numeric";
						throw CException(value_not_numeric, error_message, "CGraphPondereParser.h", 76);
					}

				}
				// if yes, we convert it to integer
				size = stoi(res);
			}
			else
			{
				res = "there is no size defined for the " + sSizeArcs;
				throw CException(size_not_defined, res, "CGraphPondereParser.h", 71);
			}
		}

		if (size > allArcsSection.size())
			throw CException(size_not_conformed, "the number of arcs you want to create is greater than the number of arcs that is actually defined in your file.txt", "CGraphPondereParser.h", 94);

		// then with a for loop, we parse each line to have the dep value and arr value of each arc
		for (unsigned int i = 0; i < size; i++)
		{
			pos = allArcsSection[i].find(sDelimiterBetweenArcsValuesNames);
			sDebArc = CGraphParser<SommetType, ArcType>::PARAnalyzeSectionElement(allArcsSection[i].substr(0, pos), ArcsVariableName[0]);
			current_pos = allArcsSection[i].find(sDelimiterBetweenArcsValuesNames, pos);
			sArrArc = CGraphParser<SommetType, ArcType>::PARAnalyzeSectionElement(allArcsSection[i].substr(pos, current_pos), ArcsVariableName[1]);
			finalPos = allArcsSection[i].find_last_of(sDelimiterBetweenArcsValuesNames);
			sArrWeight = CGraphParser<SommetType, ArcType>::PARAnalyzeSectionElement(allArcsSection[i].substr(finalPos, allArcsSection[i].size()), ArcsVariableName[2]);

			if (CGraphParser<SommetType, ArcType>::PARContainsSpaceOrTab(sDebArc) || CGraphParser<SommetType, ArcType>::PARContainsSpaceOrTab(sArrArc))
				throw CException(composed_value, "one (or more) of the values of your arcs contain spaces or tabs, correct them !", "CGraphPondereParser.h", 107);

			graph->GROAddArc(sDebArc, sArrArc);


			// we first check if the weight is not empty
			if (!sArrWeight.empty())
			{
				for (char c : sArrWeight)
				{
					// by a for loop, we check if all characters of the res's value are digits, 
					if (!isdigit(c))
					{
						// if not, we throw an exception
						string error_message = "the weight of the arc (" + sDebArc + " " + sArrArc
							+ ") is not fully a digit value";
						throw CException(value_not_numeric, error_message, "CGraphPondereParser.h", 119);
					}
				}
			}
			else
			{
				string errorMessage = "the weight of the arc (" + sDebArc + " " + sArrArc
					+ ") is not defined";
				throw CException(size_not_defined, errorMessage, "CGraphPondereParser.h", 114);
			}

			// We set the weight to the arc if it is a positive weight
			if (stoi(sArrWeight) >= 0)
				graph->GROGetArcFromKeys(sDebArc, sArrArc)->ARCSetWeight(stoi(sArrWeight));
			else
			{
				string errorMessage = "the weight of the arc (" + sDebArc + " "  +  sArrArc
					+ ") is not fully a positive number";
				throw CException(32, errorMessage, "CGraphPondereParser.h", 136);
			}

		}
	}


	void GPRMain(const string& sfileName) {}


	/**
	*******************************************************************************
	* GPPMain
	* *****************************************************************************
	* Entries : tree : sfileName : string representing the file to read/parse
	*			source : string representing the source to apply for the dijkstra's algorithm
	* Needs : None
	* Returns : void
	* Leads : read a file .txt, create the specified graph, print it, invert it and print it again
	*******************************************************************************
	*/
	pred_distance_djistra GPPMain(const string& sfileName, const string& source)
	{

		// we create the specified graph
		CGraphOrient<SommetType, ArcType>* graph = new CGraphOrient<SommetType, ArcType>();

		try
		{
			// first, we read the file
			CGraphParser<SommetType, ArcType>::PARReadFile(sfileName);

			// we add all Vertices sepcified by the file
			CGraphParser<SommetType, ArcType>::GPRAddVertex(graph, "NBSommets", "Sommets");

			vector<string> vect;

			vect.push_back("debut");
			vect.push_back("fin");
			vect.push_back("Poids");

			// we add all arcs specified by the file
			GPRAddArc(graph, "NBArcs", "Arcs", vect);

			// we print the graph
			CPrintGraph::PRIPrintGraph(*graph);

			if (graph->GROGetVertexMap().find(source) != graph->GROGetVertexMap().end())
			{
				pred_distance_djistra pred_distance_values = CShortestPathDjistra::SPDGetShortestPathDjistra(*graph, source);
				delete graph;
				return pred_distance_values;
			}
			else
			{
				string errorMessage = "the source " + source +  " given in parameter is not part of the graph's vertecies";
				throw CException(31, errorMessage, "CGraphPondereParser.h", 173);
			}
		}
		catch (CException&)
		{
			delete graph;
			throw;
		}
	}

};

#endif // !CGRAPH_PONDERE_PARSER_H

