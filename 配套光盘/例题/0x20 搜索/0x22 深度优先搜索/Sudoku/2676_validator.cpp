#include <stdio.h>
#include <stdlib.h>
#include <string>

FILE *inf, *outf,*ansf, *logf;
std::string arg4;
char a[10][10],b[10][10],T,t;

void Terminate(char* s1, char* s2)
{
//  writeln(s);
	fprintf(logf,"<?xml version=\"1.0\"?>\n<result outcome=\"%s\" security=\"%s\">%s</result>\n",s1,arg4.c_str(), s2);
  exit(0);
}

void ReadD()
{
   int i,j;char s[16];
   for(i=1;i<=9;i++)
   {
      fscanf(inf,"%s",s);
	  for(j=1;j<=9;j++)
		  a[i][j]=s[j-1]-'0';
   }
}


void Check()
{
	int i,j,k,i1,j1;char s[16];
	for(i=1;i<=9;i++)
	{
	  fscanf(outf,"%s",s);
	  if(strlen(s)!=9)
	     Terminate("No - Wrong Answer","Short or long line");
	  for(j=1;j<=9;j++)
	  {
         b[i][j]=s[j-1]-'0';
		 if(b[i][j]<1||b[i][j]>9)
			 Terminate("No - Wrong Answer","Wrong value");
		 if(a[i][j]!=0&&a[i][j]!=b[i][j])
			 Terminate("No - Wrong Answer","Missfit with initial data");
	  }
	}
	// check in line
	for(i=1;i<=9;i++)
	{
		for(j=1;j<=9;j++) s[j]=0;
		for(j=1;j<=9;j++) 
		{
			if(s[b[i][j]]==1)
			    Terminate("No - Wrong Answer","Wrong line");
		    else b[i][j]=1;
		}
	}
	// check in column
	for(j=1;j<=9;j++)
	{
		for(i=1;i<=9;i++) s[i]=0;
		for(i=1;i<=9;i++) 
		{
			if(s[b[i][j]]==1)
			    Terminate("No - Wrong Answer","Wrong column");
		    else b[i][j]=1;
		}
	}
    // check in squares
	for(i=1;i<=9;i+=3)
	{
		for(j=1;j<=9;j+=3) 
		{
			for(k=1;k<=9;k++) s[k]=0;
			for(i1=0;i1<3;i1++)
				for(j1=0;j1<3;j1++)
					if(s[b[i+i1][j+j1]]==1)
                        Terminate("No - Wrong Answer","Wrong square");
		    else b[i+i1][j+j1]=1;
		}
	}
}

void main(int argc, char* argv[])
{
	arg4 = argv[4];
    logf=fopen(argv[4],"w");
    if((outf=fopen(argv[2],"r"))==NULL) 
	  Terminate("No - Wrong Answer","Error opening output file");
	inf=fopen(argv[1],"r");
    fscanf(inf,"%d",&T);
    for(t=1;t<=T;t++)
	{
       ReadD();
       Check();
	}
    Terminate("accepted","OK");
}
