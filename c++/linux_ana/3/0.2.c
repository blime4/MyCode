#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void upcase(char *inputstring, char *newstring);

int main(void)
{
    	char *ssstring;
    	upcase("Hello",ssstring);
    	printf("str1=%s \n", ssstring);
	    upcase("Goodbye", ssstring);
    	printf("str2=%s\n", ssstring);
    	free(ssstring);
    	return 0;
}


void upcase(char *inputstring, char *newstring)
{
    	int counter;
    	if(!newstring)
    	{
        	if(!(newstring=(char*)realloc(NULL, strlen(inputstring)+1)))
		{
        		printf("ERROR ALLOCATING MEMORY! \n");
        		exit(255);
		}
    	}
    	else
    	{
        	if(!(newstring=(char*)realloc(newstring, sizeof(inputstring)+1)))
        	{
        		printf("ERROR REALLOCATING MEMORY! \n");
        		exit(255);
    		}
	}
        strcpy(newstring, inputstring);
	for(counter=0; counter<strlen(newstring); counter++)
	{
        	if(newstring[counter]>=97&&newstring[counter]<=122)
             		newstring[counter]-=32;
	}
	return ;
}
