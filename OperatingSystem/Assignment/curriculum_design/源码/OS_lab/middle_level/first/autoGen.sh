#!/bin/bash
target="origin.sh"
echo "the PID of second.sh is $$"
echo "#!/bin/bash">${target}
echo 'filename="content.txt"'>>${target}
echo 'echo 'write or read:''>>${target}
echo 'read limit'>>${target}
echo "content="817MYFILE"">>${target}
echo 'if [ $limit == "read" ]'>>${target}
echo "then">>${target}
	echo 'cat ${filename} | while read line'>>${target}
echo "do">>${target}
	echo 'echo ${line}'>>${target}
echo 'done'>>${target} 
echo 'else'>>${target}
	echo 'echo "${content}">${filename}'>>${target}
echo 'fi'>>${target}
echo 'echo 'the PID of first.sh is $$''>>${target}
source ./${target}
