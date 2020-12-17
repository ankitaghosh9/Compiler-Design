#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexanls.h"


void program();
void declarations();
void data_type();
void identifier_list();
void assign_stat();


struct token curr;
FILE *f1;

void invalid()
{
	printf("error");
	exit(0);
}

//PROGRAM FUNCTION
void program()
{
	curr=getNextToken(f1);
	if(isdtype(curr.lexeme))
	{
	  curr=getNextToken(f1);
	  if(strcmp(curr.lexeme,"main")==0)
	  {
		curr=getNextToken(f1);
		if(strcmp(curr.lexeme,"(")==0)
		{
			curr=getNextToken(f1);
			if(strcmp(curr.lexeme,")")==0)
			{
				curr=getNextToken(f1);
				if(strcmp(curr.lexeme,"{")==0)
				{
					curr=getNextToken(f1);
					declarations();
					assign_stat();
					if(strcmp(curr.lexeme,"}")==0)
					{
						return;
					}
					else
					{
						printf("\n missing } at row:%d and col:%d.\n",curr.row,curr.col);
						exit(0);
					}
				}
				else
				{
					printf("\n missing { at row:%d and col:%d.\n",curr.row,curr.col);
					exit(0);
				}
			}
			else
			{
				printf("\n missing ) at row:%d and col:%d.\n",curr.row,curr.col);
				exit(0);
			}
		}
		else
		{
			printf("\n missing ( at row:%d and col:%d.\n",curr.row,curr.col);
			exit(0);
		}
	}
	else
	{
		printf("\n missing main function\n");
		exit(0);
	}
  }
  else
  {
	printf("\n missing return datatype of function\n");
	exit(0);
  }
}


//DECLARATION FUNCTION
void declarations()
{
	if(isdtype(curr.lexeme))
	{
		data_type();
		identifier_list();

		if(strcmp(curr.lexeme,";")==0)
		{
			curr=getNextToken(f1);
			declarations();
	    }
		else printf("\n missing ; at row:%d and col:%d.\n",curr.row,curr.col);
	}

}


//DATA TYPE FUNCTION
void data_type()
{
	if(strcmp(curr.lexeme,"int")==0)
	{
		curr=getNextToken(f1);
		return;
	}
	else if(strcmp(curr.lexeme,"char")==0)
	{
		curr=getNextToken(f1);
		return;
	}
	else
	{
		printf("\n missing data type at row:%d and col:%d.\n",curr.row,curr.col);
		exit(0);
	}
}


//INDENTIFIER FUNCTION
void identifier_list()
{
	if(strcmp(curr.type,"IDENTIFIER")==0)
	{
		curr=getNextToken(f1);
		if(strcmp(curr.lexeme,",")==0)
		{
			curr=getNextToken(f1);
			identifier_list();
		}
		else return;
	}
	else
	{
		printf("\n missing identifier at row:%d and col:%d.\n",curr.row,curr.col);
		exit(0);
	}
}


 
//ASSIGN FUNCTION
void assign_stat()
{
	if(strcmp(curr.type,"IDENTIFIER")==0)
	{
		curr=getNextToken(f1);
		if(strcmp(curr.lexeme,"=")==0)
		{
			curr=getNextToken(f1);
			if(strcmp(curr.type,"IDENTIFIER")==0)
			{
				curr=getNextToken(f1);
				if(strcmp(curr.lexeme,";")==0)
				{
					curr=getNextToken(f1);
					return;
				}
			}
			else if(strcmp(curr.type,"NUMBER")==0)
			{
				curr=getNextToken(f1);
				if(strcmp(curr.lexeme,";")==0)
				{
					curr=getNextToken(f1);
					return;
				}
				else
				{
					printf("\n missing ; at row:%d and col:%d.\n",curr.row,curr.col);
					exit(0);
				}
			}
			else
			{
				printf("\n missing identifier at row:%d and col:%d.\n",curr.row,curr.col);
				exit(0);
			}
		}
		else
		{
			printf("\n missing = at row:%d and col:%d.\n",curr.row,curr.col);
			exit(0);
		}
	}
	else
	{
		printf("\n missing identifier at row:%d and col:%d.\n",curr.row,curr.col);
		exit(0);
	}
}


//MAIN FUNCTION
int main()
{
	FILE *fa, *fb;
	int ca, cb;

	fa = fopen("inp_71.c", "r");
	if (fa == NULL)
	{
		printf("Invalid file\n");
		return 0;
	}

	fb = fopen("out_71.c", "w");
	ca = getc(fa);

	while (ca != EOF)
	{
		if(ca==' ')
		{
			putc(ca,fb);
			while(ca==' ')
				ca = getc(fa);
		}
		if (ca=='/')
		{
			cb = getc(fa);
			if (cb == '/')
			{
				while(ca != '\n')
					ca = getc(fa);
			}
			else if (cb == '*')
			{
				do
				{
					while(ca != '*')
						ca = getc(fa);
					ca = getc(fa);
				} while (ca != '/');
			}
			else
			{
				putc(ca,fb);
				putc(cb,fb);
			}
		}
		else putc(ca,fb);
		ca = getc(fa);
	}
	fclose(fa);
	fclose(fb);

	fa = fopen("out_71.c", "r");
	if(fa == NULL)
	{
		printf("Invalid file");
		return 0;
	}

	fb = fopen("temp.c", "w");
	ca = getc(fa);
	while(ca != EOF)
	{
		if(ca == '#')
		{
			while(ca != '\n')
			{
				ca = getc(fa);
			}
		}
		ca = getc(fa);
		if(ca != EOF && ca != '#')
		{
			putc(ca, fb);
		}
	}

	fclose(fa);
	fclose(fb);
 

	fa = fopen("temp.c", "r");
	fb = fopen("out_71.c", "w");
	ca = getc(fa);

	while(ca != EOF)
	{
		putc(ca, fb);
		ca = getc(fa);
	}

	fclose(fa);
	fclose(fb);
	remove("temp.c");
	f1=fopen("out_71.c","r");

	if(f1==NULL)
	{
		printf("Invalid file\n");
		return 0;
	}

	struct token tkn;
	program();
	printf("\nProgram Compiled\n\n");
	fclose(f1);

	}