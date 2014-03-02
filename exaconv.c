/* Exaconvert
 * by Giovanni Santostefano
 * 
 * Read a file with \xNN exadecimal data format
 * and returns the ascii conversion on the standard output
 * 
 * compile with
 * gcc -o exaconv exaconv.c
 * run with
 * $ ./exaconv filetoconvrt.txt
 */

#include <stdio.h>
#include <stdlib.h>


/* Convert the string of two chars into an int number*/
int ConvExa(char str[2])
{  
   if(!str)return 0;
   
   return ((int)(str[0]-'0')<<4)+((int)(str[1]-'0'));
}

   
/* Read a file and print out the conversion */
int ExaToAscii(char *filename)
{
   FILE *stream=NULL;
   char c;
   int counter=0;
   int flag=0;
   char buf[2];
   
   
   if(!filename) return -1;
   
   stream=fopen(filename, "r");
   if(!stream) return -1;
   
   counter=0;
   flag=0;
   while (EOF != (c = fgetc(stream)))
     {
      
	if(flag==0 && c=='\\')
	  {
	     flag=1;
	     continue;
	  }
	
	if(flag==1 && c!='x')
	  {
	     flag=0;
	     continue;
	  }
	else if(flag==1 && c=='x') /* \x found */
	  {
	     flag=2;
	     continue;
	  }
	
	/*found exa character*/
	if(flag==2 && ((c>='0' && c<='9') || (c>='a' && c<='f')))
	  {
	     /*add the character to the buffer*/
	     if(c>='0' && c<='9') buf[counter]=c;
	     else buf[counter]='9'+c-96;
	     counter++;
	     
	     /*if the buffer is full then convert*/
	     if(counter==2)
	       {
		  printf("%c",(unsigned char)ConvExa(buf));
		  flag=0;
		  counter=0;
		  buf[0]='\0';buf[1]='\0';
	       }
	     
	     continue;
	  }
	else if(flag==2)
	  {
	     flag=0; /*reset the flag to start searching a new one*/
	     counter=0;
	     buf[0]='\0';buf[1]='\0';
	     continue;
	  }
	
	
	
     }
   
   fclose(stream);
   return 0;
}


int main(int argc, char **argv)
{
   
   if(argc<2)
     {
	printf("\n\nUSAGE: exaconv exafile.txt\n");
	return -1;
     }
   
   
   return ExaToAscii(argv[1]);
	
}
 
