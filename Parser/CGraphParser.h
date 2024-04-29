#ifndef CGRAPH_PARSER_H
#define CGRAPH_PARSER_H

#include "Parser.h"
#include "../CArc/Arc.h"
#include "../CVertex/CVertex.h"
#include "../CGraph/CGraphNOrient.h"
#include "../CGraph/CGraphOrient.h"
#include "../PrintGraph/CPrintGraph.h"

#include <cctype>

#define the_number_of_vertex_not_found 26
#define composed_value 27
#define value_not_numeric 28
#define size_not_conformed 29
#define size_not_defined 30

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
	void GPRAddVertex(CGraphOrient<SommetType, ArcType>*& graph, const string& sSizeVertex, const string& sSectionName,const string& VertexVariableName="numero", const string& sDelimiterBegin = "[", const string& sDelimiterEnd = "]", const string& sDelimiterAffectation = "=")
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
						throw CException(value_not_numeric, error_message, "CGraphParser.h", 57);
					}
						
				}
				// if yes, we convert it to integer
				size = stoi(res);
			}
			else
			{
				res = "there is no size defined for the " + sSizeVertex;
				throw CException(size_not_defined, res, "CGraphParser.h", 57);
			}
		}
		else
			throw CException(the_number_of_vertex_not_found, "Error on finding the number of the vertex to create", "CGraphParser.h", 53);




		if (size > allVerticesSection.size())
			throw CException(size_not_conformed, "the number of Vertices you want to create is greater than the number of Vertices that is actually defined in your file.txt", "CGrpahParser.h",  67);

		string vertexValue = "";
		// then we iterate over those lines and we parse them to find the value of the vertex to create
		for (int i = 0; i < size; i++)
		{
			vertexValue = PARAnalyzeSectionElement(allVerticesSection[i], VertexVariableName, sDelimiterAffectation);

			// we first check if the value is not a composed value
			if (PARContainsSpaceOrTab(vertexValue))
			{
				// it yes, we throw an exception
				throw CException(composed_value, "the vertex should not be a composed value", "CGrpahParser.h", 97);
			}
			// if not, this line created the vertex with the value "vertexValue" in the graph
			graph->GROAddVertex(vertexValue);
		}
	}

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
					// by a for loop, we check if all characters of the res's value are digits, 
					if (!isdigit(c))
					{
						// if not, we throw an exception
						string error_message = "the size of the " + sSizeArcs + " is not fully numeric";
						throw CException(value_not_numeric, error_message, "CGraphParser.h", 138);
					}

				}
				// if yes, we convert it to integer
				size = stoi(res);
			}
			else
			{
				res = "there is no size defined for the " + sSizeArcs;
				throw CException(size_not_defined, res, "CGraphParser.h", 133);
			}
		}

		if (size > allArcsSection.size())
			throw CException(size_not_conformed, "the number of arcs you want to create is greater than the number of arcs that is actually defined in your file.txt", "CGrpahParser.h", 156);

		// then with a for loop, we parse each line to have the dep value and arr value of each arc
		for (int i = 0; i < size; i++)
		{	
			size_t pos = allArcsSection[i].find(sDelimiterBetweenArcsValuesNames);
			string sDebArc = PARAnalyzeSectionElement(allArcsSection[i].substr(0, pos), ArcsVariableName[0]);
			string sArrArc = PARAnalyzeSectionElement(allArcsSection[i].substr(pos, allArcsSection[i].size()), ArcsVariableName[1]);


			if (PARContainsSpaceOrTab(sDebArc) || PARContainsSpaceOrTab(sArrArc))
				throw CException(composed_value, "one (or more) of the values of your arcs contain spaces or tabs, correct them !", "CGraphParser.h", 167);

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


			// we add all Vertices sepcified by the file
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
