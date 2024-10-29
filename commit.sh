if [ $# -eq "1" ]; then

	git add *
	git commit -m "$1"
	git push

else
	echo "Neodgovarajc broj argumenata"
fi
