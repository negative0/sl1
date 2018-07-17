#!/bin/bash

echo -n 'Enter Filename->'
read filename
if [ -e $filename ]
then
	echo 'File Exists'
else
	touch $filename
	echo 'File Created'
fi

op=0

while [ $op -ne 5 ]
do
echo -n "Operations:\n1.Add Record\n2.Delete Record\n3.Update Record\n4:Display\n5.Exit\nYour Option->"
read op

case "$op" in
	1) echo -n "Enter the name:->"
	read name
	echo -n "Enter the address->"
	read address
	echo "$name\t$address" >> $filename
	;;

	2)echo -n "Enter name to delete->"
	read deletename
	grep -v $deletename $filename > temp
	rm $filename
	mv temp $filename
	echo "Record Deleted"
	;;

	3)echo -n "Enter name to modify->"
	read modify
	grep -v $modify $filename > temp
	echo -n "Enter the new name->"
	read name
	echo -n "Enter the new Address->"
	read address
	echo "$name\t$address" >> temp
	rm $filename
	mv temp $filename
	echo "Record Modified";
	;;

	4)echo "\nName\tAddress"
	cat $filename
	;;

	5)echo "Exiting"
	echo "Thank You!"
	;;

	*)echo "Invalid Option. Please try again!"
	;;
esac
done


