

#include "global.h"
#include "tools/printer.h"
#include "tools/parse_arguments.h"


#include "systems/sheared_slitpore_system.h"
#include "command/average_stress.h"

#include <ctime>
#include <limits>

int main( int argc, char *argv[] )
{             
    defaultOutputDir = "/home/sgerloff2/projects/shearedSlitporeBD/output/"; //Sets default output dir for app_home( string str ); see global.cpp. This folder HAS to be in your /home/<username>2/ directroy!!!
    
    srand( getpid()*time ( 0 ) );
    
    PARSE_ARGUMENTS parseArguments;
    arguments = parseArguments.getArgumentList( argc, argv );
    parseArguments.checkForInvalidArguments( arguments );
    parseArguments.printArgumentList( arguments );
    
    
 /////////////////////// SLIT-PORE SYSTEM ////////////////////////////////////   
    
    SHEARED_SLITPORE_PARAMETERS sysParameters;
    sysParameters.setAsBiLayerWithShearRate( 0 );
    sysParameters.print();

    double shearRate = arguments[0];
    int ensIndex = arguments[1];
    
    SHEARED_SLITPORE_SYSTEM sys ( sysParameters );
    
    sys.readConfigurationToEnsembleContainer( "", "", ensIndex );

    sys.STRESS=true;
    sys.setShearRate(shearRate);
    
    AVERAGE_STRESS averageStress;
    
    for(int i = 0; i < 100000; ++i ){
        if(i%100==0)
            cout << i << endl;
        sys.simulateForSteps(1);
        averageStress.doForSystem(sys);
        if(i%100==0){
            cout << averageStress.getStress().xz << endl;
            sys.printConfigurationToEnsembleContainer( "", "test", ensIndex );
        }
    }
    
    return 0;
}





