/*
Consider a scheduling approach which is pre-emptive similar to shortest remaining
time first in nature. The priority of each job is dependent on its estimated run time, and
also the amount oftime it has spent waiting. Jobs gain higher priority the longer they
wait, which prevents indefinite postponement. The jobs that have spent a long time
waiting compete against those estimated to have short run times. The priority can be
computed as :
Priority = 1+ Waiting time / Estimated run time
Write a program to implement such an algorithm. Ensure
1. The input is given dynamically at run time by the user
2. The priority of each process is visible after each unit of time
3. The gantt chart is shown as an output
4. Calculate individual waiting time and average waiting time.

*/



#include<stdio.h>
#include<stdlib.h>


void sort_process(int*,int*,float*,int*,int);


int main(){
    int n;
    printf("Enter total number of process:- ");
    scanf("%d",&n);
    int estimated_runtime[n];
    int waiting_time[n];
    int process_id[n];
    for(int i=0;i<n;i++){
        printf("Enter run-time/burst-time for %dth Process:- ",(i+1));
        scanf("%d",&estimated_runtime[i]);
        waiting_time[i]=0;
        process_id[i]=i+1;
    }
    int total_process=0;
    float priority_for_process[n];
    printf("Gantt Chart:- \n");
    while(total_process<n){
        for(int i=0;i<n;i++)
            priority_for_process[i]=1+((float)waiting_time[i]/(float)estimated_runtime[i]);
        sort_process(estimated_runtime,waiting_time,priority_for_process,process_id,n);
        int exec_process=process_id[0];
        estimated_runtime[0]-=1;
        for(int i=1;i<n;i++){
            waiting_time[i]+=1;
        }
        if(estimated_runtime[0]==0){
            total_process++;
            waiting_time[0]-=estimated_runtime[0];
            priority_for_process[0]=-1;
        }
        else
            waiting_time[0]=waiting_time[0]+1;
        int count=0;
        for(int i=0;i<n;i++){
            if(estimated_runtime[i]==0)
                count++;
        }
        if(count==n)
            break;
        if(estimated_runtime[exec_process-1]!=0)
            printf("P%d-> ",exec_process);
    }
    printf("Completed\n");
    int total_waiting_time=0;
    for(int i=0;i<n;i++){
        printf("Process %d Waiting Time:- %d\n",process_id[i],waiting_time[i]);
        total_waiting_time+=waiting_time[i];
    }
    float average_waiting_time=(float)total_waiting_time/(float)n;
    printf("Average Waiting Time:- %.3f",average_waiting_time);
    return 0;
}


void sort_process(int *estimated_runtime,int *waiting_time,float *priority_for_process,int *process_id,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-1;j++){
            if(priority_for_process[j]<priority_for_process[j+1]){
                float t1=priority_for_process[j];
                priority_for_process[j]=priority_for_process[j+1];
                priority_for_process[j+1]=t1;
                int t2=estimated_runtime[j];
                estimated_runtime[j]=estimated_runtime[j+1];
                estimated_runtime[j+1]=t2;
                int t3=waiting_time[j];
                waiting_time[j]=waiting_time[j+1];
                waiting_time[j+1]=t3;
                int t4=process_id[j];
                process_id[j]=process_id[j+1];
                process_id[j+1]=t4;
            }
        }
    }
}

