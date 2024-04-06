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
* EXTERNES InCLUSIONS
*/

template<typename SommetType, typename ArcType>
class CGraphParser: public Parser
{
public:
	void PARGRAAddVertex(CGraphOrient<SommetType, ArcType>*& graph, const string& sSizeVertex, const string& sSectionName, const string& sDelimiterEnd, const string& sVertexName, const string& sDelimiterValue="=")
	{
		int size;
		if (!sDelimiterValue.empty())
			size = stoi(AnalyzeSectionElement(getLineContains(sSizeVertex), sSizeVertex, sDelimiterValue));
		else
			size = stoi(AnalyzeSectionElement(getLineContains(sSizeVertex), sSizeVertex));
		
		vector<string> allVerteciesSection = PARAnalyzeSection(sSectionName, sDelimiterEnd);

		string vertexValue = "";
		for (int i = 0; i < size; i++)
		{
			vertexValue = AnalyzeSectionElement(allVerteciesSection[i], sVertexName);
			graph->GROAddVertex(vertexValue);
			//cout << "creation du vertex " << AnalyzeSectionElement(allVerteciesSection[i], sVertexName, "=") << endl;
		}
	}

	void PARGRAAddArc(CGraphOrient<SommetType, ArcType>*& graph, const string& sSectionName, const string& sDelimiterEnd)
	{
		vector<string> allArcsSection = PARAnalyzeSection(sSectionName, sDelimiterEnd);
		for (string line : allArcsSection)
		{
			string sDebArc = AnalyzeSectionElement(line.substr(0, line.find(",")), "Numero");
			string sArrArc = AnalyzeSectionElement(line.substr(line.find(","), line.size()), "Numero");

			//cout << "arc (" << sDebArc << ", " << sArrArc << ")" << endl;

			graph->GROAddArc(sDebArc, sArrArc);
		}
	}

	CGraphOrient<SommetType, ArcType>* PARGRACreateGraph()
	{
		CGraphOrient<SommetType, ArcType>* graph;
		if (AnalyzeSectionElement(getLineContains("Oriented"), "Oriented") == "yes")
		{
			graph = new CGraphOrient<SommetType, ArcType>();
		}
		else
			graph = new CGraphNOrient<SommetType, ArcType>();

		return graph;
	}

	void PARGRAMain(const string& sfileName)
	{
		PARReadFile(sfileName);
		CGraphOrient<SommetType, ArcType>* graph = PARGRACreateGraph();
		PARGRAAddVertex(graph, "NBSommets", "Sommets=[", "]", "Numero");
		PARGRAAddArc(graph, "Arcs=[", "]");

		CPrintGraph::PrintGraph(*graph);

		graph->GROInverserAllArcs();

		cout << "inversion of all arcs of the graph" << endl;

		CPrintGraph::PrintGraph(*graph);

		delete graph;
	}

	//void PARGRAModifyVertex(const string& sOldValue, const string& sNewValue);
	//void PARGRARemoveVertex(const string& sValue);
	//void PARGRARemoveArc(const string& sDepValue, const string& sArrValue);

};

#endif // CGRAPH_PARSER_H
