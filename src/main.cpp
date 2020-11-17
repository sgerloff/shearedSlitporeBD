

#include "global.h"
#include "tools/printer.h"
#include "tools/parse_arguments.h"
#include "tools/progressbar.h"


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
    
    //Set command line arguments accordingly
    double shearRate = arguments[0];
    int ensIndex = arguments[1];
    
 /////////////////////// SLIT-PORE SYSTEM ////////////////////////////////////   
    
    //Initiate the system with two layers in equilibrium
    SHEARED_SLITPORE_PARAMETERS sysParameters;
    sysParameters.setAsBiLayerWithShearRate( 0 );
    sysParameters.print();
    
    SHEARED_SLITPORE_SYSTEM sys ( sysParameters );
    
    //Read initial configuration from container file
    sys.readConfigurationFromEnsembleContainer( "", "", ensIndex );

    //Enable stress calculation
    sys.STRESS=true;
    //Set new shear rate
    sys.setShearRate(shearRate);
    
    //Invoke command that handles the tracking of the mean stress data
    AVERAGE_STRESS averageStress;
    //Setup printer and define output file
    PRINTER printer("stress_relaxation", "shear_stress_relaxation_data");
    printer.removeFile(); //Empty existing files
    printer.printLine("t_B", "S_xz");
    //Set max simulation steps (this is set very low ... you should run longer!)
    int maxSteps = 10000;
    
    //Initialize progress bar (optional)
    PROGRESSBAR progBar;
    progBar.initializeProgressBar("Run stress relaxation", maxSteps);
    
    //Run the simulation
    for(int i = 0; i < maxSteps; ++i ){
        //Advance progress bar (optional)
        progBar.print(i);
        //Simulate one step
        sys.simulateForSteps(1);
        //Grab stresses and average
        averageStress.doForSystem(sys);
        //Every once in a while print the result
        if(i%10==0){
            printer.printLine(i*sys.getTimeStepSize(), averageStress.getStress().xz);
        }
    }
    cout << endl;
    //Save (hopefully) relaxed configuration
    sys.printConfigurationToEnsembleContainer( "", "test", ensIndex );
    
    return 0;
}





