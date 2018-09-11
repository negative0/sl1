#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/types.h>
int main()
{ 
int p1[2],p2[2],i;
char buf[5];
pipe(p1);
pipe(p2);
if(fork()==0)
{
printf("\n this is child(the input text is text1)\n");
close(p1[0]);
close(p2[1]);
write(p1[1],"text1\n",5);
read(p2[0],buf,5);
write(1,buf,5);
}
else
{ sleep(1);
printf("\n this is parent(the input text is text2)\n");
close(p2[0]);
close(p1[1]);
read(p1[0],buf,5);
write(1,buf,5);
write(p2[1],"text2\n",5);
}
}
