#include <stdio.h>

typedef struct Process {
    int pid;
    int arrival_time;  // Arrival time in queue
    int burst_time;
    int priority;      // Priority of the process
    int waiting_time;
    int turnaround_time;
} Process;

void priority_scheduling(Process p[], int n) {
    int i, j;
    int total_waiting_time = 0, total_turnaround_time = 0;

    // Sorting the processes based on arrival time and priority
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (p[i].arrival_time > p[j].arrival_time ||
               (p[i].arrival_time == p[j].arrival_time && p[i].priority > p[j].priority)) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Calculate waiting time and turnaround time for each process
    p[0].waiting_time = 0;
    p[0].turnaround_time = p[0].burst_time;
    for (i = 1; i < n; i++) {
        int prev_burst_time = 0;
        for (j = 0; j < i; j++) {
            prev_burst_time += p[j].burst_time;
        }
        p[i].waiting_time = prev_burst_time - p[i].arrival_time;
        if (p[i].waiting_time < 0) {
            p[i].waiting_time = 0;  // If it arrives in queue after previous processes are executed
        }
        p[i].turnaround_time = p[i].burst_time + p[i].waiting_time;
    }

    // Print the schedule
    printf("PID\tAT\tBT\tPR\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].priority, p[i].waiting_time, p[i].turnaround_time);
        total_waiting_time += p[i].waiting_time;
        total_turnaround_time += p[i].turnaround_time;
    }

    // Calculate average waiting time and average turnaround time
    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);

    // Printing the Gantt chart
    int timeline = 0;
    printf("Gantt Chart:\n");
    for (i = 0; i < n; i++) {
        if (p[i].arrival_time > timeline) {
            printf("%d|--- idle ---|", timeline);
            timeline = p[i].arrival_time;
        }
        printf("%d|--- P%d ---|", timeline, p[i].pid);
        timeline += p[i].burst_time;
    }
    printf("%d\n", timeline);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process p[n];
    printf("Enter the arrival time, burst time, and priority for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &p[i].burst_time);
        printf("Priority: ");
        scanf("%d", &p[i].priority);
    }
    
    priority_scheduling(p, n);
    
    return 0;
}

