if [ $# -eq 1 ]; then

	if [ -d $1 ]; then

		ls -al $1

	else
		echo "Uneti argument nije direktorijum"
	fi
else
	echo "Unesi jedan argument"
fi
