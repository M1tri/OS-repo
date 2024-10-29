if [ "$#" -eq 1 ]; then

	if [ -d "$1" ]; then

		cd $1
		if [ ! -d "KOPIJA" ]; then
			mkdir KOPIJA
		fi

		for file in *; do
			case $file in
				*.c) cp $file KOPIJA/$file.bck;;
				*) ;;
			esac
		done
	else
		echo "Uneti argument mora biti direktorijum"
	fi
else
	echo "Morate uneti jedan argument"
fi
