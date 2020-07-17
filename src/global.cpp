/*
 *  global.cpp
 *
 *  Created on: Jul 10, 2012
 *      Author: tarlan
 */
#include"global.h"

vector<double> arguments(0);

CRandomMersenne random_event( getpid()*time( 0 ) );

int read_toggle = 0; // 0: read periodic values; 1: read absolute values

char const *pchome = getenv( "HOME" );
string home = pchome ? pchome : ""; //Can be used to distinguish between Math-Cluster and PBS-Cluster

string defaultOutputDir =  "/home/sgerloff2/projects/shearedSlitporeBD/output/";

string app_home( string str )
{
   stringstream output;

   if( home == "/homes2/physik/gerloff" )
   {
      output << "/net/work/gerloff/";
   }
   else
   {
      output << defaultOutputDir;
   }

   output << str;
   return output.str();
}



