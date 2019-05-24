. generateArgumentList.sh

if [ $# -eq 0 ] ; then
	echo "Memory angeben"
	exit
fi

set -e
set -u

jobName="workHeatEnergyPerParticle_flow"

workDir="/home/sgerloff2/condor/workingDir"
jobFiles="/home/sgerloff2/condor/jobFiles"

# param=( $(seq -f "%g" 0 5) )
# param2=( $(LANG=en_US seq -f "%g" 0 0.2 1) )
# ncFieldAmplitude=( $(seq 0 1000) )
# shearRate=( $(seq 0 10 500) )
shearRate=( 0 160 240 400 )
# shearRate=( 230 250 280 300 310 330 350 370 420 )
# ensIndex=( $(seq 0 99) )
# minCount=( 10000 )
# numberOfParticles=( $(seq 50 2 150) )

# param=( 0 )

rm -f argumentList.argl
iterateNestedForLoops shearRate[@] >> argumentList.argl

cp -r src CMakeLists.txt argumentList.argl $workDir
cd $workDir && cmake -DCMAKE_BUILD_TYPE=RELEASE && make
mv brownianDynamics $workDir/${jobName} && mv argumentList.argl $workDir/${jobName}.argl && sed -i -e "1d" $workDir/${jobName}.argl

qsub -mem $1 -argfile $workDir/${jobName}.argl -o "${jobFiles}/${jobName}.\$(Cluster).\$(Process).out" -m e $jobName


