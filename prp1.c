//FIFO
#include <stdio.h>

int main() {
    int frames;
    int pageFaults = 0;

    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    // Assuming a maximum of 100 pages for simplicity
    int incomingStream[100];
    int pages;

    printf("Enter the number of pages: ");
    scanf("%d", &pages);

    printf("Enter the pages (space-separated): ");
    for (int i = 0; i < pages; i++) {
        scanf("%d", &incomingStream[i]);
    }

    printf("\nIncoming\tFrame 1\t\tFrame 2\t\tFrame 3\n");

    int temp[frames];
    
    // Initialize frames to -1 (indicating they are empty)
    for (int m = 0; m < frames; m++) {
        temp[m] = -1;
    }

    for (int m = 0; m < pages; m++) {
        int s = 0; // Flag to check if the page is already in a frame

        // Check if the page is already in one of the frames
        for (int n = 0; n < frames; n++) {
            if (incomingStream[m] == temp[n]) {
                s = 1; // Page found in frame
                break;
            }
        }

        // If the page was not found in any frame, we have a page fault
        if (s == 0) {
            pageFaults++;
            // If there is an empty frame, add the page there
            if (pageFaults <= frames) {
                temp[m % frames] = incomingStream[m];
            } else {
                // Replace the oldest page (FIFO)
                temp[(pageFaults - 1) % frames] = incomingStream[m];
            }
        }

        // Print the current state of frames
        printf("%d\t\t", incomingStream[m]);
        for (int n = 0; n < frames; n++) {
            if (temp[n] != -1) {
                printf("%d\t\t", temp[n]);
            } else {
                printf("-\t\t");
            }
        }
        printf("\n");
    }

    printf("Total Page Faults:\t%d\n", pageFaults);
    printf("Total Page Hits:\t%d\n", pages - pageFaults);

    return 0;
}

