

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    mode_t mode = S_IRUSR | S_IWUSR;

    // Open or create file
    fd = open("lab2(2).txt",O_CREAT | O_RDWR | O_TRUNC, mode);
    if (fd == -1) 
    {
        perror("open");
        return 1;
    }

    // Close the file descriptor
    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}


