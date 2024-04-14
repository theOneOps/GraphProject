
#include <iostream>
#include "CArc/Arc.h"
#include "CVertex/CVertex.h"
#include "PrintGraph/CPrintGraph.h"
#include "Parser/Parser.h"
#include "CGraph/CGraphNOrient.h"
#include "CGraph/CGraphOrient.h"
#include "Parser/CGraphParser.h"
#include "CException/CException.h"

using namespace std;

#define wrong_number_of_args 404


int main()
{	
	CGraphParser<CVertex, CArc> parser;
	parser.GPRMain("graph.txt");
	return 0;
}

