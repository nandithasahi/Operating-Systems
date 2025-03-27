#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
int pipefds[2];
pid_t child_pid;
char write_msg[]="Hello fom parent!";
char read_msg[100];

//create the pipe
if(pipe(pipefds)==-1)
{
perror("Pipe creation failed.");
return 1;
}
child_pid= fork();

if(child_pid< 0)
{
perror("Fork failed.");
return 1;
}
if (child_pid==0)
{
//child reads from pipe
close(pipefds[1]);//closing write end
read(pipefds[0], read_msg, sizeof(read_msg));
printf("Child received message: %s\n", read_msg);
close(pipefds[0]);
}
else
{
//parent writes on pipe
close(pipefds[0]);//closing read end
write(pipefds[1], write_msg, strlen(write_msg)+1);
printf("Child received message: %s\n", write_msg);
close(pipefds[1]);
}
return 0;
}
