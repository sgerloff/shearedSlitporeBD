#!/bin/bash
if [ $# -ne 2 ] ; then
	echo "expected syntax: submitArrayJob <jobName> <time limit in sec>"
	exit 1
fi

numberOfArgumentLines=$(( $(wc -l < "$1.argl") - 1 )) #Minus description line

js="jobscript"
echo "#!/bin/tcsh" > $js
echo "#\$ -t 1:$numberOfArgumentLines" >> $js
echo "#\$ -N $(basename $1)" >> $js
echo "#\$ -j y" >> $js
#echo "#\$ -e /work/gerlofF/jobFiles/errorFiles/$(basename $1).eOut" >> $js
echo "#\$ -o /work/gerloff/jobFiles/$(basename $1)_\$JOB_ID.\$TASK_ID.out" >> $js
echo "#\$ -l h_rt=$2" >> $js
echo "#\$ -m a" >> $js
echo "#\$ -M s.gerloff@tu-berlin.de" >> $js
echo "" >> $js
echo "/work/gerloff/jobFiles/workDir/runMathClusterTasks.sh $1" >> $js
qsub $js
