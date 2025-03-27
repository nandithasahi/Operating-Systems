#include <stdio.h>
#include <stdlib.h>
typedef struct {
 int pid;
 int arrival_time;
 int burst_time;
 int waiting_time;
 int turnaround_time;
 int completion_time;
 int is_completed;
} Process;
int compareArrival(const void* a, const void* b) {
 Process* p1 = (Process*)a;
 Process* p2 = (Process*)b;
 return p1->arrival_time - p2->arrival_time;
}
int findNextProcess(Process processes[], int n, int current_time) {
 int min_burst_time = __INT_MAX__;
 int idx = -1;
 for (int i = 0; i < n; i++) {
 if (processes[i].arrival_time <= current_time && !processes[i].is_completed) {
 if (processes[i].burst_time < min_burst_time) {
 min_burst_time = processes[i].burst_time;
 idx = i;
 }
 }
 }
 return idx;
}
void stf_scheduling(Process processes[], int n) {
 int total_waiting_time = 0;
 int total_turnaround_time = 0;
 int current_time = 0;
 int completed_processes = 0;
 qsort(processes, n, sizeof(Process), compareArrival);
 printf("\nProcessID\tArrivalTime\tBurstTime\tWaitingTime\tTurnaroundTime\n");
 while (completed_processes < n) {
 int idx = findNextProcess(processes, n, current_time);
 if (idx == -1) {
 current_time++;
 } else {
 Process* process = &processes[idx];
 if (current_time < process->arrival_time) {
 current_time = process->arrival_time;
 }
 process->waiting_time = current_time - process->arrival_time;
 current_time += process->burst_time;
 process->completion_time = current_time;
 process->turnaround_time = process->completion_time - process->arrival_time;
 process->is_completed = 1;
 total_waiting_time += process->waiting_time;
 total_turnaround_time += process->turnaround_time;
 completed_processes++;
 printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", process->pid, process->arrival_time,
 process->burst_time, process->waiting_time, process->turnaround_time);
 }
 }
 double avg_waiting_time = (double)total_waiting_time / n;
 double avg_turnaround_time = (double)total_turnaround_time / n;
 printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
 printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
 printf("\nGantt Chart:\n| ");
 for (int i = 0; i < n; i++) {
 if (processes[i].is_completed) {
 printf("%d | ", processes[i].pid);
 }
 }
 printf("\n0");
 for (int i = 0; i < n; i++) {
 if (processes[i].is_completed) {
 printf(" --%d--", processes[i].completion_time);
 }
 }
 printf("\n");
}
int main() {
 int n;
 printf("Enter the number of processes: ");
 scanf("%d", &n);
 Process* processes = (Process*)malloc(n * sizeof(Process));
 for (int i = 0; i < n; i++) {
 printf("Enter process id, arrival time, and burst time for process %d: ", i + 1);
 scanf("%d %d %d", &processes[i].pid, &processes[i].arrival_time, 
&processes[i].burst_time);
 processes[i].is_completed = 0;
 }
 stf_scheduling(processes, n);
 free(processes);
 return 0;
}
