#!/bin/bash
filename="content.txt"
echo write or read:
read limit
content=817MYFILE
if [ $limit == "read" ]
then
cat ${filename} | while read line
do
echo ${line}
done
else
echo "${content}">${filename}
fi
echo the PID of first.sh is 66890
