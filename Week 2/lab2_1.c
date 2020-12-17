#include <stdio.h>
#include <stdlib.h>


int main()
{
	FILE *fa, *fb;
	int ca, cb; int bs=' ';

    fa=fopen("sample1.txt", "r");
    fb=fopen("sample1out.txt","w");

    if(fa==NULL || fb == NULL)
    {
    	printf("Invalid files\n");
    	exit(0);
    }

    ca=getc(fa);

    while(ca!=EOF)
    {
    	if(ca!='\t' && ca!=' ')
    	{
    		putc(ca,fb);
    	}
    	else
    	{
    		if(ca=='\t')
    			putc(bs,fb);
    		else
    		{
    			while(ca==' ')
    				ca=getc(fa);
    			putc(bs,fb);
                putc(ca,fb);
    		}
    	}
    	ca=getc(fa);
    }
    fclose(fa);
    fclose(fb);
}