
#include <iostream>
#include "CArc/Arc.h"
#include "CVertex/CVertex.h"
#include "PrintGraph/CPrintGraph.h"
#include "Parser/Parser.h"
#include "CGraph/CGraphNOrient.h"
#include "CGraph/CGraphOrient.h"
#include "Parser/CGraphParser.h"
#include "CException/CException.h"

#include "CArc/ArcPondere.h"
#include "Parser/CGraphPondereParser.h"

/*

int main(int argc, char*argv[])
{
    if (argc == 3)
    {
        CGraphPondereParser<CVertex, CArcPondere> parserPondere;
        pred_distance_djistra values = parserPondere.GPRMain(argv[1], argv[2]);
    }
    else
    {

        cerr << "Usage: " << "ConsoleApplication.exe" << " <graph_file.txt> <source_vertex>\n" << "Example: " << "ConsoleApplication.exe" << " file.txt 2\n";
        return 1;
    }
    return 0;
}


*/

int main(int argc, char* argv[])
{

    try
    {
        if (argc == 3)
        {
            CGraphPondereParser<CVertex, CArcPondere> parserPondere;
            pred_distance_djistra values = parserPondere.GPPMain(argv[1], argv[2]);
        }
        else
        {

            cerr << "Usage: " << "ConsoleApplication.exe" << " <graph_file.txt> <source_vertex>\n" << "Example: " << "ConsoleApplication.exe" << " file.txt 2\n";
            return 1;
        }
    }
    catch (const CException& e)  // Capturer les exceptions spécifiques si elles sont définies.
    {
        std::cerr << "An error occurred: " << endl;
        e.EXCReadMessage();
    }
    return 0;  // Terminer normalement si aucune exception n'est levée.
}

/*

int main()
{
    const string source = "4";

    try
    {
        CGraphPondereParser<CVertex, CArcPondere> parserPondere;
        pred_distance_djistra values = parserPondere.GPPMain("graph.txt", source);
    }
    catch (const CException& e)  // Capturer les exceptions spécifiques si elles sont définies.
    {
        std::cerr << "An error occurred: " << endl;
        e.EXCReadMessage();
        return 1; // Terminer avec un code d'erreur pour indiquer une sortie anormale.
    }


    return 0;  // Terminer normalement si aucune exception n'est levée.
}

*/