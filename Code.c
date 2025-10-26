#include<stdio.h>
#include<stdlib.h>

int std,secn,secmax;

int removed ( int s,int *z, int *p, int *R, int *d)
{
    int i,j,same=0,temp;
    do
    {
        same=s;
        for (j=2; j<=secn; j++)
        {
            for (i=0; i<secn; i++)
            {
                if (*(R+(s-1)*secn+i)==j)
                {
                    if (*(p+secmax-1+i*secmax)!=0)
                    {
                        if (*(d+s-1)>*(d+*(p+secmax-1+i*secmax)-1))
                        {
                            temp=*(p+secmax-1+i*secmax);
                            *(p+secmax-1+i*secmax)=s;
                            s=temp;
                        }
                    }
                    else
                    {
                        *(p+*(z+i)+i*secmax)=s;
                        (*(z+i))++;
                        return 0;
                    }
                    if (same!=s)
                        break;
                }
            }
            if (same!=s)
                break;
        }
    }
    while (same!=s);
    return 0;
}

int main()
{
    puts("enter number of students");
    scanf("%i",&std);
    puts("enter number of sections");
    scanf("%i",&secn);
    puts("enter max number of students in one section");
    scanf("%i",&secmax);
    int Rghba[std][secn];
    float degree[std];
    int student[std];
    int place[secn][secmax];
    int z[secn];
    int i,j,k,t,s1,s2,out,max,temp;
    for (i=0; i<secn; i++)
        z[i]=0;
    for (i=0; i<secn; i++)
        for (j=0; j<secmax; j++)
            place[i][j]=0;
    for (i=0; i<std; i++)
        student[i]=i+1;
    puts("enter the degrees");
    for (i=0; i<std; i++)
    {
        printf("\n%i student\n",i+1);
        scanf("%f",&degree[i]);
    }
    puts("enter the Rghbaat");
    for (i=0; i<std; i++)
    {
        printf("%i student\n",i+1);
        for (j=0; j<secn; j++)
            scanf("%i",&Rghba[i][j]);
    }
    for (t=1; t<=secn; t++)
    {
        for (i=0; i<=secn-1; i++)
        {
            for (j=0; j<std; j++)
            {
                if (student[j]==0)
                    continue;
                if (Rghba[j][i]==t)
                {
                    if (z[i]<=secmax-1)
                    {
                        place[i][z[i]]=student[j];
                        z[i]++;
                    }
                    else
                    {
                        if (degree[j]>degree[place[i][secmax-1]-1])
                        {
                            out=place[i][secmax-1];
                            place[i][secmax-1]=student[j];
                            removed (out,&z[0],&place[0][0],&Rghba[0][0],&degree[0]);
                        }
                    }
                    for (s1=0; s1<secmax-1; s1++)
                    {
                        if (place[i][s1]==0)
                            break;
                        max=s1;
                        for (s2=s1+1; s2<secmax; s2++)
                        {
                            if (place[i][s2]==0)
                                break;
                            if (degree[place[i][max]-1]<degree[place[i][s2]-1])
                                max=s2;
                        }
                        if (s1!=max)
                        {
                            temp=place[i][max];
                            place[i][max]=place[i][s1];
                            place[i][s1]=temp;
                        }
                    }
                }
            }
            for (k=0; k<secmax; k++)
                if (place[i][k])
                    student[place[i][k]-1]=0;
        }
    }
    for (i=0; i<secn; i++)
    {
        printf("%i section\n",i+1);
        for (j=0; j<secmax; j++)
        {
            printf("%i ",place[i][j]);
            if (j==secmax-1 || place[i][j+1]==0)
                break;
        }
        printf("\n least degree to enter is %0.2f \n*****\n",degree[place[i][j]-1]);
    }
    return 0;
}
