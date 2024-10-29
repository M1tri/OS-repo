if [ "$#" -eq "1" ]; then
	
	if [ -d $1 ]; then

		cd $1
		broj=0
		for file in *; do
			case $file in
				*.c) gcc $file -o $broj;broj=$((broj+1));;
				*.h) cat $file;;
				*) rm -f $file;;
			esac
		done

	else
		echo "Uneti argument nije ime direktorijum"
	fi
else
	echo "Morate uneti samo jedan argument"
fi
