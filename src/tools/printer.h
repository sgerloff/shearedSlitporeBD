#ifndef PRINTER_H
#define PRINTER_H
// #include "../global.h"

#include<stdarg.h>
#include <fstream>
#include <string>
using namespace std;
#include "../global.h"

class PRINTER
{
    string outputFile, filePath,directoryPath;
    ofstream file;

    string lockDir;
    int maxWaitCounts;
    int waitSeconds;

    string fileExtension;

    void getFilePath();
    void openFile();
    void getExclusiveAccess();

public:

    bool EXCLUSIVE;
    void setExclusiveReadAndWrite( int maxWaitCountsIn, int waitSecondsIn );

    PRINTER();
    PRINTER ( string outputFileIn );
    PRINTER ( string directoryPathIn, string outputFileIn );
    ~PRINTER();

    void setFileExtension( string fileExtensionIn );

    void setDirectoryPathAndOutputFile ( string directoryPathIn, string outputFileIn );
    void removeFile();

    bool fileIsEmpty();

    template<typename T>
    void printLine ( T t )
    {
        file << t << endl;
    }

    template<typename T, typename... Args>
    void printLine ( T t, Args... args )
    {
        file << t << "\t";
        printLine ( args... );
    }

    void printLine( vector<double> vecIn );

};

#endif // PRINTER_H
