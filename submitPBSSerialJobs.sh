#!/bin/bash
if [ $# -ne 3 ] ; then
        echo "expected syntax: submitArrayJob <jobName> <time HH:MM:SS> <mem e.g. 256mb>"
        exit 1
fi

numberOfArgumentLines=$(( $(wc -l < "$1.argl") - 1 )) #Minus description line

OLD_IFS=$IFS
IFS=$'\n'
argumentLines=( $(cat "$1.argl") )
IFS=$OLD_IFS

JOB_SCRIPTS_FOLDER=jobScripts
mkdir -p $JOB_SCRIPTS_FOLDER
for i in $(seq 1 $numberOfArgumentLines); do
    js="$JOB_SCRIPTS_FOLDER/$(basename $1)_$i.js"
    rm -f $js
    echo ${argumentLines[$i]} $js
    
    echo "#!/bin/bash" > $js
    echo "#PBS -r n" >> $js
    echo "#PBS -N $(basename $1)_$i" >> $js
    echo "#PBS -P $(basename $1)_project" >> $js
    echo "#PBS -p 0" >> $js
    echo "#PBS -l walltime=$2" >> $js
    echo "#PBS -l mem=$3" >> $js
    echo "#PBS -j oe" >> $js
    echo "#PBS -koed" >> $js
    echo "#PBS -Roe" >> $js
    echo "cd $PBS_O_WORKDIR" >> $js
    echo "/home/sgerloff2/pbs/$(basename $1)/$(basename $1) ${argumentLines[$i]}" >> $js
    qsub $js
done

