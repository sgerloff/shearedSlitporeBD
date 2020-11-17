#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <string>
#include <iostream>

class PROGRESSBAR
{
   //Inputs:
   std::ostream & output;
   int res;

   std::string message;
   int maxSteps;

   //Interval-Specification
   int subIntervalCount;
   int subInterval;
   int intervalLength;


   //Formating strings:
   std::string frontRulerDescription;
   std::string rulerIntervalMarker;
   std::string endRulerDescription;
   std::string barSymbol;

   //Dynamic Variable:
   int barLength;
   int currentIt;

   void setInitial();

public:

   ~PROGRESSBAR();
   PROGRESSBAR();
   PROGRESSBAR ( std::ostream& oIN, int resIN );
   void initializeProgressBar ( std::string message, int maxSteps );

   void initializeLayout();
   std::string generateRuler();
   std::string voidString ( int length );
   void print ( int iterator );
   bool isBegin();
   bool isNewInterval();

   void flushOutput();
   void reset();

   int getBarLength();

   void setFrontRulerDescription ( std::string in );
   void setRulerIntervalMarker ( std::string in );
   void setEndRulerDescription ( std::string in );
   void setBarSymbol ( std::string in );



};

#endif // PROGRESSBAR_H
