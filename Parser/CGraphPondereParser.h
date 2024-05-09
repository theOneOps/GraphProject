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
class CGraphPondereParser : public Parser
{
public:


	/**
	*******************************************************************************
	* GPRAddVertex
	* *****************************************************************************
	* Entries : graph : CGraphOrient<SommetType, ArcType> representing the graph to fill with Vertices
	*			sSizeVertex : string representing the value of the name of the element size we want to read (eg: "Nbsommet" for "Nbsommet=2")
	*			sSectionName : string representing the name of the section to read plus the first delimiter of the section (eg:"Sommets" for "Sommets=[ numero = 2,  numero = 3]")
				sDelimiterEnd : string representing the last delimiter of the section (eg: "]" for "Sommets=[ numero = 2,  numero = 3]")
				VertexVariableName : string representing the value of the attribut that contains the value we're looking for (eg: "]" for "Sommets=[ numero = 2,  numero = 3]")
				sDelimiterBegin : string representing the delimiter at the beginning of an section (eg:"[" for "Sommets=[ numero = 2,  numero = 3]")
				sDelimiterEnd : string representing the delimiter at the ending of an section (eg:"]" for "Sommets=[ numero = 2,  numero = 3]")
				sDelimiterAffectation : string representing the affectation sign used for the section (eg:"=" for "Sommets=[ numero = 2,  numero = 3]")

	* Needs : None
	* Returns : void
	* Leads : add some Vertices to the graph with values read from the file
	*******************************************************************************
	*/
	void GPRAddVertex(CGraphOrient<SommetType, ArcType>*& graph, const string& sSizeVertex, const string& sSectionName, const string& VertexVariableName = "numero", const string& sDelimiterBegin = "[", const string& sDelimiterEnd = "]", const string& sDelimiterAffectation = "=")
	{
		// we get accessed to each line of the section (which means each element that contains the value of the vertex to create)
		vector<string> allVerticesSection = PARAnalyzeSection(sSectionName, sDelimiterAffectation, sDelimiterBegin, sDelimiterEnd);

		int size;
		if (!sDelimiterAffectation.empty())
		{
			string res = PARAnalyzeSectionElement(PARGetLineContains(sSizeVertex), sSizeVertex, sDelimiterAffectation);
			if (!res.empty())
			{
				// by a for loop, we check if all characters of the res's value are digits, 
				for (char c : res)
				{

					if (!isdigit(c))
					{
						// if not, we throw an exception
						string error_message = "the size of the " + sSizeVertex + " is not fully numeric";
						throw CException(value_not_numeric, error_message, "CGraphPondereParser.h", 57);
					}

				}
				// if yes, we convert it to integer
				size = stoi(res);
			}
			else
			{
				res = "there is no size defined for the " + sSizeVertex;
				throw CException(size_not_defined, res, "CGraphPondereParser.h", 57);
			}
		}
		else
			throw CException(the_number_of_vertex_not_found, "Error on finding the number of the vertex to create", "CGraphPondereParser.h", 53);




		if (size > allVerticesSection.size())
			throw CException(size_not_conformed, "the number of Vertices you want to create is greater than the number of Vertices that is actually defined in your file.txt", "CGraphPondereParser.h", 67);

		string vertexValue = "";
		// then we iterate over those lines and we parse them to find the value of the vertex to create
		for (int i = 0; i < size; i++)
		{
			vertexValue = PARAnalyzeSectionElement(allVerticesSection[i], VertexVariableName, sDelimiterAffectation);

			// we first check if the value is not a composed value
			if (PARContainsSpaceOrTab(vertexValue))
			{
				// it yes, we throw an exception
				throw CException(composed_value, "the vertex should not be a composed value", "CGraphPondereParser.h", 97);
			}
			// if not, this line created the vertex with the value "vertexValue" in the graph
			graph->GROAddVertex(vertexValue);
		}
	}



	void GPRAddArc(CGraphOrient<SommetType, ArcType>*& graph, const string& sSizeArcs, const string& sSectionName, const vector<string>& ArcsVariableName,
		const string& sDelimiterBegin = "[", const string& sDelimiterEnd = "]", const string& sDelimiterAffectation = "=", const string& sDelimiterBetweenArcsValuesNames = ",")
	{
		// we get accessed to lines that describes the arcs to create
		vector<string> allArcsSection = PARAnalyzeSection(sSectionName, sDelimiterAffectation, sDelimiterBegin, sDelimiterEnd);
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
			string res = PARAnalyzeSectionElement(PARGetLineContains(sSizeArcs), sSizeArcs, sDelimiterAffectation);
			if (!res.empty())
			{
				for (char c : res)
				{
					// by a for loop, we check if all characters of the res's value are digits, 
					if (!isdigit(c))
					{
						// if not, we throw an exception
						string error_message = "the size of the " + sSizeArcs + " is not fully numeric";
						throw CException(value_not_numeric, error_message, "CGraphPondereParser.h", 138);
					}

				}
				// if yes, we convert it to integer
				size = stoi(res);
			}
			else
			{
				res = "there is no size defined for the " + sSizeArcs;
				throw CException(size_not_defined, res, "CGraphPondereParser.h", 133);
			}
		}

		if (size > allArcsSection.size())
			throw CException(size_not_conformed, "the number of arcs you want to create is greater than the number of arcs that is actually defined in your file.txt", "CGraphPondereParser.h", 156);

		// then with a for loop, we parse each line to have the dep value and arr value of each arc
		for (unsigned int i = 0; i < size; i++)
		{
			pos = allArcsSection[i].find(sDelimiterBetweenArcsValuesNames);
			sDebArc = PARAnalyzeSectionElement(allArcsSection[i].substr(0, pos), ArcsVariableName[0]);
			current_pos = allArcsSection[i].find(sDelimiterBetweenArcsValuesNames, pos);
			sArrArc = PARAnalyzeSectionElement(allArcsSection[i].substr(pos, current_pos), ArcsVariableName[1]);
			finalPos = allArcsSection[i].find_last_of(sDelimiterBetweenArcsValuesNames);
			sArrWeight = PARAnalyzeSectionElement(allArcsSection[i].substr(finalPos, allArcsSection[i].size()), ArcsVariableName[2]);

			if (PARContainsSpaceOrTab(sDebArc) || PARContainsSpaceOrTab(sArrArc))
				throw CException(composed_value, "one (or more) of the values of your arcs contain spaces or tabs, correct them !", "CGraphPondereParser.h", 167);

			graph->GROAddArc(sDebArc, sArrArc);

			cout << "le poids pour l'arc de dep " << sDebArc << " et de arr " << sArrArc << " est " << "[" << sArrWeight << "]" << endl;

			// We set the weight to the arc
			graph->GROGetArcFromKeys(sDebArc, sArrArc)->ARCSetWeight(stoi(sArrWeight));
		}
	}

	/**
	*******************************************************************************
	* GPRMain
	* *****************************************************************************
	* Entries : tree : sfileName : string representing the file to read/parse
	* Needs : None
	* Returns : void
	* Leads : read a file .txt, create the specified graph, print it, invert it and print it again
	*******************************************************************************
	*/
	void GPRMain(const string& sfileName, const string& source)
	{

		// we create the specified graph
		CGraphOrient<SommetType, ArcType>* graph = new CGraphOrient<SommetType, ArcType>();

		try
		{
			// first, we read the file
			PARReadFile(sfileName);

			// we add all Vertices sepcified by the file
			GPRAddVertex(graph, "NBSommets", "Sommets");

			vector<string> vect;

			vect.push_back("debut");
			vect.push_back("fin");
			vect.push_back("Poids");

			// we add all arcs specified by the file
			GPRAddArc(graph, "NBArcs", "Arcs", vect);

			// we print the graph
			CPrintGraph::PRIPrintGraph(*graph);

			//CShortestPathDjistra<SommetType, ArcType>::SDRGetShortestPathDjistra(*graph, source);

			CShortestPathDjistra::SPDGetShortestPathDjistra(*graph, source);

			delete graph;
		}
		catch (CException e)
		{
			delete graph;
			e.EXCReadMessage();
		}
	}

};

#endif // !CGRAPH_PONDERE_PARSER_H

