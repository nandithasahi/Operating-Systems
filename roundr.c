#include <stdio.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;

void round_robin_scheduling(Process p[], int n, int time_quantum) {
    int time = 0, done = 0;
    int total_waiting_time = 0, total_turnaround_time = 0;

    // Initialize remaining time for each process (same as burst time initially)
    for (int i = 0; i < n; i++) {
        p[i].remaining_time = p[i].burst_time;
    }

    // Array to record the Gantt chart timeline and process IDs
    int gantt_chart[100];   // Arbitrary size for illustration, extend as needed
    int gantt_index = 0;

    // Process scheduling loop
    while (done < n) {
        int executed = 0; // Track if any process was executed in this cycle

        for (int i = 0; i < n; i++) {
            if (p[i].remaining_time > 0 && p[i].arrival_time <= time) {
                // Add process ID to Gantt chart
                gantt_chart[gantt_index++] = p[i].pid;
                
                if (p[i].remaining_time > time_quantum) {
                    time += time_quantum;
                    p[i].remaining_time -= time_quantum;
                } else {
                    time += p[i].remaining_time;
                    p[i].waiting_time = time - p[i].arrival_time - p[i].burst_time;
                    p[i].turnaround_time = time - p[i].arrival_time;
                    total_waiting_time += p[i].waiting_time;
                    total_turnaround_time += p[i].turnaround_time;
                    p[i].remaining_time = 0;
                    done++;
                }
                executed = 1;  // Process was executed in this cycle
            }
        }

        if (!executed) time++;  // If no process was executed, increment time
    }

    // Print the table
    printf("PID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].waiting_time, p[i].turnaround_time);
    }

    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);

    // Print Gantt Chart
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < gantt_index; i++) {
        printf(" P%d |", gantt_chart[i]);
    }
    printf("\n");
}

int main() {
    int n, time_quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    Process p[n];
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Process %d Arrival Time: ", p[i].pid);
        scanf("%d", &p[i].arrival_time);
        printf("Process %d Burst Time: ", p[i].pid);
        scanf("%d", &p[i].burst_time);
    }

    round_robin_scheduling(p, n, time_quantum);
    return 0;
}

