#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int turnaround_time;
    int waiting_time;
    int completion_time;
} Process;

int compareArrival(const void* a, const void* b) {
    return ((Process*)a)->arrival_time - ((Process*)b)->arrival_time;
}

void fcfs_scheduling(Process process[], int n) {
    int current_time = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    qsort(process, n, sizeof(Process), compareArrival);

    printf("\nPID\tARRIVAL TIME\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");

    for (int i = 0; i < n; i++) {
        if (current_time < process[i].arrival_time) {
            current_time = process[i].arrival_time;
        }

        process[i].waiting_time = current_time - process[i].arrival_time;
        process[i].completion_time = current_time + process[i].burst_time;
        process[i].turnaround_time = process[i].waiting_time + process[i].burst_time;

        total_waiting_time += process[i].waiting_time;
        total_turnaround_time += process[i].turnaround_time;

        current_time += process[i].burst_time;

        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n",
               process[i].pid, process[i].arrival_time, process[i].burst_time,
               process[i].waiting_time, process[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f", (float)total_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process process[n];

    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        process[i].pid = i + 1;
        scanf("%d %d", &process[i].arrival_time, &process[i].burst_time);
    }

    fcfs_scheduling(process, n);

    return 0;
}

