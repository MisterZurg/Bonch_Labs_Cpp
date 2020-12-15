#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <iostream>

#define KEY (149212)

using namespace std;

int main()
{
    int id;

    union semun {
        int val;
        struct semid_ds *buf;
        ushort * array;
    } argument;
    argument.val = 0;

    id = semget(KEY, 1, 0666);

    if (id < 0)
    {
        cerr << "Cannot find semaphore\n";
        exit(0);
    }

    cout << "Semaphore found\n";

    float elapsed_time = 0;

    cout << "Waiting...\n";

    while (true)
    {
        usleep(100000);
        elapsed_time += 0.1;
        if (semctl(id, 0, GETVAL, argument) > 0) 
        {
            cout << "Current semaphore value: " << semctl(id, 0, GETVAL, argument) << endl;
            cout << "pid: " << getppid() << endl;
            cout << "Time elapsed: " << elapsed_time << "seconds\n";
            break;
        }
    }

    cout << "Shutting down...\n";
    sleep(3);

    return 0;
}