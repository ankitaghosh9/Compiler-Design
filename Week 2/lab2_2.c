#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *directives[] = {"#include","#define","#if"};

int is_directive(const char *str)
{
	for(int i = 0; i < sizeof(directives)/sizeof(char *); i++) 
	   {
		int len = strlen(directives[i]);
		if(strncmp(str, directives[i], len) == 0)
		  {
			return 1;
		  }
	   }

	return 0;
}

int main()
{
	char buf[2048];
	FILE *f1,*f2;
	f1 = fopen("input.c", "r");
    f2 = fopen("output2.c", "w");
    if(f1 == NULL || f2 == NULL)
      {
        perror("Invalid files\n");
        return 1;
      }
	while(fgets(buf, 2048, f1) != NULL)
		 {
			if(!is_directive(buf))
			  { 
				fputs(buf, f2);
			  }
	     }
	fclose(f1);
    fclose(f2);
}