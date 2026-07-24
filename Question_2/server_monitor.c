#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>

int main() {
  pid_t pid = fork()

  if (pid < 0) {
    perror("Fork failed");
    return 1;
}

if (pid == 0) {
    printf("[Child] Process ID: %d started. Simulating unresponsive state...\n", getpid());
    while(1) {
        sleep(1);
    }
} else {
    printf("[Parent] Monitoring child process with PID: %d\n", pid);
    sleep(3);

    printf("[Parent] Child %d is not responding. Sending SIGTERM...\n", pid);
    kill(pid, SIGTERM);

    int status;
    pid_t wpid = waitpid(pid, &status, 0);

    if(wpid > 0 && WIFSIGNALED(status)) {
       printf("[PARENT] Child %d cleaned up. Zombie prevented.\n", wpid);
    }
}
return 0;
}
