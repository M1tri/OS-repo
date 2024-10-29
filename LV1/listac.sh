if [ "$#" -eq "1" ]; then

	if [ -d $1 ]; then
		for file in $1/*; do
			echo $file
		done
	else
		echo "Uneti argument nije direktorijum"
	fi
else
	echo "Morate uneti jedan argument"
fi
