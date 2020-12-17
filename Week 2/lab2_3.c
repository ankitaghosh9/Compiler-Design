#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int main()
{
	FILE *fa;
    char c;
    int n=20; int len=20;
	char keyw[20][20] = {"const", "bool", "char", "int","float", "double","return", "for", "while", "do", "switch","if", "else","case", "break","printf"};


	fa = fopen("input.c", "r");
	if (fa == NULL)
	{
		printf("Cannot open file \n");
		exit(0); 
	}
	
	c=getc(fa);
	printf("Keywords are:\n");
	while(c!=EOF)
	{
		if(isalpha(c))
		{
			char buf[100];
			int x=0;
			while(isalpha(c))
			{
				buf[x++]=c;
				c=getc(fa);
			}
			if(c==' '||c=='\t'||c=='\n'||c=='('||c=='{'||c==';')
			{
				// printf("entered blank %c\n",c);
				buf[x]='\0';
				int i;
				for(i=0;i<n;i++)
				{
					if(strcmp(buf,keyw[i])==0)
					{
						// printf("found match\n");
						for(int j=0;j<x;j++)
							printf("%c",toupper(buf[j]));
						printf("\n");
						break;
					}
				}
			}
			else
			{
				// printf("entered not blank  %c\n",c);
				while(c!=' ' && c!='\t' && c!='\n' && c!='{' && c!=';' && c!=EOF)
					c=getc(fa);
			}			
		}
		else
		{
			// printf("entered not blank out  %c\n",c);
			while(c!=' ' && c!='\t' && c!='\n' && c!=';'  && c!='{' && c!=EOF)
				c=getc(fa);
		}		
		if(c!=EOF)
			c=fgetc(fa);
	}
	fclose(fa);
	printf("Printing Completed\n");
}