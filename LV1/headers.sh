if [ $# -eq "1" ]; then

	if [ -d $1 ]; then

		echo "Unesite ekstenziju preko tastature (bez tacke)"
		read extension
		pattern="*.$extension"
		cd $1

		for file in *; do
			case $file in
				$pattern) echo $file;;
				*);;
			esac
		done
	else
		echo "Uneti argument nije direktorijum"
	fi
else
	echo "Morate uneti jedan argument"
fi
