#include "../struct/configuration_container.h"

CONFIGURATION_CONTAINER::CONFIGURATION_CONTAINER()
{
    printer.EXCLUSIVE = true;
    containerData.clear();
}

CONFIGURATION_CONTAINER::CONFIGURATION_CONTAINER(string dir, string str)
{
    printer.EXCLUSIVE = true;
    containerData.clear();
    openContainer(dir, str);
}

void CONFIGURATION_CONTAINER::openContainer(string dir, string str)
{
    printer.setDirectoryPathAndOutputFile( dir, str );
    if( !printer.fileIsEmpty() ){
        READ_DATA_FROM_FILE reader;
        reader.readFileFromDirectory( dir ,str );
        containerData = reader.getLineList();
    }
}

void CONFIGURATION_CONTAINER::writeToEnsembleIndex(int ensIndex, vector<double> configIn)
{
    vector<double>::iterator it = configIn.begin();
    configIn.insert(it, ensIndex);
    
    if( ensIndex < containerData.size() && containerData.size() != 0 ){
        containerData[ensIndex] = configIn;
    } else {
        vector<vector<double> > tmp(ensIndex+1);
        tmp[ensIndex] = configIn;
        for(int i = 0; i < containerData.size(); ++i){
            tmp[i]=containerData[i];
        }
        containerData = tmp;
    }
    printer.removeFile();
    for(int i = 0; i < containerData.size(); ++i) {
        printer.printLine( containerData[i] );
    }
}

vector<double> CONFIGURATION_CONTAINER::readEnsembleIndex(int ensIndex)
{
    if(ensIndex < containerData.size() ){
        return containerData[ensIndex];
    } else {
        cout << "EnsIndex too large: " << ensIndex << "\t" << containerData.size() << endl;
        vector<double> empty;
        return empty;
    }
}

