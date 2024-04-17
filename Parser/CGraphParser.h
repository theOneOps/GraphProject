#ifndef CGRAPH_PARSER_H
#define CGRAPH_PARSER_H

#include "Parser.h"
#include "../CArc/Arc.h"
#include "../CVertex/CVertex.h"
#include "../CGraph/CGraphNOrient.h"
#include "../CGraph/CGraphOrient.h"
#include "../PrintGraph/CPrintGraph.h"

#include <cctype>

#define size_not_conformed 25
#define size_not_defined 26
/**********************************************************
*  Class : CGraphParser management
* *********************************************************
* ROLE : parse a file txt, and created the graph described in the file
* *********************************************************
* VERSION: 1.0
* AUTHOR: Selly Bill-Gate MEDEWOU
		  Jeremie YANG
* DATE: 02/04/2024
* *********************************************************
* 
*/
template<typename SommetType, typename ArcType>
class CGraphParser: public Parser
{
public:

	/**
	*******************************************************************************
	* GPRAddVertex
	* *****************************************************************************
	* Entries : graph : CGraphOrient<SommetType, ArcType> representing the graph to fill with vertecies
	*			sSizeVertex : string representing the value of the name of the element size we want to read (eg: "Nbsommet" for "Nbsommet=2")
	*			sSectionName : string representing the name of the section to read plus the first delimiter of the section (eg:"Sommets=[" for "Sommets=[2, 3]")
				sDelimiterEnd : string representing the last delimiter of the section (eg: "]" for "Sommets=[2, 3]")
	* Needs : None
	* Returns : void
	* Leads : add some vertecies to the graph with values read from the file
	*******************************************************************************
	*/
	void GPRAddVertex(CGraphOrient<SommetType, ArcType>*& graph, const string& sSizeVertex, const string& sSectionName,const string& VertexVariableName="numero", const string& sDelimiterBegin = "[", const string& sDelimiterEnd = "]", const string& sDelimiterAffectation = "=")
	{
		// we get accessed to each line of the section (which means each element that contains the value of the vertex to create)
		vector<string> allVerteciesSection = PARAnalyzeSection(sSectionName, sDelimiterAffectation, sDelimiterBegin, sDelimiterEnd);

		int size;
		if (!sDelimiterAffectation.empty())
		{
			//cout << PARGetLineContains(sSizeVertex) << endl;
			string res = PARAnalyzeSectionElement(PARGetLineContains(sSizeVertex), sSizeVertex, sDelimiterAffectation);
			if (!res.empty())
			{
				for (char c : res)
				{
					if (!isdigit(c))
					{
						string error_message = "the size of the " + sSizeVertex + " is not fully numeric";
						throw CException(size_not_defined, error_message, "CGraphParser.h", 57);
					}
						
				}
				size = stoi(res);
			}
			else
			{
				res = "there is no size defined for the " + sSizeVertex;
				throw CException(size_not_defined, res, "CGraphParser.h", 53);
			}
		}
		else
			throw CException(the_number_of_vertex_not_found, "Error on finding the number of the vertex to create", "CgraphParser.h", 50);




		if (size > allVerteciesSection.size())
			throw CException(size_not_conformed, "the number of vertecies you want to create is greater than the number of vertecies that is actually defined in your file.txt", "CGrpahParser.h",  67);

		string vertexValue = "";
		// then we iterate over those lines and we parse them to find the value of the vertex to create
		for (int i = 0; i < size; i++)
		{
			vertexValue = PARAnalyzeSectionElement(allVerteciesSection[i], VertexVariableName, sDelimiterAffectation);
			if (PARContainsSpaceOrTab(vertexValue))
				throw CException(size_not_conformed, "the vertex should not be a composed value", "CGrpahParser.h", 67);
			// this line created the vertex with the value "vertexValue" in the graph
			graph->GROAddVertex(vertexValue);
			//cout << "creation du vertex " << PARAnalyzeSectionElement(allVerteciesSection[i], sVertexName, "=") << endl;
		}
	}

	/**
	*******************************************************************************
	* GPRAddArc
	* *****************************************************************************
	* Entries :  graph : CGraphOrient<SommetType, ArcType> representing the graph to create arcs for
	*			sSizeArcs : string representing the value of the name of the element size we want to read (eg: "Nbarc" for "Nbarc=2")
	*			sSectionName : string representing the name of the section to read plus the first delimiter of the section (eg:"Arcs=[" for "Arcs=[2, 3]")
				sDelimiterEnd : string representing the last delimiter of the section (eg: "]" for "Arcs=[2, 3]")
	* Needs : None
	* Returns : void
	* Leads : add some arcs to the graph with values dep and arr read from the file
	*******************************************************************************
	*/
	void GPRAddArc(CGraphOrient<SommetType, ArcType>*& graph, const string& sSizeArcs, const string& sSectionName, const vector<string>& ArcsVariableName,
		const string& sDelimiterBegin = "[", const string& sDelimiterEnd="]", const string& sDelimiterAffectation = "=", const string& sDelimiterBetweenArcsValuesNames = ",")
	{

		// we get accessed to lines that describes the arcs to create
		vector<string> allArcsSection = PARAnalyzeSection(sSectionName, sDelimiterAffectation, sDelimiterBegin, sDelimiterEnd);
		// first, we read the number of arcs to create
		int size;

		if (!sDelimiterAffectation.empty())
		{
			string res = PARAnalyzeSectionElement(PARGetLineContains(sSizeArcs), sSizeArcs, sDelimiterAffectation);
			if (!res.empty())
			{
				for (char c : res)
				{
					if (!isdigit(c))
					{
						string error_message = "the size of the " + sSizeArcs + " is not fully numeric";
						throw CException(size_not_defined, error_message, "CGraphParser.h", 119);
					}

				}
				size = stoi(res);
			}
			else
			{
				res = "there is no size defined for the " + sSizeArcs;
				throw CException(size_not_defined, res, "CGraphParser.h", 115);
			}
		}

		if (size > allArcsSection.size())
			throw CException(size_not_conformed, "the number of arcs you want to create is greater than the number of arcs that is actually defined in your file.txt", "CGrpahParser.h", 93);

		// then with a for loop, we parse each line to have the dep value and arr value of each arc
		for (int i = 0; i < size; i++)
		{	
			size_t pos = allArcsSection[i].find(sDelimiterBetweenArcsValuesNames);
			string sDebArc = PARAnalyzeSectionElement(allArcsSection[i].substr(0, pos), ArcsVariableName[0]);
			string sArrArc = PARAnalyzeSectionElement(allArcsSection[i].substr(pos, allArcsSection[i].size()), ArcsVariableName[1]);

			//cout << "debut arc -> " << sDebArc << "| fin arc ->" << sArrArc << endl;

			if (PARContainsSpaceOrTab(sDebArc) || PARContainsSpaceOrTab(sArrArc))
				throw CException(size_not_defined, "one of the values of your arcs contain spaces or tabs, correct them !", "CGraphParser.h", 115);

			//cout << "arc (" << sDebArc << ", " << sArrArc << ")" << endl;
			// then we create the  arc with the specified values
			graph->GROAddArc(sDebArc, sArrArc);
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
	void GPRMain(const string& sfileName)
	{

		// we create the specified graph
		CGraphOrient<SommetType, ArcType>* graph = new CGraphOrient<SommetType, ArcType>();

		try
		{
			// first, we read the file
			PARReadFile(sfileName);


			// we add all vertecies sepcified by the file
			GPRAddVertex(graph, "NBSommets", "Sommets");

			vector<string> vect;

			vect.push_back("debut");
			vect.push_back("fin");

			// we add all arcs specified by the file
			GPRAddArc(graph, "NBArcs", "Arcs", vect);

			// we print the graph
			CPrintGraph::PRIPrintGraph(*graph);

			// we invert the graph
			graph->GROInverserAllArcs();

			cout << "inversion of all arcs of the graph" << endl;

			// we print the inverted graph
			CPrintGraph::PRIPrintGraph(*graph);

			delete graph;
		}
		catch (CException e)
		{
			delete graph;
			e.EXCReadMessage();
		}
	}
};

#endif // CGRAPH_PARSER_H
