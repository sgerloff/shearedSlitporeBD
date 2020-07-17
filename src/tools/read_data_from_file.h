#ifndef READ_DATA_FROM_FILE_H
#define READ_DATA_FROM_FILE_H

#include "../global.h"
#include <fstream>

class READ_DATA_FROM_FILE
{
    string fileExtension;
    
    bool FIXED_COLUMN_NUMBER;
    int numberOfColumns;
    
    vector<vector<double> > lineList;
    vector<string> description;
    
    vector<double> readLineOfData( string line ); 
    vector<string> readDescription( string line );
    
public:
    bool fileGood;
    
    READ_DATA_FROM_FILE();
    void reset();
    
    void setFixedColumnNumber( int numberOfColumnsIn );
    
    void readFileFromDirectory( string dir, string str );
    
    vector<string> getDescription();
    vector<vector<double> > getLineList();
    vector<vector<double> > getColumnList();
    
};

#endif // READ_DATA_FROM_FILE_H
