#!/bin/bash
. generateArgumentList.sh

if [ $# -eq 0 ] ; then
	echo "laufzeit in sekunden angeben"
	exit
fi
set -eu

jobName=sampleJob

shearRate=( 400 )
ensIndex=( $(seq 0 1 99) )


rm -f argumentList.argl
iterateNestedForLoops shearRate[@] ensIndex[@] >> argumentList.argl

src="./src"
workDir=/work/gerloff/jobFiles/workDir

#Please change server address and directories accordingly, including the scripts runMathClusterTasks.sh, and submitMathClusterArrayJob.sh:
scp -r $src runMathClusterTasks.sh submitMathClusterArrayJob.sh CMakeLists.txt argumentList.argl gerloff@cluster.math.tu-berlin.de:
ssh gerloff@cluster.math.tu-berlin.de 'cd . && cmake -DCMAKE_BUILD_TYPE=RELEASE . && make -C .'
ssh gerloff@cluster.math.tu-berlin.de "mv runMathClusterTasks.sh $workDir/ && mv submitMathClusterArrayJob.sh $workDir/ && mv shearedSlitporeBD $workDir/${jobName} && mv argumentList.argl $workDir/${jobName}.argl"

ssh gerloff@cluster.math.tu-berlin.de "cd $workDir; ./submitMathClusterArrayJob.sh ${jobName} $1" #This script needs to be placed into the workDir. D
ssh gerloff@cluster.math.tu-berlin.de "rm -rf src CMakeLists.txt"
