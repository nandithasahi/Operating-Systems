#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int n; // Number of processes
int m; // Number of resources
int alloc[MAX][MAX]; // Allocation matrix
int max[MAX][MAX]; // Maximum demand matrix
int avail[MAX]; // Available resources

// Function to take input for matrices and available resources
void input() {
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    printf("Enter the Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter the MAX Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the Available Resources:\n");
    for (int j = 0; j < m; j++) {
        scanf("%d", &avail[j]);
    }
}

// Function to calculate the need matrix
void calculateNeed(int need[MAX][MAX]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

// Function to check if the system is in a safe state
bool isSafe(int need[MAX][MAX]) {
    bool finish[MAX] = {false}; // Array to track completed processes
    int work[MAX]; // Copy of available resources

    // Initialize work with available resources
    for (int j = 0; j < m; j++) {
        work[j] = avail[j];
    }

    int count = 0; // Count of processes that can finish

    while (count < n) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canProceed = true;

                // Check if the process can proceed
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canProceed = false;
                        break;
                    }
                }

                // If the process can proceed, allocate resources to it
                if (canProceed) {
                    for (int j = 0; j < m; j++) {
                        work[j] += alloc[i][j];
                    }
                    finish[i] = true; // Mark process as finished
                    found = true;
                    count++;
                }
            }
        }

        // If no process can proceed, then there is a potential deadlock
        if (!found) {
            return false; // Not in a safe state
        }
    }

    return true; // In a safe state
}

// Function to detect if there is a deadlock
void detectDeadlock() {
    int need[MAX][MAX];
    calculateNeed(need);

    if (isSafe(need)) {
        printf("No deadlock detected.\n");
    } else {
        printf("Deadlock detected among processes.\n");
    }
}

int main() {
    input();
    detectDeadlock();
    return 0;
}

