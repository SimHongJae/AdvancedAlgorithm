#include "kernel.h"


void sort_elements(element *elements, int start, int end) {
    if (start >= end)
        return;

    int pivot = start;
    int i = pivot + 1;
    int j = end;
    element temp;
    while (i <= j)
    {
        while (i <= end && elements[i].value <= elements[pivot].value)
        {
            i++;
        }
        while (j > start && elements[j].value >= elements[pivot].value)
        {
            j--;
        }
        if (i > j)
        {
            temp = elements[j];
            elements[j] = elements[pivot];
            elements[pivot] = temp;
        }
        else
        {
            temp = elements[i];
            elements[i] = elements[j];
            elements[j] = temp;
        }
    }
    sort_elements(elements, start, j - 1);
    sort_elements(elements, j + 1, end);
}

int partition_by_greedy(element *elements, int nmemb)
{
    sort_elements(elements, 0,nmemb-1);
    int sum0=0,sum1=0;
    for (int i= 0 ; i <nmemb;i++){
        if(sum0<=sum1){
            sum0+= elements[i].value;
            elements[i].groupId[0]=0;
            fprintf(stderr,"sum0 : %d %d\n", sum0, elements[i].value);
        }
        else{
            sum1+= elements[i].value;
            elements[i].groupId[0]=1;
            fprintf(stderr,"sum1 : %d %d\n", sum1, elements[i].value);
        }
    }
 
    return 1;
}

void dp(int level,element *elements,int* part_left,int *part_right,int nmemb_left,int nmemb_right,int sum_left,int sum_right,int half_sum,int *num_partitionable){
    //fprintf(stderr,"%d %d %d    4444555555555555\n\n",level,nmemb_left,nmemb_right);
    
    int* left = (int *)malloc(sizeof(int) * (nmemb_left+2));
    int* right = (int *)malloc(sizeof(int) * (nmemb_right+2));
    memcpy(left, part_left,sizeof(int)*nmemb_left);
    memcpy(right,part_right,sizeof(int)*nmemb_right);
    



    int num_partitionablee=*num_partitionable;
    if(level==0){
        
        int nmemb=nmemb_left+nmemb_right;

        element* elementss = (element *)malloc(sizeof(element)*(nmemb+2));
        memcpy(elementss,elements,sizeof(element)*nmemb);
        
        

        for(int i=0;i<nmemb_left;i++){
            for(int j=0;j<nmemb;j++){
                if(elementss[j].index==left[i]){
                  //  fprintf(stderr,"%d %d 0\n", j,elementss[j].value);
                    elementss[j].groupId[num_partitionablee]=0;
                    break;
                }
            }
        }

        for(int i=0;i<nmemb_right;i++){
            for(int j=0;j<nmemb;j++){
                if(elementss[j].index==right[i]){
                   // fprintf(stderr,"%d %d 1\n", j,elementss[j].value);
                    elementss[j].groupId[num_partitionablee]=1;
                    break;
                }
            }
        }
        
        for(int i=0;i<nmemb;i++){
            elements[i]=elementss[i];
        }

        free(elementss);

        (num_partitionablee)++;
       
       

    }

    else{
        //fprintf(stderr,"@@@@@@@@@\n");
        if((sum_left+elements[level-1].value<=half_sum)){

            //fprintf(stderr,"@@@@@@@@@\n");

            left[nmemb_left]=elements[level-1].index;
            nmemb_left++;
            sum_left += elements[level-1].value;
            dp(level-1,elements, left,right,nmemb_left,nmemb_right,sum_left,sum_right,half_sum,&num_partitionablee);
            left[nmemb_left]=-1;
            nmemb_left--;
            sum_left -= elements[level-1].value;
        }

        if((sum_right+elements[level-1].value<=half_sum)){

            //fprintf(stderr,"@@@@@@@@@\n");

            right[nmemb_right]=elements[level-1].index;
            nmemb_right++;
            sum_right += elements[level-1].value;
            dp(level-1,elements, left,right,nmemb_left,nmemb_right,sum_left,sum_right,half_sum,&num_partitionablee);
            right[nmemb_right]=-1;
            nmemb_right--;
            sum_right -= elements[level-1].value;
        }


    }

    free(left);
    free(right);
    *num_partitionable=num_partitionablee; 
     //fprintf(stderr,"num_partitionable : %d \n", *num_partitionable);
    
}

int partition_by_dp(element *elements, int nmemb)
{
   int half_sum=0;
   int num_partitionable=0;
    sort_elements(elements, 0,nmemb-1);
    for(int i=0;i<nmemb;i++){
        half_sum+=elements[i].value;
    }
    half_sum/=2;
    int* left = (int *)malloc(sizeof(int) * 2);
    int* right = (int *)malloc(sizeof(int) * 2);
    
    left[0]=elements[nmemb-1].index;
    
    
    dp(nmemb-1,elements, left,right,1,0,elements[nmemb-1].value,0,half_sum,&num_partitionable);
    
    free(left);
    free(right);
    
    return num_partitionable;

    /*
     TODO : Partition the elements using Dynamic Programming algorithm.
     - You might want to use the sorting algorithm implemented.
     - Your elementry goal is to tell whether the given set of numbers are partionable and show one solution.
     - Your secondary goal is to tell all the possible cases of parititioning.
     - Returns 0 if not partitionable, else number of available partitions.
    */

 
}
