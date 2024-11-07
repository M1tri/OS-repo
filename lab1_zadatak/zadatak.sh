if [ $# -ge 2 ]; then

	if [ -d $1 ]; then
	
		cd $1

		shift 1
		for file in *.txt; do

			for arg in $@; do
			
				echo "$arg" >> $file
			done
		done
	else
		echo "Prvi argument mora biti putanja do direktorijuma!"
	fi
else
	echo "Minimalni broj argumenata je 2"

fi
