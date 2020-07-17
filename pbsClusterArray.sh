#!/bin/bash
. generateArgumentList.sh

if [ $# -ne 2 ] ; then
	echo "expected options: <time HH:MM:SS> <mem e.g. 256mb>"
	exit
fi
set -eu

jobName=sampleJob
workDir=/home/sgerloff2/pbs/${jobName} #Please change directories accordingly!

shearRate=( 400 )
ensIndex=( $(seq 0 1 99) )

rm -f argumentList.argl
iterateNestedForLoops shearRate[@] ensIndex[@]  >> argumentList.argl


mkdir -p $workDir
cp -r src CMakeLists.txt argumentList.argl $workDir
cd $workDir && cmake -DCMAKE_BUILD_TYPE=RELEASE && make
mv shearedSlitporeBD $workDir/${jobName}
mv argumentList.argl $workDir/${jobName}.argl
cp submitPBSSerialJobs.sh $workDir/
cd $workDir
/home/sgerloff2/pbs/submitPBSSerialJobs.sh ${jobName} $1 $2 #Please change directories accordingly!
