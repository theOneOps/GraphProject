#ifndef PARSER_H
#define PARSER_H


#include <iostream>
#include <fstream>
#include "CArc/Arc.h"
#include "CVertex/CVertex.h"
#include "CGraph/CGraphOriented.h"
#include "CGraph/CGraphNOriented.h"
#include "CPrintGraph.h"


#define file_not_open 20

using namespace std;

/**********************************************************
*  Class : Parser management
* *********************************************************
* 
* ROLE : based on a txt file, create an oriented or non oriented graph
* 
* *********************************************************
* VERSION: 1.0
* AUTHOR: Selly Bill-Gate MEDEWOU
		  Jeremie YANG
* DATE: 28/03/2024
* *********************************************************
* EXTERNES InCLUSIONS
*/

class Parser
{
public:

	static void PARReadTxt(const string& txt, CGraphOriented** graph)
	{
		ifstream file(txt);

		if (!file.is_open()) {
			cerr << "Erreur lors de l'ouverture du fichier" << endl;
			throw CException(file_not_open, "Error on opening the file to read", "Parser.h", 26);
		}

		string line;
		if (getline(file, line))
		{
			if (line.find("Oriented=") != string::npos)
			{
				if (line.substr(line.find("=") + 1) == "yes")
					(*graph) = new CGraphOriented();
				else
					(*graph) = new CGraphNOriented();
			}
		}

		while (getline(file, line))
		{
			if (line.find("Numero") != string::npos)
			{
				std::string prefix = "Numero=";
				size_t startPos = line.find(prefix) + prefix.length();
				std::string vertexNumber = line.substr(startPos);
				std::cout << "vertex " << vertexNumber << std::endl;

				cout << "vertex " + vertexNumber<< endl;
				(*graph)->GROAddVertex(vertexNumber);
			}
			else if (line.find("Debut=") != string::npos)
			{
				string deb = "Debut=";
				string fin = "Fin=";
				string vertexDep;
				string vertexArr;
				size_t startPos = line.find(deb) + deb.length();
				size_t endPos = line.find(",");
				if (endPos != string::npos)
				{
					vertexDep = line.substr(startPos, endPos - startPos);
					startPos = line.find(fin, endPos) + fin.length();
					endPos = line.length();

					vertexArr = line.substr(startPos, endPos - startPos);

					cout << "vertex Dep " + vertexDep << " vertex Arr " + vertexArr << endl;
				}

				(*graph)->GROAddArc(vertexDep, vertexArr);
			}
			else
				cout << line << endl;
		}
		file.close();
	}

	static void mainFunc(const string& txt)
	{
		CGraphOriented* graph;

		Parser::PARReadTxt("graph.txt", &graph);

		CPrintGraph::GROPrintGraph(*graph);

		cout << "arcs Inverted " << endl;

		graph->GROInverserAllArcs();

		CPrintGraph::GROPrintGraph(*graph);

		delete graph;
	}
};

#endif
