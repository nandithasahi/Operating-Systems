#include <stdio.h>

typedef struct Process {
    int pid;           // Process ID
    int arrival_time;   // Arrival time of the process
    int burst_time;     // Burst time of the process
    int remaining_time; // Remaining time (initially equal to burst time)
    int waiting_time;   // Waiting time
    int turnaround_time;// Turnaround time
} Process;

void round_robin_scheduling(Process p[], int n, int time_quantum) {
    int time = 0;       // Current time
    int done = 0;       // Number of processes that have completed
    int total_waiting_time = 0, total_turnaround_time = 0;

    // Initialize remaining time for each process (same as burst time initially)
    for (int i = 0; i < n; i++) {
        p[i].remaining_time = p[i].burst_time;
    }

    // Repeat the process execution cycle until all processes are completed
    while (done < n) {
        for (int i = 0; i < n; i++) {
            if (p[i].remaining_time > 0 && p[i].arrival_time <= time) {
                // If the process has remaining time and has arrived
                if (p[i].remaining_time > time_quantum) {
                    // If remaining time is more than time quantum, execute it for a full quantum
                    time += time_quantum;
                    p[i].remaining_time -= time_quantum;
                } else {
                    // If remaining time is less than or equal to time quantum, finish the process
                    time += p[i].remaining_time;
                    p[i].waiting_time = time - p[i].arrival_time - p[i].burst_time;
                    p[i].turnaround_time = time - p[i].arrival_time;
                    p[i].remaining_time = 0; // Process is done
                    done++; // Increment the count of finished processes
                    total_waiting_time += p[i].waiting_time;
                    total_turnaround_time += p[i].turnaround_time;
                }
            }
        }
    }

    // Print the results
    printf("PID\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].waiting_time, p[i].turnaround_time);
    }

    // Calculate and print average waiting time and average turnaround time
    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);

    // Gantt Chart
    printf("Gantt Chart:\n");
    time = 0;
    while (done < n) {
        for (int i = 0; i < n; i++) {
            if (p[i].remaining_time > 0 && p[i].arrival_time <= time) {
                if (p[i].remaining_time > time_quantum) {
                    printf("%d|--- P%d ---|", time, p[i].pid);
                    time += time_quantum;
                    p[i].remaining_time -= time_quantum;
                } else {
                    printf("%d|--- P%d ---|", time, p[i].pid);
                    time += p[i].remaining_time;
                    p[i].remaining_time = 0;
                    done++;
                }
            }
        }
    }
    printf("%d\n", time);
}

int main() {
    int n, time_quantum;

    // Input number of processes and time quantum
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    Process p[n];

    // Input arrival time and burst time for each process
    printf("Enter the arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &p[i].burst_time);
    }

    // Call round robin scheduling function
    round_robin_scheduling(p, n, time_quantum);

    return 0;
}

