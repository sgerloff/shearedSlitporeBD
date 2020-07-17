#ifndef CONFIGURATION_CONTAINER_H
#define CONFIGURATION_CONTAINER_H

#include "../tools/printer.h"
#include "../tools/read_data_from_file.h"
/**
 * @todo write docs
 */
class CONFIGURATION_CONTAINER
{
    PRINTER printer;
    vector<vector<double> > containerData;
    
public:
    /**
     * Default constructor
     */
    CONFIGURATION_CONTAINER();
    CONFIGURATION_CONTAINER( string dir, string str);
    
    void openContainer( string dir, string str );
    void writeToEnsembleIndex( int ensIndex, vector<double> configIn );
    vector<double> readEnsembleIndex( int ensIndex );
};

#endif // CONFIGURATION_CONTAINER_H
