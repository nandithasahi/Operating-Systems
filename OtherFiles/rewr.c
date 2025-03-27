#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    int fd_read, fd_write;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;

    fd_read = open("lab2(2).txt", O_RDONLY);
    if (fd_read == -1) {
        perror("open input.txt");
        return 1;
    }

    // Open or create the output file for writing
    fd_write = open("lab2(1).txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if (fd_write == -1) {
        perror("open output.txt");
        close(fd_read);
        return 1;
    }

    // Read from fd_read into buffer
    bytes_read = read(fd_read, buffer, BUFFER_SIZE);
    if (bytes_read == -1) 
    {
        perror("read");
        close(fd_read);
        close(fd_write);
        return 1;
    }

    // Write from buffer to fd_write
    bytes_written = write(fd_write, buffer, bytes_read);
    if (bytes_written == -1) 
    {
        perror("write");
        close(fd_read);
        close(fd_write);
        return 1;
    }

    printf("Successfully copied %zd bytes from lab2(2).txt to lab1(1).txt\n", bytes_written);

    // Close file descriptors
    close(fd_read);
    close(fd_write);

    return 0;
}

