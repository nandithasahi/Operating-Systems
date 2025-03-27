#include <stdio.h>
#include <limits.h>

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

    printf("\nIncoming\tFrame 1 \tFrame 2 \tFrame 3\n");

    int temp[frames];

    // Initialize frames to -1 (empty)
    for (int m = 0; m < frames; m++) {
        temp[m] = -1;
    }

    // Loop through each page in the incoming stream
    for (int m = 0; m < pages; m++) {
        int s = 0; // Reset found flag
        // Check if page is already in one of the frames
        for (int n = 0; n < frames; n++) {
            if (incomingStream[m] == temp[n]) {
                s++; // Page found in frame
                break; // No need to check further
            }
        }

        if (s == 0) { // Page fault (page not found in frames)
            pageFaults++;

            // Check if there's an empty frame
            int emptyFrame = -1;
            for (int n = 0; n < frames; n++) {
                if (temp[n] == -1) {
                    emptyFrame = n;
                    break;
                }
            }

            if (emptyFrame != -1) {
                // Use the empty frame
                temp[emptyFrame] = incomingStream[m];
            } else {
                // Find the page to replace using OPR
                int farthest = -1;
                int replaceIndex = -1;

                for (int n = 0; n < frames; n++) {
                    int j;
                    // Look ahead in the incoming stream to see when the page is used
                    for (j = m + 1; j < pages; j++) {
                        if (temp[n] == incomingStream[j]) {
                            break;
                        }
                    }

                    // If the page is not found in the future, replace it
                    if (j == pages) {
                        replaceIndex = n;
                        break;
                    }

                    // If this page is found, check the farthest one
                    if (j > farthest) {
                        farthest = j;
                        replaceIndex = n;
                    }
                }

                // Replace the page
                temp[replaceIndex] = incomingStream[m];
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

    // Output the total page faults and hits
    printf("Total Page Faults:\t%d\n", pageFaults);
    printf("Total Page Hits:\t%d\n", pages - pageFaults);

    return 0;
}

