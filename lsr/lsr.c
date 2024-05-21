// LSR

#include<stdio.h>
#include<limits.h>
void main()
{
    int i,j,H,ad[50][50],d;
    printf("Link State routing Protocol \n Enter the number of hops:");
    scanf("%d",&H);
    printf("Enter the adjacency matrix: \n");
    for(i=0;i<H;i++)
    {
    for(j=0;j<H;j++)
    {
        scanf("%d",&ad[i][j]);
    }
    }
    int dist[H],visited[H],bound,v;
    for(j=0;j<H;j++)
    {
        dist[j]=INT_MAX;
        visited[j]=0;
    }
    dist[0]=0;
    for(bound=0;bound<H-1;bound++)
    {
        int min=INT_MAX,min_index;
        for(v=0;v<H;v++)
        {
            if(visited[v]==0 && dist[v]<min)
            {
                min=dist[v];
                min_index=v;
            }
        }
        visited[min_index]=1;
        for(d=1;d<=H;d++)
        {
            if(!visited[d] && ad[min_index][d] && dist[min_index]!=INT_MAX && dist[min_index]+ad[min_index][d]<dist[d])
            {
                dist[d]=dist[min_index]+ad[min_index][d];
            }
        }
        printf("\n");
    }
    printf("vertex\t\tDistance from source\n");
    for(i=0;i<H;i++)
    {
    	printf("%d\t\t%d\n",i,dist[i]);
    }
}
