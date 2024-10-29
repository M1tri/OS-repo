if test $# -eq "1"; then
	
	brojac=0
	while test $brojac -ne $1; do
		echo $brojac
		brojac=$((brojac+1))
	done
else
	echo "Morate uneti jedan argument"
fi
