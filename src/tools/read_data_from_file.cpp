#include "read_data_from_file.h"

READ_DATA_FROM_FILE::READ_DATA_FROM_FILE()
{
    fileExtension = "txt";
    
    reset();
}

void READ_DATA_FROM_FILE::reset()
{
    lineList.clear();
    description.clear();
    FIXED_COLUMN_NUMBER = false;
}

void READ_DATA_FROM_FILE::setFixedColumnNumber(int numberOfColumnsIn)
{
    FIXED_COLUMN_NUMBER = true;
    numberOfColumns = numberOfColumnsIn;
}

void READ_DATA_FROM_FILE::readFileFromDirectory(string dir, string str)
{
    string filePath = app_home( "" ) + dir + "/" + str + "." + fileExtension;
    ifstream inputFile( filePath.c_str() );

    fileGood = inputFile.good();
    
    string line;
    
    cout << filePath << endl;
    
    streampos startOfFile = inputFile.tellg();
    
    while (getline(inputFile, line)){
        
        vector<double> lineData = readLineOfData( line );
        
        if( lineList.size() == 0 ){
            if( lineData.size() == 0 ){
                inputFile.seekg( startOfFile );
                getline(inputFile,line);
                description = readDescription( line );
            }
        }
        if( lineData.size() > 0){
            if( FIXED_COLUMN_NUMBER ){
                if( lineData.size() == numberOfColumns ){
                    lineList.push_back( lineData ); 
                } else {
                    cout << "omitted line with count: " << lineData.size() << endl;
                }
            }else{
                lineList.push_back( lineData );
            }
        }
    }
}

vector<double> READ_DATA_FROM_FILE::readLineOfData(string line)
{
    stringstream inputLine(line);
    vector<double> data;
    data.clear();
    
    double tmpData;
    while( inputLine >> tmpData )
        data.push_back( tmpData );
    
    return data;
}

vector<string> READ_DATA_FROM_FILE::readDescription(string line)
{
    stringstream inputLine(line);
    vector<string> description;
    description.clear();
    
    string str;
    while( inputLine >> str )
        description.push_back( str );
    
    return description;
}

vector<string> READ_DATA_FROM_FILE::getDescription()
{
    return description;
}

vector<vector<double> > READ_DATA_FROM_FILE::getLineList()
{
    return lineList;
}

vector<vector<double> > READ_DATA_FROM_FILE::getColumnList()
{
    vector<vector<double> > columnList( lineList[0].size() );
    for( int i = 0; i < columnList.size(); ++i )
        columnList[i].clear();
    
    for( int i = 0; i < lineList.size(); ++i ){
        for( int j = 0; j < lineList[i].size(); ++j ){
            if( j < columnList.size() )
                columnList[j].push_back( lineList[i][j] ); 
        }
    }
    
    return columnList;
}


