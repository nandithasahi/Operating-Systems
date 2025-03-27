#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

// Function prototype for isSafe
bool isSafe(int processes[], int numProcesses, int numResources, int avail[], int max[][MAX_RESOURCES], int allot[][MAX_RESOURCES]);

// Function to read and validate integer input
bool readIntArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        if (scanf("%d", &array[i]) != 1) {
            printf("Invalid input. Please enter integers only.\n");
            return false; // Input was not valid
        }
    }
    return true; // All inputs were valid
}

// Definition of the isSafe function
bool isSafe(int processes[], int numProcesses, int numResources, int avail[], int max[][MAX_RESOURCES], int allot[][MAX_RESOURCES]) {
    int need[MAX_PROCESSES][MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {0};
    int safeSeq[MAX_PROCESSES];
    int work[MAX_RESOURCES];
    int count = 0;

    // Calculate the need matrix
    for (int i = 0; i < numProcesses; i++)
        for (int j = 0; j < numResources; j++)
            need[i][j] = max[i][j] - allot[i][j];

    // Initialize the work vector with available resources
    for (int i = 0; i < numResources; i++)
        work[i] = avail[i];

    // Find a safe sequence
    while (count < numProcesses) {
        bool found = false;
        
        for (int p = 0; p < numProcesses; p++) {
            if (!finish[p]) {
                int j;
                
                for (j = 0; j < numResources; j++)
                    if (need[p][j] > work[j])
                        break;

                if (j == numResources) {
                    // If a process's needs are met, mark it as finished
                    for (int k = 0; k < numResources; k++)
                        work[k] += allot[p][k];
                    
                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        // If no process could be completed, system is not in a safe state
        if (!found) {
            printf("System is not in a safe state\n");
            return false;
        }
    }

    // System is in a safe state; print the safe sequence
    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < count; i++)
        printf("%d ", safeSeq[i]);
    printf("\n");

    return true;
}

int main() {
    int processes[MAX_PROCESSES];
    int avail[MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int allot[MAX_PROCESSES][MAX_RESOURCES];
    int numProcesses, numResources;

    // Input the number of processes
    printf("Enter the number of processes: ");
    while (scanf("%d", &numProcesses) != 1 || numProcesses > MAX_PROCESSES || numProcesses < 1) {
        printf("Invalid number of processes. Enter a value between 1 and %d: ", MAX_PROCESSES);
        while (getchar() != '\n'); // clear the input buffer
    }

    // Input the number of resources
    printf("Enter the number of resources: ");
    while (scanf("%d", &numResources) != 1 || numResources > MAX_RESOURCES || numResources < 1) {
        printf("Invalid number of resources. Enter a value between 1 and %d: ", MAX_RESOURCES);
        while (getchar() != '\n'); // clear the input buffer
    }

    // Input available resources
    printf("Enter available resources (space-separated): ");
    while (!readIntArray(avail, numResources)) {
        printf("Enter available resources (space-separated): ");
        while (getchar() != '\n'); // clear the input buffer
    }

    // Input maximum resources needed by each process
    printf("Enter maximum resources needed by each process:\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("Process %d: ", i);
        while (!readIntArray(max[i], numResources)) {
            printf("Process %d: ", i);
            while (getchar() != '\n'); // clear the input buffer
        }
    }

    // Input allocated resources for each process
    printf("Enter allocated resources for each process:\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("Process %d: ", i);
        while (!readIntArray(allot[i], numResources)) {
            printf("Process %d: ", i);
            while (getchar() != '\n'); // clear the input buffer
        }
    }

    // Initialize process array
    for (int i = 0; i < numProcesses; i++)
        processes[i] = i;

    // Check if the system is in a safe state
    isSafe(processes, numProcesses, numResources, avail, max, allot);

    return 0;
}

