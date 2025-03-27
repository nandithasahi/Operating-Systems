#include <stdio.h>
#define MAX_MATRIX 10
int max[MAX_MATRIX][MAX_MATRIX], allocation[MAX_MATRIX][MAX_MATRIX], need[MAX_MATRIX][MAX_MATRIX];
int avail[MAX_MATRIX];
int np, nr;//number of processes and number of resources
void readMatrix(int matrix[MAX_MATRIX][MAX_MATRIX])
{
    int i, j;
    for(i=0; i<np; i++)
    for(j=0; j<nr; j++)
    scanf("%d", &matrix[i][j]);
    return;
}
void displayMatrix(int matrix[MAX_MATRIX][MAX_MATRIX])
{
    int i, j;
    for(i=0; i<np; i++)
    {
        printf("\nP%d: ", i);
        for(j=0; j<nr; j++)
            printf(" %d", matrix[i][j]);
    }
    printf("\n");
    return;
}
void calculateNeed()
{
    int i,j;
    for(i=0; i<np; i++)
    for(j=0; j<nr; j++)
    need[i][j]=max[i][j]-allocation[i][j];
    return;
}
void banker()
{
    int i, j, k=0, flag;
    int finish[MAX_MATRIX], safe_seq[MAX_MATRIX];
    for (i=0; i<np; i++)
    {
        finish[i]=0;//initially all processes are incomplete
    }
    for (i=0; i<np; i++)
    {
        flag=0;
        if(finish[i]==0)
        {
            for(j=0; j<nr; j++)
            {
                if(need[i][j]>avail[j])
                {
                    flag=1;//Break a loop as need is greater than avail
                    break;
                }
            }
            if(flag==0)//need<avail, so complete processes
            {
                finish[i]=1;
                safe_seq[k]=i;
                k++;
                //add allocated resources of finished process in available resources
                for(j=0; j<nr; j++)
                    avail[j]+= allocation[i][j];
                //
                i=-1;
            }
        }
    }
    flag=1;//check if all processes are completed
    for(i=0; i<np; i++)
        if(finish[i]==0)
        {
            printf("\nThe system is in deadlock. \n");
            flag=i;
            break;
        }
    if(flag)
    {
        printf("\nSystem is in Safe State.\n");
        printf("Sequence is: \n");
        for(i=0; i<k; i++)
        {
            printf("P%d ->", safe_seq[i]);
        }
        printf("end\n");
    }
    return;
}
int main()
{
    int j=0;
    //read input
    {
        printf("\nEnter number of processes: ");
        scanf("%d", &np);
        printf("\nEnter number of resources: ");
        scanf("%d", &nr);
        printf("\nEnter initial allocation matrix: ");
        readMatrix(allocation);
        printf("\nEnter max requirement matrix: ");
        readMatrix(max);
        printf("\nEnter available resources: ");
        for(j= 0; j< nr; j++ )
            scanf("%d", &avail[j]);
        printf("\n");
    }
    //display entered data
    {
        printf("Entered Data: \n");
        printf("Initial Allocation: \n");
        displayMatrix(allocation);
        printf("Maximum Requirement: \n");
        displayMatrix(max);
    }
    //calculate and display need
    {
        calculateNeed();
        printf("Need is: \n");
        displayMatrix(need);
    }
    //execute processes using Banker's Algorithm
    banker();
    printf("\n");
    return 0;
}
