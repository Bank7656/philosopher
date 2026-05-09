#include "philosopher_bonus.h"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    sem_t   *my_sem;
    pid_t   pid;
    int     status;
    int     timeout = 2;

    my_sem = sem_open("/watchdog_sem", O_CREAT, 0644, 1);
    pid = fork();
    if (pid == 0)
    {
        printf("Child: Attempt to lock semaphore\n");
        sem_wait(my_sem);
        printf("Child: semaphore is lock\n");
        while (1)
            sleep(1);
        sem_post(my_sem);
        printf("Child: semaphore is unlock\n");
    }
    else
    {
        sleep(timeout);
        if (waitpid(pid, &status, WNOHANG) == 0)
        {
            printf("Child stuct\n");
            kill(pid, SIGKILL);
            waitpid(pid, &status, 0);
            printf("Child Terminated\n");
            sem_post(my_sem);
        }
        else
            printf("Child finished\n");
    }
    sem_close(my_sem);
    sem_unlink("/watchdog_sem");
    return (0);
}