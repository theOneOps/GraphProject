#ifndef CGRAPH_PARSER_H
#define CGRAPH_PARSER_H

#include "Parser.h"


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
	* PARGRAAddVertex
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
	void PARGRAAddVertex(CGraphOrient<SommetType, ArcType>*& graph, const string& sSizeVertex, const string& sSectionName, const string& sDelimiterEnd, const string& sDelimiterValue="=")
	{
		int size;
		if (!sDelimiterValue.empty())
			size = stoi(AnalyzeSectionElement(getLineContains(sSizeVertex), sDelimiterValue));
		else
			throw CException(the_number_of_vertex_not_found, "Error on finding the number of the vertex to create", "Parser.h", 44);

		// we get accessed to each line of the section (which means each element that contains the value of the vertex to create)
		vector<string> allVerteciesSection = PARAnalyzeSection(sSectionName, sDelimiterEnd);

		string vertexValue = "";
		// then we iterate over those lines and we parse them to find the value of the vertex to create
		for (int i = 0; i < size; i++)
		{
			vertexValue = AnalyzeSectionElement(allVerteciesSection[i], sDelimiterValue);
			// this line created the vertex with the value "vertexValue" in the graph
			graph->GROAddVertex(vertexValue);
			//cout << "creation du vertex " << AnalyzeSectionElement(allVerteciesSection[i], sVertexName, "=") << endl;
		}
	}

	/**
	*******************************************************************************
	* PARGRAAddArc
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
	void PARGRAAddArc(CGraphOrient<SommetType, ArcType>*& graph, const string& sSizeArcs, const string& sSectionName, const string& sDelimiterEnd, const string& sDelimiterValue = "=")
	{

		// we get accessed to lines that describes the arcs to create
		vector<string> allArcsSection = PARAnalyzeSection(sSectionName, sDelimiterEnd);
		// first, we read the number of arcs to create
		int size;
		if (!sDelimiterValue.empty())
			size = stoi(AnalyzeSectionElement(getLineContains(sSizeArcs), sDelimiterValue));
		else
			size = stoi(AnalyzeSectionElement(getLineContains(sSizeArcs), sDelimiterValue));

		// then with a for loop, we parse each line to have the dep value and arr value of each arc
		for (int i = 0; i < size; i++)
		{
			
			size_t pos = allArcsSection[i].find(",");
			string sDebArc = AnalyzeSectionElement(allArcsSection[i].substr(0, pos));
			string sArrArc = AnalyzeSectionElement(allArcsSection[i].substr(pos, allArcsSection[i].size()));

			//cout << "arc (" << sDebArc << ", " << sArrArc << ")" << endl;
			// then we create the  arc with the specified values
			graph->GROAddArc(sDebArc, sArrArc);
		}
	}

	/**
	*******************************************************************************
	* PARGRACreateGraph
	* *****************************************************************************
	* Entries : None
	* Needs : None
	* Returns : CGraphOrient<SommetType, ArcType>*
	* Leads : return an oriented or non oriented graph based on the file parsed
	*******************************************************************************
	*/
	CGraphOrient<SommetType, ArcType>* PARGRACreateGraph()
	{
		// 
		CGraphOrient<SommetType, ArcType>* graph;
		if (AnalyzeSectionElement(getLineContains("Oriented")) == "yes")
		{
			// if the oriented is set to yes into the file, we create an oriented graph
			graph = new CGraphOrient<SommetType, ArcType>();
		}
		else // unless,  we create an non oriented graph
			graph = new CGraphNOrient<SommetType, ArcType>();

		return graph;
	}

	/**
	*******************************************************************************
	* PARGRAMain
	* *****************************************************************************
	* Entries : tree : sfileName : string representing the file to read/parse
	* Needs : None
	* Returns : void
	* Leads : read a file .txt, create the specified graph, print it, invert it and print it again
	*******************************************************************************
	*/
	void PARGRAMain(const string& sfileName)
	{
		// first, we read the file
		PARReadFile(sfileName);

		// we create the specified graph
		CGraphOrient<SommetType, ArcType>* graph = PARGRACreateGraph();

		// we add all vertecies sepcified by the file
		PARGRAAddVertex(graph, "NBSommets", "Sommets=[", "]");

		// we add all arcs specified by the file
		PARGRAAddArc(graph,"NBArcs", "Arcs=[", "]");

		// we print the graph
		CPrintGraph::PrintGraph(*graph);

		// we invert the graph
		graph->GROInverserAllArcs();

		cout << "inversion of all arcs of the graph" << endl;

		// we print the inverted graph
		CPrintGraph::PrintGraph(*graph);

		// we deallocate the memory of the graph
		delete graph;
	}

	//void PARGRAModifyVertex(const string& sOldValue, const string& sNewValue);
	//void PARGRARemoveVertex(const string& sValue);
	//void PARGRARemoveArc(const string& sDepValue, const string& sArrValue);

};

#endif // CGRAPH_PARSER_H
