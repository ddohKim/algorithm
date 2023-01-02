
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int col, row;
FILE* file;

int main(int argc,char **argv) {
   if(argc!=3)
   {printf("input error! AGAIN INPUT");
	   return 0;
   } 
	
   clock_t start, end;
    
   char file_name[100];
    int index;
    strcpy(file_name,argv[1]);
    index=atoi(argv[2]);
    file=fopen(file_name,"r");
    fscanf(file,"%d %d",&row,&col);

    int **array;
    array=(int **)malloc(sizeof(int*)*row);
    for(int i=0;i<row;i++){
        array[i]=(int*)malloc(sizeof(int)*col);
    }


    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++)
        {
            fscanf(file,"%d",&array[i][j]);
        }
    }

 int **neg_array;
    neg_array=(int **)malloc(sizeof(int*)*row);
    for(int i=0;i<row;i++){
        neg_array[i]=(int*)malloc(sizeof(int)*col);
    }

    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++)
        {
            neg_array[i][j]=array[i][j];
        }
    }
    int maxSum=0;
    int recSum=0;
    
    
    //O(n^6)
    if(index==1)
    {   start=clock();
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                for(int k=i;k<row;k++){
                    for(int h=j;h<col;h++){
                        recSum=0;
                        for( int a=i;a<=k;a++){
                            for( int b=j;b<=h;b++){
                                recSum+=array[a][b];
                            }
                        }
                        if(maxSum<recSum)
                            maxSum=recSum;
                    }
                }
            }
        }
        if(maxSum==0){
            maxSum=array[0][0];
            for(int i=0;i<row;i++){
                for(int j=0;j<col;j++)
                {
                    if(maxSum<array[i][j])
                        maxSum=array[i][j];
                }
            }
        }
        end=clock();
    }
    //O(n^4)
    else if(index==2){
        
    
        
        
    start=clock();
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(j>0)
            {array[i][j]+=array[i][j-1];
                if(i>0)
                    array[i][j]-=array[i-1][j-1];
            };
            if(i>0)
                array[i][j]+=array[i-1][j];
        }}
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            for(int k=i;k<row;k++){
                for(int h=j;h<col;h++){
                    recSum=array[k][h];
                    if(j>0)
                    {
                        recSum-=array[k][j-1];
                        if(i>0)recSum+=array[i-1][j-1];
                    }
                    if(i>0) recSum-=array[i-1][h];
                    if(maxSum<recSum)
                        maxSum=recSum;
                }
            }
        }
    }
        if(maxSum==0){
            maxSum=neg_array[0][0];
            for(int i=0;i<row;i++){
                for(int j=0;j<col;j++)
                {
                    if(maxSum<neg_array[i][j])
                        maxSum=neg_array[i][j];
                }
            }
        }
    end=clock();
}
 //O(n^3)
    else if(index==3){
        start=clock();
        for(int i=0;i<col;i++){
            int colMaxSum[row];
            memset(colMaxSum,0,sizeof(int)*row);
            for(int j=i;j<col;j++){
                for(int k=0;k<row;k++){
                    colMaxSum[k]+=array[k][j];
                }
                recSum=0;
                int submaxSum=colMaxSum[0];
                for(int k=0;k<row;k++){
                    recSum+=colMaxSum[k];
                    if(recSum<=-1){
                        recSum=0;
                        continue;
                    }
                    if(recSum>submaxSum)
                    {
                        submaxSum=recSum;
                    }
                    
                    
                }
                if(submaxSum>maxSum){
                    maxSum=submaxSum;
                }
            }
            
        }
        if(maxSum==0){
            maxSum=array[0][0];
            for(int i=0;i<row;i++){
                for(int j=0;j<col;j++)
                {
                    if(maxSum<array[i][j])
                        maxSum=array[i][j];
                }
            }
        }
        end=clock();
    }
    
    else{
        start=clock();
        end=clock();
    }

for(int i=0;i<row;i++){
    free(array[i]);
    free(neg_array[i]);
}
free(array);
free(neg_array);

char result_filename[100]="result_";
strcat(result_filename,file_name);
  FILE *result_fp=fopen(result_filename,"w");
    fprintf(result_fp,"%s\n%d\n%d\n%d\n%d\n%.1lf\n",file_name,index,row,col,maxSum,(double)end-start);
    fclose(file);
    fclose(result_fp);
    return 0;
}

