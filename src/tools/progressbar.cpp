#include "progressbar.h"

PROGRESSBAR::~PROGRESSBAR()
{
    output << std::endl;
}

PROGRESSBAR::PROGRESSBAR() : output( std::cout ), res( 50 )
{
   setInitial();
}


PROGRESSBAR::PROGRESSBAR( std::ostream &oIN, int resIN ) : output( oIN ), res( resIN )
{
   setInitial();
}

void PROGRESSBAR::initializeProgressBar( std::string messageIN, int maxStepsIN )
{
   message = messageIN;
   maxSteps = maxStepsIN;
   intervalLength = maxSteps / res;
   initializeLayout();
}

void PROGRESSBAR::initializeLayout()
{
   output << message;
   output << "\t";
   output << generateRuler();
   output << "\n";
   output << voidString( message.length() );
   output << "\t";
   output << voidString( frontRulerDescription.length() );
   flushOutput();
}

void PROGRESSBAR::setInitial()
{
   //Inputs (Default):
   message = "No Message Specified!";
   maxSteps = 1;

   //Interval-Specification (Default)
   subIntervalCount = 10;
   subInterval = res / subIntervalCount;
   intervalLength = maxSteps / res;


   //Formating strings (Default):
   frontRulerDescription = "0%";
   rulerIntervalMarker = "|";
   endRulerDescription = "100%";
   barSymbol = "\u2588";

   //Dynamic Variable:
   barLength = 0;
   currentIt = 0;
}


std::string PROGRESSBAR::generateRuler()
{
   std::string ruler = frontRulerDescription;

   for( int i = 0; i < res; ++i )
   {
      if( i % subInterval == 0 )
      {
         ruler += rulerIntervalMarker;
      }
      else
      {
         ruler += ".";
      }
   }

   return ruler + rulerIntervalMarker + endRulerDescription;
}

std::string PROGRESSBAR::voidString( int length )
{
   std::string voidString;

   for( int i = 0; i < length; ++i )
   {
      voidString += " ";
   }

   return voidString;
}


void PROGRESSBAR::print( int iteratorIN )
{
   currentIt = iteratorIN;

   if( isBegin() )
   {
      output << barSymbol;
      flushOutput();
   }

   if( isNewInterval() )
   {
      output << barSymbol;
      flushOutput();
      ++barLength;
   }
}

bool PROGRESSBAR::isBegin()
{
   return currentIt == 0 && barLength == 0;
}

bool PROGRESSBAR::isNewInterval()
{
   return ( currentIt + 1 ) % intervalLength == 0 && ( currentIt + 1 ) / intervalLength > barLength;
}

void PROGRESSBAR::reset()
{
   output << "\n";
   flushOutput();
   barLength = 0;
   message = "No Message Specified!";
   maxSteps = 1;
}

void PROGRESSBAR::flushOutput()
{
   flush( output );
}

int PROGRESSBAR::getBarLength()
{
   return barLength;
}

void PROGRESSBAR::setFrontRulerDescription( std::string in )
{
   frontRulerDescription = in;
}

void PROGRESSBAR::setRulerIntervalMarker( std::string in )
{
   rulerIntervalMarker = in;
}

void PROGRESSBAR::setEndRulerDescription( std::string in )
{
   endRulerDescription = in;
}

void PROGRESSBAR::setBarSymbol( std::string in )
{
   barSymbol = in;
}


