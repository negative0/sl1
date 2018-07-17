#/bin/sh
echo 'Enter First Number:\n->'
read a
echo 'Enter Second Number:\n->'
read b
echo '\n1:Add\n2:Sub\nYour Choice:'
read option
case "$option" in
	1)add=`expr $a \+ $b`
	echo "Addition is:" $add;;
	2)sub=`expr $a \- $b`
	echo "Subtraction is:" $sub;;
	*)echo 'Invalid Option';;
esac
	
