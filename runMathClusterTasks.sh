#!/bin/bash
if [ $# -ne 1 ] ; then
	echo "expected syntax: runTasks <jobName>"
	exit 1
fi

OLD_IFS=$IFS
IFS=$'\n'
argumentLines=( $(cat "/work/gerloff/jobFiles/workDir/$1.argl") )
IFS=$OLD_IFS

echo "runTasks: /work/gerloff/jobFiles/workDir/$1 ${argumentLines[$SGE_TASK_ID]}"

/work/gerloff/jobFiles/workDir/$1 ${argumentLines[$SGE_TASK_ID]}
