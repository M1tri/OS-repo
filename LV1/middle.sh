if [ $# -eq "2" ]; then
	file="text.txt"
	counter=0
	while IFS= read -r linija; do
			
		if [[ $counter -ge $1 && $counter -le $2 ]]; then	
			echo $linija
		fi
	#	echo counter: $counter
		counter=$((counter+1))

	done < $file
else
	echo "Morate uneti 2 argumenta"
fi
