#include "printer.h"

PRINTER::PRINTER()
{
    setExclusiveReadAndWrite(100,10);
    EXCLUSIVE = false;

    setFileExtension("txt");
    setDirectoryPathAndOutputFile( "", "" );
}

PRINTER::PRINTER( string outputFileIn )
{
    setExclusiveReadAndWrite(100,10);
    EXCLUSIVE = false;

    setFileExtension("txt");
    setDirectoryPathAndOutputFile( "", outputFileIn );
}

PRINTER::PRINTER( string directoryPathIn, string outputFileIn )
{
    setExclusiveReadAndWrite(100,10);
    EXCLUSIVE = false;

    setFileExtension("txt");
    setDirectoryPathAndOutputFile( directoryPathIn, outputFileIn );
}

PRINTER::~PRINTER()
{
    file.close();
    if( EXCLUSIVE ) {
        rmdir( lockDir.c_str() );
    }
}

void PRINTER::setExclusiveReadAndWrite(int maxWaitCountsIn, int waitSecondsIn)
{
    EXCLUSIVE = true;
    maxWaitCounts = maxWaitCountsIn;
    waitSeconds = waitSecondsIn;
}

void PRINTER::setFileExtension ( string fileExtensionIn )
{
    remove( filePath.c_str() );
    fileExtension = fileExtensionIn;
    file.close();
    getFilePath();
    openFile();
}

bool PRINTER::fileIsEmpty()
{
    file.seekp(0, ios::end); // put the "cursor" at the end of the file
    double length = file.tellp();
    if( length == 0 )
        return true;
    else
        return false;
}

void PRINTER::setDirectoryPathAndOutputFile( string directoryPathIn, string outputFileIn )
{
    directoryPath = directoryPathIn;

    string cmd = "mkdir -p " + app_home( directoryPath );
    system( cmd.c_str() );

    outputFile = outputFileIn;
    getFilePath();

    if( EXCLUSIVE ) {
        getExclusiveAccess();
    }

    openFile();
}

void PRINTER::getExclusiveAccess()
{
    lockDir = app_home( "" ) + directoryPath + "/" + outputFile + ".lock.d";
    int count = 0;

    while( mkdir(lockDir.c_str(), 0755) != 0 ) {

        if(count == 0)
            cout << "File currently locked" << endl;
        else
            cout << "." << endl;

        sleep( rand() % waitSeconds + 1 );

        ++count;
        if( count >= maxWaitCounts ) {
            cout << "Waited for up to" << maxWaitCounts*waitSeconds << " seconds; Exit!" << endl;
            exit(1);
        }
    }
}

void PRINTER::getFilePath()
{
    filePath = app_home( "" ) + directoryPath + "/" + outputFile + "." + fileExtension;
}

void PRINTER::openFile()
{
    file.close();
    file.open( filePath.c_str(), ios::app );
}

void PRINTER::removeFile()
{
    file.close();
    remove( filePath.c_str() );
    openFile();
}

void PRINTER::printLine(vector<double> vecIn)
{
    file << vecIn[0];
    for(int i = 1; i < vecIn.size(); ++i) {
        file << "\t";
        file << vecIn[i];
    }
    file << endl;
}






